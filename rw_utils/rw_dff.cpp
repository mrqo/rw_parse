/*		rw_dff.cpp	Written by Marek Iwaniuk (c).
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/03/2017 (MM/DD/YYYY)
*/

#include "stdafx.h"

#include "rw_dff.h"

RwDff::RwDff(std::string fileName) : RwFile(fileName) {
	this->clumps = new RwClump[1];
}

RwDff::~RwDff() {
	delete[] this->data;
	for (int i = 0; i < this->clumps[0].frameList.data.frameCount; i++) {
		
		delete[] this->clumps[0].frameList.data.frameInformation[i].rotationalMatrix;
	}
	delete[] this->clumps[0].frameList.data.frameInformation;
	delete[] this->clumps[0].frameList.extensions;
}

void RwDff::serialize() {
	size_t ptr_pos = 0;
	readSectionHeader(this->clumps[0], this->data, ptr_pos);
	readSectionHeader(this->clumps[0].data, this->data, ptr_pos);
	readClumpData(this->clumps[0].data, this->data, ptr_pos);
	readSectionHeader(this->clumps[0].frameList, this->data, ptr_pos);
	readSectionHeader(this->clumps[0].frameList.data, this->data, ptr_pos);
	readFrameListData(this->clumps[0].frameList.data, this->data, ptr_pos);

	this->clumps[0].frameList.extensions = new RwFrameListExtension[this->clumps[0].frameList.data.frameCount];
	for (int i = 0; i < this->clumps[0].frameList.data.frameCount; i++) {
		readSectionHeader(this->clumps[0].frameList.extensions[i], this->data, ptr_pos);
		ptr_pos += this->clumps[0].frameList.extensions[i].sectionSize;
	}
	
	readSectionHeader(this->clumps[0].geometryList, this->data, ptr_pos);
	readSectionHeader(this->clumps[0].geometryList.data, this->data, ptr_pos);
	readGeometryListData(this->clumps[0].geometryList.data, this->data, ptr_pos);
	
	this->clumps[0].geometryList.geometries = new RwGeometry[this->clumps[0].geometryList.data.geometryCount];

	for (int i = 0; i < this->clumps[0].geometryList.data.geometryCount; i++) {
		readSectionHeader(this->clumps[0].geometryList.geometries[i], this->data, ptr_pos);
		readSectionHeader(this->clumps[0].geometryList.geometries[i].data, this->data, ptr_pos);
		readGeometryData(this->clumps[0].geometryList.geometries[i].data, this->data, ptr_pos);

		readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList, this->data, ptr_pos);
		readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.data, this->data, ptr_pos);
		readMaterialListData(this->clumps[0].geometryList.geometries[i].materialList.data, this->data, ptr_pos);

		int materialCount = this->clumps[0].geometryList.geometries[i].materialList.data.materialCount;
		this->clumps[0].geometryList.geometries[i].materialList.materials = new RwMaterial[materialCount];
		for (int j = 0; j < materialCount; j++) {
			readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j], this->data, ptr_pos);
			readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].data, this->data, ptr_pos);
			readMaterialData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].data, this->data, ptr_pos);

			int textureCount = this->clumps[0].geometryList.geometries[i].materialList.materials[j].data.textureCount;
			this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures = new RwTexture[textureCount];
			for (int k = 0; k < textureCount; k++) {
				readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k], this->data, ptr_pos);
				readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].data, this->data, ptr_pos);
				readTextureData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].data, this->data, ptr_pos);

				readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureName, this->data, ptr_pos);
				readStringData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureName, this->data, ptr_pos);
				readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureAlphaName, this->data, ptr_pos);
				readStringData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureAlphaName, this->data, ptr_pos);
				
				// The content of extension is Sky Mipmap Val
				readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].extension, this->data, ptr_pos);
				ptr_pos += this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].extension.sectionSize;
			}
			// Probably always void extension
			readSectionHeader(this->clumps[0].geometryList.geometries[i].materialList.materials[j].extension, this->data, ptr_pos);
			ptr_pos += this->clumps[0].geometryList.geometries[i].materialList.materials[j].extension.sectionSize;
		}
		// For Bin Mesh aka Material split
		readSectionHeader(this->clumps[0].geometryList.geometries[i].extension, this->data, ptr_pos);
		ptr_pos += this->clumps[0].geometryList.geometries[i].extension.sectionSize;
	}

	readSectionHeader(this->clumps[0].atomic, this->data, ptr_pos);
	readSectionHeader(this->clumps[0].atomic.data, this->data, ptr_pos);
	ptr_pos += this->clumps[0].atomic.data.sectionSize;
}

void RwDff::printFileStructure() {
	int level = 0;
	RwUtils::printFileInfo(this);
	RwUtils::printHeaderInfo(this->clumps[0], level);
	RwUtils::printHeaderInfo(this->clumps[0].data, ++level);
	RwUtils::printClumpDataStruct(this->clumps[0].data, level);
	RwUtils::printHeaderInfo(this->clumps[0].frameList, level);
	RwUtils::printHeaderInfo(this->clumps[0].frameList.data, ++level);
	RwUtils::printFrameListData(this->clumps[0].frameList.data, level);

	for (int i = 0; i < this->clumps[0].frameList.data.frameCount; i++) {
		RwUtils::printHeaderInfo(this->clumps[0].frameList.extensions[i], level);
		RwUtils::printVoidStructure(level);
	}

	RwUtils::printHeaderInfo(this->clumps[0].geometryList, --level);
	RwUtils::printHeaderInfo(this->clumps[0].geometryList.data, ++level);
	RwUtils::printGeometryListData(this->clumps[0].geometryList.data, level);

	for (int i = 0; i < this->clumps[0].geometryList.data.geometryCount; i++) {
		RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i], level);
		RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].data, ++level);
		RwUtils::printGeometryData(this->clumps[0].geometryList.geometries[i].data, level);
		RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList, level);
		RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.data, ++level);
		RwUtils::printMaterialListData(this->clumps[0].geometryList.geometries[i].materialList.data, level);

		for (int j = 0; j < this->clumps[0].geometryList.geometries[i].materialList.data.materialCount; j++) {
			RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j], level);
			RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j].data, ++level);
			RwUtils::printMaterialData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].data, level);
			for (int k = 0; k < this->clumps[0].geometryList.geometries[i].materialList.materials[j].data.textureCount; k++) {
				RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k], level);
				RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].data, ++level);
				RwUtils::printTextureData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].data, level);
				RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureName, level);
				RwUtils::printStringData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureName, level);
				RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureAlphaName, level);
				RwUtils::printStringData(this->clumps[0].geometryList.geometries[i].materialList.materials[j].textures[k].textureAlphaName, level);
				level--;
			}
			level--;
		}
		RwUtils::printHeaderInfo(this->clumps[0].geometryList.geometries[i].extension, level);
		RwUtils::printVoidStructure(level);
		level--;
	}
	level--;

	RwUtils::printHeaderInfo(this->clumps[0].atomic, --level);
	RwUtils::printVoidStructure(level);
}

void RwDff::readSectionHeader(RwSectionHeader &sh, uint_8* buffer, size_t &ptr_pos) {
	sh.sectionType = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	sh.sectionSize = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	sh.versionNumber = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
}

void RwDff::readFrameListData(RwFrameListData &frd, uint_8* buffer, size_t &ptr_pos) {
	frd.frameCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	using FIChunk = std::remove_reference<decltype(*frd.frameInformation)>::type;
	frd.frameInformation = new FIChunk[frd.frameCount];

	for (int i = 0; i < frd.frameCount; i++) {
		frd.frameInformation[i].rotationalMatrix = new float_32[frd.ROT_MAT_DIM];
		for (int j = 0; j < frd.ROT_MAT_DIM; j++) {
			frd.frameInformation[i].rotationalMatrix[j] = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		}
		frd.frameInformation[i].coordinatesOffsetX = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		frd.frameInformation[i].coordinatesOffsetY = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		frd.frameInformation[i].coordinatesOffsetZ = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		frd.frameInformation[i].parentFrame = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
		frd.frameInformation[i].unk1 = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	}
}

void RwDff::readClumpData(RwClumpData &cd, uint_8* buffer, size_t &ptr_pos) {
	cd.objectCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	cd.unk1 = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	cd.unk2 = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
}

void RwDff::readGeometryListData(RwGeometryListData &gld, uint_8* buffer, size_t &ptr_pos) {
	gld.geometryCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
}

void RwDff::readGeometryData(RwGeometryData &gd, uint_8* buffer, size_t &ptr_pos) {
	gd.dataHeader.flags = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	gd.dataHeader.unk1 = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	gd.dataHeader.triangleCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	gd.dataHeader.vertexCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	gd.dataHeader.morphTargetCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);

	if (false) { // version equals 4099 according to old documentation, disabled as for now
		gd.lightingHeader.ambient = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
		gd.lightingHeader.diffuse = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
		gd.lightingHeader.specular = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	}

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_PRELIT) {
		using CIChunk = std::remove_reference<decltype(*gd.colorInformation)>::type;
		gd.colorInformation = new CIChunk[gd.dataHeader.vertexCount];
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			gd.colorInformation[i].red = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
			gd.colorInformation[i].green = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
			gd.colorInformation[i].blue = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
			gd.colorInformation[i].alpha = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
		}
	}

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_TEXTURED) {
		using TMIChunk = std::remove_reference<decltype(*gd.textureMappingInformation)>::type;
		gd.textureMappingInformation = new TMIChunk[gd.dataHeader.vertexCount];
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			gd.textureMappingInformation[i].u = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
			gd.textureMappingInformation[i].v = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		}
	}

	using FIChunk = std::remove_reference<decltype(*gd.faceInformation)>::type;
	gd.faceInformation = new FIChunk[gd.dataHeader.triangleCount];
	for (int i = 0; i < gd.dataHeader.triangleCount; i++) {
		gd.faceInformation[i].vertex2 = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
		gd.faceInformation[i].vertex1 = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
		gd.faceInformation[i].flags = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
		gd.faceInformation[i].vertex3 = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	}

	gd.nonameInfo.boundingSphereX = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	gd.nonameInfo.boundingSphereY = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	gd.nonameInfo.boundingSphereZ = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	gd.nonameInfo.boundingSphereR = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	gd.nonameInfo.hasPosition = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	gd.nonameInfo.hasNormals = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);

	using VIChunk = std::remove_reference<decltype(*gd.vertexInformation)>::type;
	gd.vertexInformation = new VIChunk[gd.dataHeader.vertexCount];
	for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
		gd.vertexInformation[i].x = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		gd.vertexInformation[i].y = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		gd.vertexInformation[i].z = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	}

	if (gd.dataHeader.flags & rwOBJECT_VERTEX_NORMALS) {
		using NIChunk = std::remove_reference<decltype(*gd.normalInformation)>::type;
		gd.normalInformation = new NIChunk[gd.dataHeader.vertexCount];
		for (int i = 0; i < gd.dataHeader.vertexCount; i++) {
			gd.normalInformation[i].x = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
			gd.normalInformation[i].y = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
			gd.normalInformation[i].z = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
		}
	}
}

void RwDff::readMaterialListData(RwMaterialListData &mld, uint_8* buffer, size_t &ptr_pos) {
	mld.materialCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	mld.arrayOfUnks = new uint_32[mld.materialCount];
	for (int i = 0; i < mld.materialCount; i++) {
		mld.arrayOfUnks[i] = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	}
}

void RwDff::readMaterialData(RwMaterialData &md, uint_8* buffer, size_t &ptr_pos) {
	md.unk1 = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	md.R = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	md.G = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	md.B = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	md.A = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	md.unk2 = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	md.textureCount = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	md.unkPosX = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	md.unkPosY = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
	md.unkPosZ = RwUtils::readFloatFromArrayLE(buffer, ptr_pos);
}

void RwDff::readTextureData(RwTextureData &td, uint_8* buffer, size_t &ptr_pos) {
	td.textureFilterModeFlags = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	td.unk = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
}

void RwDff::readStringData(RwString &s, uint_8* buffer, size_t &ptr_pos) {
	s.text = RwUtils::readString(buffer, ptr_pos, s.sectionSize);
}