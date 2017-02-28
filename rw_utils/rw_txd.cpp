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
		readTextureNativeData(this->texDictionary.textures[i].data, this->data, ptr_pos);
		ptr_pos += this->texDictionary.textures[i].data.sectionSize;

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
		RwUtils::printVoidStructure(level + 1);
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
	tnd.textureFormat.uAddressing = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.textureFormat.vAddressing = RwUtils::readByteFromArrayLE(buffer, ptr_pos);
	tnd.textureFormat.pad = RwUtils::readWordFromArrayLE(buffer, ptr_pos);

	// TODO: Read rest of file; figure out how to read texture and alpha names
}