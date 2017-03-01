#include "stdafx.h"
#include "rw_txd.h"

RwTxd::RwTxd(std::string fileName) : RwFile(fileName) {
	//this->texDictionary = new RwTextureDictionary();
}

RwTxd::~RwTxd() {
	//delete this->texDictionary;
}

void RwTxd::serialize() { // implemented for SA PC
	size_t ptr_pos = 0;
	readSectionHeader(this->texDictionary, this->data, ptr_pos);
	readSectionHeader(this->texDictionary.data, this->data, ptr_pos);
	readTextureDictionaryData(this->texDictionary.data, this->data, ptr_pos);

	this->texDictionary.textures = new RwTextureNative[this->texDictionary.data.rwNewer.textureCount];
	for (int i = 0; i < this->texDictionary.data.rwNewer.textureCount; i++) {
		readSectionHeader(this->texDictionary.textures[i], this->data, ptr_pos);
		readSectionHeader(this->texDictionary.textures[i].data, this->data, ptr_pos);
		size_t offset = ptr_pos;
		readTextureNativeData(this->texDictionary.textures[i].data, this->data, ptr_pos);
		ptr_pos = offset + this->texDictionary.textures[i].data.sectionSize;

		readSectionHeader(this->texDictionary.textures[i].extension, this->data, ptr_pos);
		ptr_pos += this->texDictionary.textures[i].extension.sectionSize;
	}

	readSectionHeader(this->texDictionary.extension, this->data, ptr_pos);
	ptr_pos += this->texDictionary.extension.sectionSize;
}

void RwTxd::printFileStructure() {
	int level = 0;
	RwUtils::printFileInfo(this);
	RwUtils::printHeaderInfo(this->texDictionary, level);
	RwUtils::printHeaderInfo(this->texDictionary.data, ++level);
	RwUtils::printTextureDictionaryData(this->texDictionary.data, level);

	for (int i = 0; i < this->texDictionary.data.rwNewer.textureCount; i++) {
		RwUtils::printHeaderInfo(this->texDictionary.textures[i], level);

		RwUtils::printHeaderInfo(this->texDictionary.textures[i].data, level + 1);
		RwUtils::printTextureNativeData(this->texDictionary.textures[i].data, level + 1);
		RwUtils::printHeaderInfo(this->texDictionary.textures[i].extension, level + 1);
		RwUtils::printVoidStructure(level + 1);
	}

	RwUtils::printHeaderInfo(this->texDictionary.extension, level);
	RwUtils::printVoidStructure(level);
}

void RwTxd::readTextureDictionaryData(RwTextureDictionaryData& tdd, uint_8* buffer, size_t& ptr_pos) {
	// Implemented for San Andreas
	tdd.rwNewer.textureCount = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	tdd.rwNewer.deviceId = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
}

void RwTxd::readTextureNativeData(RwTextureNativeData& tnd, uint_8* buffer, size_t& ptr_pos) {
	tnd.textureFormat.platformId = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	tnd.textureFormat.filterMode = RwUtils::readByteFromArrayLE(buffer, ptr_pos);

	// I don't know if it is the right order
	uint_8 uvAddressing = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.textureFormat.uAddressing = (uvAddressing & ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4))) >> 4;
	tnd.textureFormat.vAddressing = uvAddressing & ((1 << 3) | (1 << 3) | (1 << 1) | (1 << 0));
	
	tnd.textureFormat.pad = RwUtils::readWordFromArrayLE(buffer, ptr_pos);

	strcpy(tnd.textureFormat.name, (char*)RwUtils::readString(buffer, ptr_pos, 32).c_str());
	strcpy(tnd.textureFormat.maskName, (char*)RwUtils::readString(buffer, ptr_pos, 32).c_str());

	tnd.rasterFormat.rasterFormat = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.d3dFormat = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.width = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.height = RwUtils::readWordFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.depth = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.numLevels = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.rasterType = RwUtils::readByteFromArrayLE(buffer, ptr_pos);

	uint_8 flags = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.rasterFormat.alpha = (flags & (1 << 7)) >> 7;
	tnd.rasterFormat.cubeTexture = (flags & (1 << 6)) >> 6;
	tnd.rasterFormat.autoMipMaps = (flags & (1 << 5)) >> 5;
	tnd.rasterFormat.isNotRwCompatible = (flags & (1 << 4)) >> 4;
	tnd.rasterFormat.pad = flags & ((1 << 3) | (1 << 2) | (1 << 1) | (1));
}