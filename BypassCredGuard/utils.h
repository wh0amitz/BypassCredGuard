#pragma once
#include "stdafx.h"

BOOL LsaSearchGeneric(PLSA_CONTEXT cLsass, PLSA_LIB pLib, PPATCH_GENERIC genericReferences, SIZE_T cbReferences, PVOID* genericPtr, PVOID* genericPtr1);
PPATCH_GENERIC GetGenericFromBuild(PPATCH_GENERIC generics, SIZE_T cbGenerics, DWORD BuildNumber);
void PrintfHex(LPCVOID lpData, DWORD cbData);