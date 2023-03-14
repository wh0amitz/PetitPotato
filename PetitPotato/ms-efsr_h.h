

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ms-efsr.idl:
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


#ifndef __ms2Defsr_h_h__
#define __ms2Defsr_h_h__

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


#ifndef __DefaultIfName_INTERFACE_DEFINED__
#define __DefaultIfName_INTERFACE_DEFINED__

/* interface DefaultIfName */
/* [version][uuid] */ 

typedef struct Struct_68_t
    {
    unsigned char StructMember0[ 6 ];
    } 	Struct_68_t;

typedef struct Struct_100_t
    {
    unsigned char StructMember0;
    unsigned char StructMember1;
    struct Struct_68_t StructMember2;
    /* [size_is] */ long StructMember3[ 1 ];
    } 	Struct_100_t;

typedef struct Struct_136_t
    {
    long StructMember0;
    /* [size_is][unique] */ unsigned char *StructMember1;
    } 	Struct_136_t;

typedef struct Struct_152_t
    {
    long StructMember0;
    /* [unique] */ struct Struct_100_t *StructMember1;
    /* [unique] */ struct Struct_136_t *StructMember2;
    /* [string][unique] */ wchar_t *StructMember3;
    } 	Struct_152_t;

typedef struct Struct_220_t
    {
    long StructMember0;
    /* [size_is][unique] */ struct Struct_152_t **StructMember1;
    } 	Struct_220_t;

typedef struct Struct_266_t
    {
    long StructMember0;
    long StructMember1;
    /* [size_is][unique] */ unsigned char *StructMember2;
    } 	Struct_266_t;

typedef struct Struct_282_t
    {
    long StructMember0;
    /* [unique] */ struct Struct_100_t *StructMember1;
    /* [unique] */ struct Struct_266_t *StructMember2;
    } 	Struct_282_t;

typedef struct Struct_346_t
    {
    long StructMember0;
    /* [size_is][unique] */ struct Struct_282_t **StructMember1;
    } 	Struct_346_t;

typedef struct Struct_392_t
    {
    long StructMember0;
    /* [size_is][unique] */ unsigned char *StructMember1;
    } 	Struct_392_t;

typedef struct Struct_462_t
    {
    /* [range] */ long StructMember0;
    /* [range] */ long StructMember1;
    /* [size_is][unique] */ unsigned char *StructMember2;
    } 	Struct_462_t;

typedef struct Struct_492_t
    {
    long StructMember0;
    /* [unique] */ struct Struct_220_t *StructMember1;
    /* [unique] */ struct Struct_282_t *StructMember2;
    /* [unique] */ struct Struct_392_t *StructMember3;
    } 	Struct_492_t;

long Proc0_EfsRpcOpenFileRaw_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [context_handle][out] */ void **arg_1,
    /* [string][in] */ wchar_t *arg_2,
    /* [in] */ long arg_3);

long Proc1_EfsRpcReadFileRaw_Downlevel( 
    /* [context_handle][in] */ void *arg_0,
    /* [out] */ unsigned char *arg_1);

long Proc2_EfsRpcWriteFileRaw_Downlevel( 
    /* [context_handle][in] */ void *arg_0,
    /* [in] */ unsigned char *arg_1);

void Proc3_EfsRpcCloseRaw_Downlevel( 
    /* [context_handle][out][in] */ void **arg_0);

long Proc4_EfsRpcEncryptFileSrv_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1);

long Proc5_EfsRpcDecryptFileSrv_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [in] */ long arg_2);

long Proc6_EfsRpcQueryUsersOnFile_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [ref][out] */ struct Struct_220_t **arg_2);

long Proc7_EfsRpcQueryRecoveryAgents_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [ref][out] */ struct Struct_220_t **arg_2);

long Proc8_EfsRpcRemoveUsersFromFile_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [in] */ struct Struct_220_t *arg_2);

long Proc9_EfsRpcAddUsersToFile_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [in] */ struct Struct_346_t *arg_2);

long Proc10_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [unique][in] */ struct Struct_282_t *arg_1,
    /* [in] */ long arg_2,
    /* [in] */ long arg_3);

long Proc11_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [string][in] */ wchar_t *arg_2,
    /* [in] */ long arg_3,
    /* [in] */ long arg_4,
    /* [unique][in] */ struct Struct_392_t *arg_5,
    /* [in] */ long arg_6);

long Proc12_EfsRpcFileKeyInfo_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [in] */ long arg_2,
    /* [ref][out] */ struct Struct_392_t **arg_3);

long Proc13_EfsRpcDuplicateEncryptionInfoFile_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [string][in] */ wchar_t *arg_2,
    /* [in] */ long arg_3,
    /* [in] */ long arg_4,
    /* [unique][in] */ struct Struct_392_t *arg_5,
    /* [in] */ long arg_6);

long Proc14_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ struct Struct_136_t *arg_1,
    /* [in] */ struct Struct_462_t *arg_2);

long Proc15_EfsRpcAddUsersToFileEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long arg_1,
    /* [unique][in] */ struct Struct_392_t *arg_2,
    /* [string][in] */ wchar_t *arg_3,
    /* [in] */ struct Struct_346_t *arg_4);

long Proc16_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long arg_1,
    /* [unique][in] */ struct Struct_392_t *arg_2,
    /* [string][in] */ wchar_t *arg_3,
    /* [in] */ long arg_4,
    /* [ref][out] */ struct Struct_392_t **arg_5);

long Proc17_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [ref][out] */ struct Struct_392_t **arg_1);

long Proc18_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [ref][out] */ struct Struct_392_t **arg_2);

long Proc19_EfsRpcFileKeyInfoEx_Downlevel( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ wchar_t *arg_1,
    /* [unique][in] */ struct Struct_392_t *arg_2,
    /* [in] */ struct Struct_392_t *arg_3,
    /* [unique][in] */ struct Struct_492_t *arg_4);

long Proc20_EfsRpcFlushEfsCache_Downlevel( 
    /* [in] */ handle_t IDL_handle);



extern RPC_IF_HANDLE DefaultIfName_v1_0_c_ifspec;
extern RPC_IF_HANDLE DefaultIfName_v1_0_s_ifspec;
#endif /* __DefaultIfName_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


