#include "stdafx.h"

BOOL MemorySearch(HANDLE hProcess, LPBYTE Pattern, SIZE_T Length, PMEMORY_SEARCH Search)
{
	BOOL status = FALSE;
	MEMORY_SEARCH sBuffer = { { NULL, Search->memoryRange.size}, NULL };
	PBYTE CurrentPtr;
	PBYTE limit;

	if (sBuffer.memoryRange.memoryAdress.address = LocalAlloc(LPTR, Search->memoryRange.size))
	{
		if (ReadProcessMemory(hProcess, Search->memoryRange.memoryAdress.address, sBuffer.memoryRange.memoryAdress.address, Search->memoryRange.size, NULL))
		{
			limit = (PBYTE)sBuffer.memoryRange.memoryAdress.address + sBuffer.memoryRange.size;
			for (CurrentPtr = (PBYTE)sBuffer.memoryRange.memoryAdress.address; !status && (CurrentPtr + Length <= limit); CurrentPtr++)
				status = RtlEqualMemory(Pattern, CurrentPtr, Length);
			CurrentPtr--;
			Search->result = (PBYTE)Search->memoryRange.memoryAdress.address + ((PBYTE)CurrentPtr - (PBYTE)sBuffer.memoryRange.memoryAdress.address);
		}
	}
	return status;
}