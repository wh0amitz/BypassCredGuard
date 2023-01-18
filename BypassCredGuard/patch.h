#pragma once
#include "stdafx.h"

typedef struct _PATCH_PATTERN {
	DWORD Length;
	BYTE* Pattern;
} PATCH_PATTERN, * PPATCH_PATTERN;

typedef struct _PATCH_OFFSETS {
	LONG off0;
#if defined(_M_ARM64)
	LONG armOff0;
#endif
	LONG off1;
#if defined(_M_ARM64)
	LONG armOff1;
#endif
	LONG off2;
#if defined(_M_ARM64)
	LONG armOff2;
#endif
	LONG off3;
#if defined(_M_ARM64)
	LONG armOff3;
#endif
	LONG off4;
#if defined(_M_ARM64)
	LONG armOff4;
#endif
	LONG off5;
#if defined(_M_ARM64)
	LONG armOff5;
#endif
	LONG off6;
#if defined(_M_ARM64)
	LONG armOff6;
#endif
	LONG off7;
#if defined(_M_ARM64)
	LONG armOff7;
#endif
	LONG off8;
#if defined(_M_ARM64)
	LONG armOff8;
#endif
	LONG off9;
#if defined(_M_ARM64)
	LONG armOff9;
#endif
} PATCH_OFFSETS, * PPATCH_OFFSETS;

typedef struct _PATCH_GENERIC {
	DWORD MinBuildNumber;
	PATCH_PATTERN Search;
	PATCH_PATTERN Patch;
	PATCH_OFFSETS Offsets;
} PATCH_GENERIC, * PPATCH_GENERIC;