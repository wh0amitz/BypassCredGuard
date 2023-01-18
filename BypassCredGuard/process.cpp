#include "stdafx.h"


DWORD GetProcessIdByName(LPCWSTR processName)
{
	// Create toolhelp snapshot.
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	// Walkthrough all processes.
	if (Process32FirstW(hSnapshot, &process))
	{
		do
		{
			if (_wcsicmp(process.szExeFile, processName) == 0)
			{
				return process.th32ProcessID;
			}
		} while (Process32NextW(hSnapshot, &process));
	}

	CloseHandle(hSnapshot);
	return 0;
}


BOOL GetVeryBasicModuleInformations(HANDLE hProcess)
{
	BOOL status = FALSE;
	PEB Peb;
	PEB_LDR_DATA LdrData;
	LDR_DATA_TABLE_ENTRY LdrEntry;
	PROCESS_VERY_BASIC_MODULE_INFORMATION moduleInformation;
	UNICODE_STRING moduleName;
	PBYTE pListEntryStart, pListEntryEnd;

	moduleInformation.ModuleName = &moduleName;
	if (GetProcessPeb(hProcess, &Peb))
	{
		if (ReadProcessMemory(hProcess, Peb.Ldr, &LdrData, sizeof(PEB_LDR_DATA), NULL))
		{
			for (
				pListEntryStart = (PBYTE)LdrData.InLoadOrderModuleList.Flink,
				pListEntryEnd = (PBYTE)Peb.Ldr + FIELD_OFFSET(PEB_LDR_DATA, InLoadOrderModuleList);
				pListEntryStart != pListEntryEnd;
				pListEntryStart = (PBYTE)LdrEntry.InLoadOrderLinks.Flink
				)
			{
				if (ReadProcessMemory(hProcess, pListEntryStart, &LdrEntry, sizeof(LDR_DATA_TABLE_ENTRY), NULL))
				{
					moduleInformation.DllBase.address = LdrEntry.DllBase;
					moduleInformation.SizeOfImage = LdrEntry.SizeOfImage;
					moduleName = LdrEntry.BaseDllName;

					if (GetUnicodeString(&moduleName, cLsass.hProcess))
					{
						status = FindModules(&moduleInformation);
					}
					LocalFree(moduleName.Buffer);
				}
			}
		}
	}
	return status;
}


BOOL GetProcessPeb(HANDLE hProcess, PPEB pPeb)
{
	BOOL status = FALSE;
	PROCESS_BASIC_INFORMATION processInformations;
	ULONG returnLength;

	if (NT_SUCCESS(NtQueryInformationProcess(hProcess, ProcessBasicInformation, &processInformations, sizeof(processInformations), &returnLength)) 
		&& (returnLength == sizeof(processInformations)) 
		&& processInformations.PebBaseAddress)
	{
		status = ReadProcessMemory(hProcess, processInformations.PebBaseAddress, pPeb, sizeof(PEB), NULL);
	}

	return status;
}


BOOL GetUnicodeString(PUNICODE_STRING string, HANDLE hProcess)
{
	BOOL status = FALSE;
	MEMORY_ADDRESS aDestin = { NULL };
	MEMORY_ADDRESS aSource = { string->Buffer };

	string->Buffer = NULL;
	if (aSource.address && string->MaximumLength)
	{
		if (aDestin.address = LocalAlloc(LPTR, string->MaximumLength))
		{
			string->Buffer = (PWSTR)aDestin.address;
			status = ReadProcessMemory(hProcess, aSource.address, aDestin.address, string->MaximumLength, NULL);
		}
	}
	return status;
}