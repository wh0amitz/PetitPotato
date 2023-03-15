

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ms-dtyp.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ms2Ddtyp_h_h__
#define __ms2Ddtyp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ms2Ddtyp_0000_0000 */
/* [local] */ 

#ifndef _DTYP_IDL
#define _DTYP_IDL
#ifndef _WINDEF_H
typedef int BOOL;

typedef int *PBOOL;

typedef int *LPBOOL;

typedef unsigned char BYTE;

typedef unsigned char *PBYTE;

typedef unsigned char *LPBYTE;

typedef unsigned long DWORD;

typedef unsigned long *PDWORD;

typedef unsigned long *LPDWORD;

#endif
#ifndef _BASETSD_H_
typedef unsigned int DWORD32;

typedef unsigned __int64 DWORD64;

#endif
#ifndef _WINDEF_H
typedef int INT;

typedef int *LPINT;

#endif
#ifndef _BASETSD_H_
typedef signed char INT8;

typedef short INT16;

typedef int INT32;

typedef __int64 INT64;

#endif
#ifndef _BASETSD_H_
typedef int LONG32;

typedef __int64 LONG64;

#endif
typedef unsigned __int64 QWORD;

#ifndef _WINNT_
typedef short SHORT;

#endif
typedef __int64 TIME;

#ifndef _WINNT_
typedef unsigned char CHAR;

typedef unsigned char *PCHAR;

typedef unsigned char UCHAR;

typedef unsigned char *PUCHAR;

#endif
#ifndef _WINDEF_H
typedef unsigned int UINT;

#endif
#ifndef _BASETSD_H_
typedef unsigned char UINT8;

typedef unsigned short UINT16;

typedef unsigned int UINT32;

typedef unsigned __int64 UINT64;

#endif
#ifndef _WINNT_
typedef unsigned long ULONG;

typedef unsigned long *PULONG;

#endif
#ifndef _BASETSD_H_
typedef unsigned int ULONG32;

typedef unsigned __int64 ULONG64;

#endif
#ifndef _WINNT_
typedef unsigned __int64 ULONGLONG;

typedef unsigned short USHORT;

#endif
#ifndef _WINDEF_H
typedef unsigned short WORD;

typedef unsigned short *PWORD;

typedef unsigned short *LPWORD;

#endif
#ifndef _WINNT_
typedef long LONG;

typedef long *PLONG;

#endif
#ifndef _WINDEF_H
typedef long *LPLONG;

#endif
#ifndef _WINNT_
typedef __int64 LONGLONG;

#endif
#ifndef _WINDEF_H
typedef float FLOAT;

#endif
#ifndef __wtypes_h__
typedef double DOUBLE;

#endif
#ifndef _WINNT_
typedef BYTE BOOLEAN;

typedef BYTE *PBOOLEAN;

#endif
#ifndef _BASETSD_H_
typedef __int64 LONG_PTR;

typedef unsigned __int64 ULONG_PTR;

typedef ULONG_PTR SIZE_T;

typedef ULONG_PTR DWORD_PTR;

#endif
typedef DWORD NET_API_STATUS;

#ifndef _WINNT_
typedef ULONGLONG DWORDLONG;

typedef ULONGLONG *PDWORDLONG;

#endif
typedef DWORD HCALL;

#ifndef _WINNT_
typedef void *HANDLE;

typedef void *PVOID;

#endif
#ifndef __WINE_RPCDCE_H
typedef void *RPC_BINDING_HANDLE;

#endif
typedef /* [context_handle] */ void *PCONTEXT_HANDLE;

typedef PCONTEXT_HANDLE *PPCONTEXT_HANDLE;

#ifndef _WINNT_
typedef wchar_t WCHAR;

typedef wchar_t *PWCHAR;

#if 0
typedef wchar_t UNICODE;

#endif
typedef const unsigned char *LPCSTR;

typedef const wchar_t *LPCWSTR;

typedef unsigned char *PSTR;

typedef unsigned char *LPSTR;

typedef wchar_t *LPWSTR;

typedef wchar_t *PWSTR;

#endif
typedef const wchar_t *LMCSTR;

typedef WCHAR *LMSTR;

#ifndef __wtypes_h__
typedef WCHAR *BSTR;

#endif
#if 0
typedef LPCSTR LPCTSTR;

typedef LPSTR LPTSTR;

typedef CHAR TCHAR;

#endif
#if 0
typedef struct _FILETIME
    {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
    } 	FILETIME;

typedef struct _FILETIME *PFILETIME;

typedef struct _FILETIME *LPFILETIME;

typedef struct _GUID
    {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[ 8 ];
    } 	GUID;

typedef struct _GUID UUID;

typedef struct _GUID *PGUID;

typedef struct _LARGE_INTEGER
    {
    LONGLONG QuadPart;
    } 	LARGE_INTEGER;

typedef struct _LARGE_INTEGER *PLARGE_INTEGER;

typedef DWORD LCID;

#endif
typedef struct _RPC_UNICODE_STRING
    {
    USHORT Length;
    USHORT MaximumLength;
    /* [length_is][size_is] */ LPWSTR Buffer;
    } 	RPC_UNICODE_STRING;

typedef struct _RPC_UNICODE_STRING *PRPC_UNICODE_STRING;

#if 0
typedef struct _SYSTEMTIME
    {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
    } 	SYSTEMTIME;

typedef struct _SYSTEMTIME *PSYSTEMTIME;

typedef struct _UINT128
    {
    UINT64 lower;
    UINT64 upper;
    } 	UINT128;

typedef struct _UINT128 *PUINT128;

typedef struct _ULARGE_INTEGER
    {
    ULONGLONG QuadPart;
    } 	ULARGE_INTEGER;

typedef struct _ULARGE_INTEGER *PULARGE_INTEGER;

typedef struct _UNICODE_STRING
    {
    USHORT Length;
    USHORT MaximumLength;
    /* [length_is][size_is] */ LPWSTR Buffer;
    } 	UNICODE_STRING;

typedef struct _UNICODE_STRING *PUNICODE_STRING;

#endif
#if 0
typedef struct _SID_IDENTIFIER_AUTHORITY
    {
    BYTE Value[ 6 ];
    } 	SID_IDENTIFIER_AUTHORITY;

typedef struct _SID
    {
    BYTE Revision;
    BYTE SubAuthorityCount;
    SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
    /* [size_is] */ DWORD SubAuthority[ 1 ];
    } 	SID;

typedef struct _SID *PSID;

typedef struct _ACCESS_MASK
    {
    DWORD ACCESS_MASK;
    } 	ACCESS_MASK;

typedef struct _ACCESS_MASK *PACCESS_MASK;

typedef struct _ACE_HEADER
    {
    UCHAR AceType;
    UCHAR AceFlags;
    USHORT AceSize;
    } 	ACE_HEADER;

typedef struct _ACE_HEADER *PACE_HEADER;

typedef struct _ACCESS_ALLOWED_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	ACCESS_ALLOWED_ACE;

typedef struct _ACCESS_ALLOWED_ACE *PACCESS_ALLOWED_ACE;

typedef struct _ACCESS_ALLOWED_OBJECT_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD Flags;
    GUID ObjectType;
    GUID InheritedObjectType;
    DWORD SidStart;
    } 	ACCESS_ALLOWED_OBJECT_ACE;

typedef struct _ACCESS_ALLOWED_OBJECT_ACE *PACCESS_ALLOWED_OBJECT_ACE;

typedef struct _ACCESS_DENIED_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	ACCESS_DENIED_ACE;

typedef struct _ACCESS_DENIED_ACE *PACCESS_DENIED_ACE;

typedef struct _ACCESS_ALLOWED_CALLBACK_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	ACCESS_ALLOWED_CALLBACK_ACE;

typedef struct _ACCESS_ALLOWED_CALLBACK_ACE *PACCESS_ALLOWED_CALLBACK_ACE;

typedef struct _ACCESS_DENIED_CALLBACK_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	ACCESS_DENIED_CALLBACK_ACE;

typedef struct _ACCESS_DENIED_CALLBACK_ACE *PACCESS_DENIED_CALLBACK_ACE;

typedef struct _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD Flags;
    GUID ObjectType;
    GUID InheritedObjectType;
    DWORD SidStart;
    } 	ACCESS_ALLOWED_CALLBACK_OBJECT_ACE;

typedef struct _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE *PACCESS_ALLOWED_CALLBACK_OBJECT_ACE;

typedef struct _ACCESS_DENIED_CALLBACK_OBJECT_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD Flags;
    GUID ObjectType;
    GUID InheritedObjectType;
    DWORD SidStart;
    } 	ACCESS_DENIED_CALLBACK_OBJECT_ACE;

typedef struct _ACCESS_DENIED_CALLBACK_OBJECT_ACE *PACCESS_DENIED_CALLBACK_OBJECT_ACE;

typedef struct _SYSTEM_AUDIT_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	SYSTEM_AUDIT_ACE;

typedef struct _SYSTEM_AUDIT_ACE *PSYSTEM_AUDIT_ACE;

typedef struct _SYSTEM_AUDIT_CALLBACK_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	SYSTEM_AUDIT_CALLBACK_ACE;

typedef struct _SYSTEM_AUDIT_CALLBACK_ACE *PSYSTEM_AUDIT_CALLBACK_ACE;

typedef struct _SYSTEM_MANDATORY_LABEL_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD SidStart;
    } 	SYSTEM_MANDATORY_LABEL_ACE;

typedef struct _SYSTEM_MANDATORY_LABEL_ACE *PSYSTEM_MANDATORY_LABEL_ACE;

typedef struct _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE
    {
    ACE_HEADER Header;
    ACCESS_MASK Mask;
    DWORD Flags;
    GUID ObjectType;
    GUID InheritedObjectType;
    DWORD SidStart;
    } 	SYSTEM_AUDIT_CALLBACK_OBJECT_ACE;

typedef struct _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE *PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE;

typedef struct _ACL
    {
    UCHAR AclRevision;
    UCHAR Sbz1;
    USHORT AclSize;
    USHORT AceCount;
    USHORT Sbz2;
    } 	ACL;

typedef struct _ACL *PACL;

typedef struct _SECURITY_DESCRIPTOR
    {
    UCHAR Revision;
    UCHAR Sbz1;
    USHORT Control;
    ULONG Owner;
    ULONG Group;
    ULONG Sacl;
    ULONG Dacl;
    } 	SECURITY_DESCRIPTOR;

typedef struct _SECURITY_DESCRIPTOR *PSECURITY_DESCRIPTOR;

typedef DWORD SECURITY_INFORMATION;

typedef DWORD *PSECURITY_INFORMATION;

#endif
typedef struct _RPC_SID
    {
    UCHAR Revision;
    UCHAR SubAuthorityCount;
    SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
    /* [size_is] */ DWORD SubAuthority[ 1 ];
    } 	RPC_SID;

typedef struct _RPC_SID *PRPC_SID;

#endif /* _DTYP_IDL */


extern RPC_IF_HANDLE __MIDL_itf_ms2Ddtyp_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ms2Ddtyp_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


