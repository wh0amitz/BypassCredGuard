#pragma once
#include "stdafx.h"


typedef struct _MEMORY_ADDRESS {
	LPVOID address;
} MEMORY_ADDRESS, * PMEMORY_ADDRESS;

typedef struct _MEMORY_RANGE {
	MEMORY_ADDRESS memoryAdress;
	SIZE_T size;
} MEMORY_RANGE, * PMEMORY_RANGE;

typedef struct _MEMORY_SEARCH {
	MEMORY_RANGE memoryRange;
	LPVOID result;
} MEMORY_SEARCH, * PMEMORY_SEARCH;

BOOL MemorySearch(HANDLE hProcess, LPBYTE Pattern, SIZE_T Length, PMEMORY_SEARCH Search);