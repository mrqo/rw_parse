#include "stdafx.h"

#include "rw_ide.h"
#include <iostream>
#include <stdio.h>

RwIde::RwIde(std::string fileName) : RwFile(fileName) { }

RwIde::~RwIde() {

}

bool RwIde::openFile() {
	this->p_File = fopen((char*)fileName.c_str(), "r");
	if (!this->p_File) {
		return false;
	}
	return true;
}

void RwIde::loadFile() {
	
}

void RwIde::serialize() {
	std::cout << "Todo: Serialize IDE..." << std::endl;
	bool loopSerialization = true;

	// Todo: serialize IDE file

	char buff[1000];
	while (fgets(buff, 1000, p_File)) {
		printf("%s", buff);
	}
}