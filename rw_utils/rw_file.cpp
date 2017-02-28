/*		rw_file.cpp 	Written by Marek Iwaniuk (c).
 *		Created on 02/07/2017 (MM/DD/YYYY)
 */

#include "stdafx.h"

#include "rw_file.h"

RwFile::RwFile(std::string fileName) {
	this->fileName = fileName;
}

RwFile::~RwFile() {
	fclose(this->p_File);
}

bool RwFile::openFile() {
	this->p_File = fopen((char*)fileName.c_str(), "rb");

	if (!this->p_File) {
		return false;
	}
	return true;
}

void RwFile::loadFile() {
	fseek(this->p_File, 0L, SEEK_END);
	this->fileSize = ftell(this->p_File);
	this->data = new uint_8[this->fileSize];
	rewind(this->p_File);
	fread(this->data, sizeof(uint_8), this->fileSize, this->p_File);
}

size_t RwFile::getFileSize() {
	return this->fileSize;
}

std::string RwFile::getFileName() {
	return this->fileName;
}

void RwFile::readSectionHeader(RwSectionHeader &sh, uint_8* buffer, size_t& ptr_pos) {
	sh.sectionType = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	sh.sectionSize = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
	sh.versionNumber = RwUtils::readDwordFromArrayLE(buffer, ptr_pos);
}
