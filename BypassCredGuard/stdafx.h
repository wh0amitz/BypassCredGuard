#pragma once

#define SECURITY_WIN32

#include <Windows.h>
#include <rpc.h>
#include <rpcndr.h>
#include <stdio.h>
#include <DsGetDC.h>
#include <sspi.h>
#include <Midles.h>
#include <sddl.h>
#include <string.h>
#include <bcrypt.h>
#include <tlhelp32.h>
#include <NTSecAPI.h>
#include <NTSecPKG.h>

#include "privilege.h"
#include "memory.h"
#include "process.h"
#include "lsa.h"
#include "patch.h"
#include "utils.h"

#pragma comment(lib, "Ntdsapi.lib")
#pragma comment(lib, "Secur32.lib")

#if !defined(NT_SUCCESS)
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#define WIN_BUILD_XP		2600
#define WIN_BUILD_2K3	    3790
#define WIN_BUILD_VISTA	    6000
#define WIN_BUILD_7		    7600
#define WIN_BUILD_8		    9200
#define WIN_BUILD_BLUE	    9600
#define WIN_BUILD_10_1507	10240
#define WIN_BUILD_10_1511	10586
#define WIN_BUILD_10_1607	14393
#define WIN_BUILD_10_1703	15063
#define WIN_BUILD_10_1709	16299
#define WIN_BUILD_10_1803	17134
#define WIN_BUILD_10_1809	17763
#define WIN_BUILD_10_1903	18362
#define WIN_BUILD_10_1909	18363
#define WIN_BUILD_10_2004	19041
#define WIN_BUILD_10_20H2	19042
#define WIN_BUILD_10_21H2	19044
#define WIN_BUILD_2022		20348

#define WIN_MIN_BUILD_XP	2500
#define WIN_MIN_BUILD_2K3	3000
#define WIN_MIN_BUILD_VISTA	5000
#define WIN_MIN_BUILD_7		7000
#define WIN_MIN_BUILD_8		8000
#define WIN_MIN_BUILD_BLUE	9400
#define WIN_MIN_BUILD_10	9800
#define WIN_MIN_BUILD_11	22000


extern DWORD NT_MAJOR_VERSION, NT_MINOR_VERSION, NT_BUILD_NUMBER;

#ifdef __cplusplus
extern "C" VOID WINAPI RtlGetNtVersionNumbers(LPDWORD pMajor, LPDWORD pMinor, LPDWORD pBuild);
#endif