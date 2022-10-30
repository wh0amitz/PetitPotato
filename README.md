# PetitPotato

Local privilege escalation via PetitPotam (Abusing impersonate privileges).

## Description

[PetitPotam](https://github.com/topotam/PetitPotam) uses MS-EFSR (Encrypting File System Remote), a protocol used to perform maintenance and management operations on encrypted data stored remotely and accessed over a network. There are a series of APIs similar to `EfsRpcOpenFileRaw` in MS-EFSR. The syntax of the `EfsRpcOpenFileRaw` API is shown below.

```c++
long EfsRpcOpenFileRaw(
   [in] handle_t binding_h,
   [out] PEXIMPORT_CONTEXT_HANDLE* hContext,
   [in, string] wchar_t* FileName,
   [in] long Flags
 );
```

Such APIs can specify a UNC path via the FileName parameter to open encrypted objects on the server for backup or restore. When the path in the format `\\IP\C$` is specified, the lsass.exe service will access `\\IP\pipe\srvsvc` with `NT AUTHORITY SYSTEM` account privileges.

If we can call the `EfsRpcOpenFileRaw` API to force the local computer to connect to the malicious named pipe we created, then we can impersonate the named pipe client process and eventually gain the SYSTEKM privilege.

Here are all the APIs I found that have a FileName parameter, and most of them can be used for privilege escalation (but when I tested locally, some API calls failed, maybe I made a mistake somewhere):

|                MS-EFSR API                 | EfsID |
| :----------------------------------------: | :---: |
|             EfsRpcOpenFileRaw              |   0   |
|            EfsRpcEncryptFileSrv            |   1   |
|            EfsRpcDecryptFileSrv            |   2   |
|           EfsRpcQueryUsersOnFile           |   3   |
|         EfsRpcQueryRecoveryAgents          |   4   |
|     EfsRpcRemoveUsersFromFile (Failed)     |   5   |
|            EfsRpcAddUsersToFile            |   6   |
|             EfsRpcFileKeyInfo              |   7   |
| EfsRpcDuplicateEncryptionInfoFile (Failed) |   8   |
|           EfsRpcAddUsersToFileEx           |   9   |
|        EfsRpcFileKeyInfoEx (Failed)        |  10   |
|  EfsRpcGetEncryptedFileMetadata (Failed)   |  11   |
|  EfsRpcSetEncryptedFileMetadata (Failed)   |  12   |


## Usage

```powershell
PetitPotato.exe [EfsID] [Command]
```

- `EfsID`: MS-EFSR API number to use
- `Command`: command to execute

## Example

```cmd
C:\Users\Administrator\Desktop>PetitPotato.exe 3 cmd.exe

[+] Malicious named pipe running on \\.\pipe\petit\pipe\srvsvc.
[+] Invoking EfsRpcQueryUsersOnFile with target path: \\localhost/pipe/petit\C$\wh0nqs.txt.
[+] The connection is successful.
[+] ImpersonateNamedPipeClient OK.
[+] OpenThreadToken OK.
[+] DuplicateTokenEx OK.
[+] CreateProcessAsUser OK.
Microsoft Windows [版本 10.0.18363.592]
(c) 2019 Microsoft Corporation。保留所有权利。

C:\Windows\system32>whoami
nt authority\system

C:\Windows\system32>
```

![image-20221030165055659](/images/image-20221030165055659.png)

![image-20221030165622668](/images/image-20221030165622668.png)

## Link

- https://github.com/topotam/PetitPotam
- https://itm4n.github.io/printspoofer-abusing-impersonate-privileges/
- https://itm4n.github.io/from-rpcview-to-petitpotam/

