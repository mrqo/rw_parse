#pragma once

#ifndef RW_TXD
#define RW_TXD

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "basic_types.h"
#include "rw_utils.h"
#include "rw_txd_structure.h"
#include "rw_file.h"

class RwTxd : public RwFile {
public:
	RwTxd(std::string fileName);
	~RwTxd();
	void		serialize();
	void		printFileStructure();
private:
	RwTextureDictionary	texDictionary;

	/*	--- Reading functions --- */
	void		readTextureDictionaryData(RwTextureDictionaryData& tdd, uint_8* buffer, size_t& ptr_pos);
	void		readTextureNativeData(RwTextureNativeData& tnd, uint_8* buffer, size_t& ptr_pos);
};
#endif
