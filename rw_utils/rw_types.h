/*		rw_types.h	Written by Marek Iwaniuk (c).
 *		Created on 02/07/2017 (MM/DD/YYYY)
 */

#pragma once

#ifndef RW_TYPES
#define RW_TYPES

#include <Windows.h>

typedef CHAR	uchar_4;
typedef BYTE	uint_8;		// 1 BYTE
typedef WORD	uint_16;	// 2 BYTEs (WORD)
typedef DWORD32	uint_32;	// 4 BYTEs (DWORD)
typedef DWORD64 uint_64;	// 8 BYTEs (QWORD)
typedef FLOAT	float_32;	// 4 BYTEs FLOAT

#endif