/*		rw_utils.cpp	Written by Marek Iwaniuk (c).
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/04/2017 (MM/DD/YYYY)
*/

#include "stdafx.h"

#include "rw_utils.h"
#include "rw_dff_structure.h"

/* Extracts version info from given DWORD */
uint_32 RwUtils::unpackLibraryVersion(uint_32 libid) {
	if (libid & 0xFFFF0000) {
		return (libid >> 14 & 0x3FF0) + 0x30000 | (libid >> 16 & 0x3F);
	}
	return libid << 8;
}

/* Reads BYTE from given array within given offset (LittleEndian) */
uint_8 RwUtils::readByteFromArrayLE(uint_8* buffer, size_t &ptr_pos) {
	return buffer[ptr_pos++];
}

/* Reads WORD from given array within given offset (LittleEndian) */
uint_16 RwUtils::readWordFromArrayLE(uint_8* buffer, size_t &ptr_pos) {
	uint_16 res = (buffer[ptr_pos + 1] << 8) + (buffer[ptr_pos]);
	ptr_pos += sizeof(uint_16);
	return res;
}

/* Reads DWORD from given array within given offset (LittleEndian) */
uint_32 RwUtils::readDwordFromArrayLE(uint_8* buffer, size_t &ptr_pos) {
	uint_32 res = (buffer[ptr_pos + 3] << 24) + (buffer[ptr_pos + 2] << 16) + (buffer[ptr_pos + 1] << 8) + (buffer[ptr_pos]);
	ptr_pos += sizeof(uint_32);
	return res;
}

/* Reads 4 byte float from given array within given offset (LittleEndian) */
float_32 RwUtils::readFloatFromArrayLE(uint_8* buffer, size_t &ptr_pos) {
	float_32 res;
	memcpy(&res, buffer + ptr_pos, sizeof(float_32));
	ptr_pos += sizeof(float_32);
	return res;
}

/* Copies given chunk of memory to a new array and returns this array */
uint_8* RwUtils::readData(uint_8* buffer, size_t &ptr_pos, size_t dataSize) {
	uint_8* arr = new uint_8[dataSize];

	for (int i = 0; i < dataSize; ++i) {
		arr[i] = buffer[i + ptr_pos];
	}
	ptr_pos += dataSize;
	return arr;
}

std::string RwUtils::readString(uint_8* buffer, size_t &ptr_pos, size_t dataSize) {
	std::string s;
	for (size_t i = ptr_pos; i < ptr_pos + dataSize; i++) {
		s += (char)buffer[i];
	}
	ptr_pos += dataSize;
	return s;
}

/* Converts enum type to string */
std::string RwUtils::getSectionTypeName(uint_32 type) {
	switch (type) {
	case rwDATA:
		return "rwDATA";
	case rwSTRING:
		return "rwSTRING";
	case rwEXTENSION:
		return "rwEXTENSION";
	case rwTEXTURE:
		return "rwTEXTURE";
	case rwMATERIAL:
		return "rwMATERIAL";
	case rwMATERIALLIST:
		return "rwMATERIALLIST";
	case rwFRAMELIST:
		return "rwFRAMELIST";
	case rwGEOMETRY:
		return "rwGEOMETRY";
	case rwCLUMP:
		return "rwCLUMP";
	case rwATOMIC:
		return "rwATOMIC";
	case rwTEXTURENATIVE:
		return "rwTEXTURENATIVE";
	case rwTEXTUREDICTIONARY:
		return "rwTEXTUREDICTIONARY";
	case rwGEOMETRYLIST:
		return "rwGEOMETRYLIST";
	case rwMATERIALSPLIT:
		return "rwMATERIALSPLIT";
	case rwFRAME:
		return "rwFRAME";
	default:
		return "rwUNKNOWN";
	}
}

std::string RwUtils::getVersion(uint_32 type, bool includeGameVersion) {
	switch (type) {
	case rwVERSION_30002:
		return std::string("3.0.0.0.2")	+ std::string((includeGameVersion) ? " GTA3 (Alpha PS2)" : "");
	case rwVERSION_30004:
		return std::string("3.0.0.0.4") + std::string((includeGameVersion) ? " GTA3 (PS2)" : "");
	case rwVERSION_300010:
		return std::string("3.0.0.0.10") + std::string((includeGameVersion) ? " GTA3 (PS2/WIN)" : "");
	case rwVERSION_3200:
		return std::string("3.2.0.0") + std::string((includeGameVersion) ? " GTA3 (WIN)" : "");
	case rwVERSION_3302:
		return std::string("3.3.0.2") + std::string((includeGameVersion) ? " GTAVC (WIN)" : "");
	case rwVERSION_3403:
		return std::string("3.4.0.3") + std::string((includeGameVersion) ? " GTA3/VC (XBOX)" : "");
	case rwVERSION_3405:
		return std::string("3.4.0.5") + std::string((includeGameVersion) ? " GTAVC (Android)" : "");
	case rwVERSION_3500:
		return std::string("3.5.0.0") + std::string((includeGameVersion) ? " GTAIII (Android)" : "");
	case rwVERSION_3603:
		return std::string("3.6.0.3") + std::string((includeGameVersion) ? " GTASA" : "");
	}
}

void RwUtils::printBracet(IOBracets bracet, size_t levelSpacing) {
	printLevelSpacing(levelSpacing);
	switch (bracet) {
	case ioOPEN:
		std::cout << "{\n";
		break;
	case ioCLOSE:
		std::cout << "}\n";
	default:
		std::cout << "\n";
		break;
	}
}

void RwUtils::printLevelSpacing(int level) {
	for (int i = 0; i < 4 * level; i++) {
		std::cout << " ";
	}
}

void RwUtils::printVoidStructure(int level) {
	printBracet(ioOPEN, level);
	printLevelSpacing(level + 1);
	std::cout << rw_io_colors::blue << "READING OF THIS PART IS NOT IMPLEMENTED" << rw_io_colors::white << std::endl;
	printBracet(ioCLOSE, level);
}

void RwUtils::printPointerPosition(int ptr_pos) {
	std::cout << "ptr_pos = " << rw_io_colors::green << ptr_pos << rw_io_colors::white << std::endl << std::endl;
}

template<typename T>
void RwUtils::printVarType() {
	std::cout << rw_io_colors::yellow << typeid(T).name() << " " << rw_io_colors::white;
}

template<typename T>
void RwUtils::printDecVariable(char* varName, T var, size_t levelSpacing) {
	printLevelSpacing(levelSpacing);
	printVarType<T>();
	std::cout << varName << " = " << var << std::dec << "\n";
}

template<typename T>
void RwUtils::printHexVariable(char* varName, T var, size_t levelSpacing) {
	printLevelSpacing(levelSpacing);
	printVarType<T>();
	std::cout << varName << " = " << std::hex << "0x" << var << std::dec << "\n";
}

void RwUtils::printStringVariable(char* varName, std::string var, size_t levelSpacing) {
	printLevelSpacing(levelSpacing);
	printVarType<std::string>();
	std::cout << varName << " = " << var << "\n";
}

template<typename ...T>
void RwUtils::printArrayElement(char* arrLabel, size_t elementNum, size_t levelSpacing, T... args) {
	printLevelSpacing(levelSpacing);
	std::cout << arrLabel << "[" << rw_io_colors::blue << elementNum << rw_io_colors::white << "] = <";
	std::array<T, sizeof...(T)> const array = { args... };
	for (const auto elem : array) {
		std::cout << elem << "/";
	}
	std::cout << ">" << std::endl;
}

void RwUtils::printFileInfo(RwFile *rwFile) {
	std::cout << "File: " << rw_io_colors::green << rwFile->getFileName() << rw_io_colors::white << std::endl;
	std::cout << "Size: " << rw_io_colors::green << rwFile->getFileSize() << rw_io_colors::white << " bytes" << std::endl;
}

void RwUtils::printHeaderInfo(RwSectionHeader &header, int level) {
	printLevelSpacing(level);
	std::cout << rw_io_colors::red << RwUtils::getSectionTypeName(header.sectionType) << rw_io_colors::white << " <";
	std::cout << rw_io_colors::blue << header.sectionSize << rw_io_colors::white << " bytes / ";
	std::cout << RwUtils::getVersion(header.versionNumber, true) << ">:\n";
}

void RwUtils::printClumpDataStruct(RwClumpData &clumpDataStruct, int level) {
	printBracet(ioOPEN, level);
	printDecVariable("objectCount", clumpDataStruct.objectCount, ++level);
	printDecVariable("unk1", clumpDataStruct.unk1, level);
	printDecVariable("unk2", clumpDataStruct.unk2, level);
	printBracet(ioCLOSE, --level);
}

void RwUtils::printFrameListData(RwFrameListData &frameListData, int level) {
	printBracet(ioOPEN, level);
	printDecVariable("frameCount", frameListData.frameCount, ++level);

	for (int i = 0; i < frameListData.frameCount; i++) {
		printLevelSpacing(level + 2);
		std::cout << "frameInformation[" << i << "]:" << std::endl;
		printBracet(ioOPEN, level + 2);

		printLevelSpacing(level + 3);
		printVarType<decltype(frameListData.frameInformation[i].rotationalMatrix)>();
		std::cout << "rotationalMatrix[3][3] = { ";

		for (int j = 0; j < frameListData.ROT_MAT_DIM / 3; j++) {
			std::cout << "{";
			for (int k = 0; k < frameListData.ROT_MAT_DIM / 3; k++) {
				std::cout << frameListData.frameInformation[i].rotationalMatrix[j * 3 + k];
				std::cout << (k < 2 ? ", " : "");
			}
			std::cout << (j < 2 ? "}, " : "} }");
		}

		std::cout << std::endl;
		printDecVariable("coordinatesOffsetX", frameListData.frameInformation[i].coordinatesOffsetX, level + 3);
		printDecVariable("coordinatesOffsetY", frameListData.frameInformation[i].coordinatesOffsetY, level + 3);
		printDecVariable("coordinatesOffsetZ", frameListData.frameInformation[i].coordinatesOffsetZ, level + 3);
		printDecVariable("parentFrame", frameListData.frameInformation[i].parentFrame, level + 3);
		printDecVariable("unk1", frameListData.frameInformation[i].unk1, level + 3);
		printBracet(ioCLOSE, level + 2);
	}
	printBracet(ioCLOSE, --level);
}

void RwUtils::printGeometryListData(RwGeometryListData &gld, int level) {
	printBracet(ioOPEN, level);
	printDecVariable("geometryCount", gld.geometryCount, ++level);
	printBracet(ioCLOSE, --level);
}

void RwUtils::printGeometryData(RwGeometryData &gd, int level) {
	printBracet(ioOPEN, level);
	printHexVariable("flags", gd.dataHeader.flags, ++level);
	printDecVariable("unk1", gd.dataHeader.unk1, level);
	printDecVariable("triangleCount", gd.dataHeader.triangleCount, level);
	printDecVariable("vertexCount", gd.dataHeader.vertexCount, level);
	printDecVariable("morphTargetCount", gd.dataHeader.morphTargetCount, level);

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_PRELIT) {
		printLevelSpacing(level++);
		std::cout << "[colorInformation]:\n";
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			printLevelSpacing(level);
			std::cout << "<R/G/B/A>[" << rw_io_colors::blue << i << rw_io_colors::white << "] = <" << (int)gd.colorInformation[i].red << "/" << (int)gd.colorInformation[i].green << "/" << (int)gd.colorInformation[i].blue << "/" << (int)gd.colorInformation[i].alpha << ">\n";
		}
		level--;
		std::cout << "\n";
	}

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_TEXTURED) {
		printLevelSpacing(level++);
		std::cout << "[textureMappingInformation]:\n";
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			printLevelSpacing(level);
			std::cout << "<u/v>[" << rw_io_colors::blue << i << rw_io_colors::white << "] = <" << ((float_32)gd.textureMappingInformation[i].u) << "/" << ((float_32)gd.textureMappingInformation[i].v) << ">\n";
		}
		level--;
		std::cout << "\n";
	}

	printLevelSpacing(level++);
	std::cout << "[faceInformation]:\n";
	for (int i = 0; i < gd.dataHeader.triangleCount; i++) {
		printLevelSpacing(level);
		std::cout << "<v2/v1/f/v3>[" << rw_io_colors::blue << i << rw_io_colors::white << "] = <" << ((int)gd.faceInformation[i].vertex2) << "/" << ((int)gd.faceInformation[i].vertex1) << "/" << ((int)gd.faceInformation[i].flags) << "/" << ((int)gd.faceInformation[i].vertex3) << ">\n";
	}
	level--;
	std::cout << "\n";

	printDecVariable("boundingSphereX", gd.nonameInfo.boundingSphereX, level);
	printDecVariable("boundingSphereY", gd.nonameInfo.boundingSphereY, level);
	printDecVariable("boundingSphereZ", gd.nonameInfo.boundingSphereZ, level);
	printDecVariable("boundingSphereR", gd.nonameInfo.boundingSphereR, level);
	printDecVariable("hasPosition", gd.nonameInfo.hasPosition, level);
	printDecVariable("hasNormals", gd.nonameInfo.hasNormals, level);

	std::cout << "\n";
	printLevelSpacing(level);
	std::cout << "[vertexInformation]:\n";

	for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
		printLevelSpacing(level + 1);
		std::cout << "<x/y/z>[" << rw_io_colors::blue << i << rw_io_colors::white << "] = <" << (float_32)gd.vertexInformation[i].x << "/" << (float_32)gd.vertexInformation[i].y << "/" << (float_32)gd.vertexInformation[i].z << ">\n";
	}
	std::cout << "\n";

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_NORMALS) {
		printLevelSpacing(level);
		std::cout << "[normalInformation]:\n";
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			printLevelSpacing(level + 1);
			std::cout << "<x/y/z>[" << rw_io_colors::blue << i << rw_io_colors::white << "] = <" << (float_32)gd.normalInformation[i].x << "/" << (float_32)gd.normalInformation[i].y << "/" << (float_32)gd.normalInformation[i].z << ">\n";
			//printArrayElement("<x/y/z>", i, level + 1, (float_32)gd.normalInformation[i].x, (float_32)gd.normalInformation[i].y, (float_32)gd.normalInformation[i].z);
		}
	}
	printBracet(ioCLOSE, --level);
}

void RwUtils::printMaterialListData(RwMaterialListData &mld, int level) {
	printBracet(ioOPEN, level++);
	printDecVariable("materialCount", mld.materialCount, level);
	printLevelSpacing(level);
	std::cout << "[arrayOfUnks]:\n";
	for (int i = 0; i < mld.materialCount; i++) {
		printLevelSpacing(level + 1);
		std::cout << "[" << rw_io_colors::blue << i << rw_io_colors::white << "] = " << (int)mld.arrayOfUnks[i] << "\n";
	}
	printBracet(ioCLOSE, --level);
}

void RwUtils::printMaterialData(RwMaterialData &md, int level) {
	printBracet(ioOPEN, level++);
	printDecVariable("unk1", md.unk1, level);
	printDecVariable("R", (short)md.R, level);
	printDecVariable("G", (short)md.G, level);
	printDecVariable("B", (short)md.B, level);
	printDecVariable("A", (short)md.A, level);
	printDecVariable("unk2", md.unk2, level);
	printDecVariable("textureCount", md.textureCount, level);
	printDecVariable("unkPosX", md.unkPosX, level);
	printDecVariable("unkPosY", md.unkPosY, level);
	printDecVariable("unkPosZ", md.unkPosZ, level);
	printBracet(ioCLOSE, --level);
}

void RwUtils::printTextureData(RwTextureData &td, int level) {
	printBracet(ioOPEN, level++);
	printHexVariable("textureFilterModeFlags", td.textureFilterModeFlags, level);
	printDecVariable("unk", td.unk, level);
	printBracet(ioCLOSE, --level);
}

void RwUtils::printStringData(RwString &str, int level) {
	printBracet(ioOPEN, level++);
	char* text = (char*)(str.text.c_str());
	printStringVariable("text", text, level);
	printBracet(ioCLOSE, --level);
}