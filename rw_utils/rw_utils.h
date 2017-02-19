/*		rw_utils.h	Written by Marek Iwaniuk (c).
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/04/2017 (MM/DD/YYYY)
*/

#pragma once

#ifndef RW_UTILS
#define RW_UTILS

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <iomanip>

#include "ConsoleColors.h"

#include "rw_file.h"
#include "rw_dff_structure.h"

enum IOBracets {
	ioOPEN = 1,
	ioCLOSE = 2
};

static class RwUtils {
public:
	/* --- Reading functions --- */
	static uint_8		readByteFromArrayLE(uint_8* buffer, size_t &ptr_pos);
	static uint_16		readWordFromArrayLE(uint_8* buffer, size_t &ptr_pos);
	static uint_32		readDwordFromArrayLE(uint_8* buffer, size_t &ptr_pos);
	static float_32		readFloatFromArrayLE(uint_8* buffer, size_t &ptr_pos);
	static uint_8*		readData(uint_8* buffer, size_t &ptr_pos, size_t dataSize);
	static std::string	readString(uint_8* buffer, size_t &ptr_pos, size_t dataSize);

	/* --- Printing functions --- */
	static void printLevelSpacing(int level);
	static void printVoidStructure(int level);
	static void printPointerPosition(int ptr_pos);

	static void printBracet(IOBracets bracet, size_t levelSpacing = 0);
	template<typename T>
	static void printVarType();
	template<typename T>
	static void printDecVariable(char* varName, T var, size_t spacingLevel = 0);
	template<typename T>
	static void printHexVariable(char* varName, T var, size_t spacingLevel = 0);
	template<typename ...T>
	static void printArrayElement(char* arrLabel, size_t elementNum, size_t spacingLevel, T... args);
	static void printStringVariable(char* varName, std::string var, size_t spacingLevel = 0);
	static void printFileInfo(RwFile *rwFile);
	static void printHeaderInfo(RwSectionHeader &header, int level);
	static void printClumpDataStruct(RwClumpData &clumpDataStruct, int level);
	static void printFrameListData(RwFrameListData &frameListData, int level);
	static void printGeometryListData(RwGeometryListData &gld, int level);
	static void printGeometryData(RwGeometryData &gd, int level);
	static void printMaterialListData(RwMaterialListData &mld, int level);
	static void printMaterialData(RwMaterialData &md, int level);
	static void printTextureData(RwTextureData &td, int level);
	static void printStringData(RwString &str, int level);

	/* --- Other functions --- */
	static uint_32		unpackLibraryVersion(uint_32 libid);
	static std::string	getSectionTypeName(uint_32 type);
	static std::string	getVersion(uint_32 type, bool includeGameVersion);
};

#endif