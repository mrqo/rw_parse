/*		rw_file.h	Written by Marek Iwaniuk (c).
 *		Created on 02/07/2017 (MM/DD/YYYY)
 */

#pragma once

#ifndef RW_FILE
#define RW_FILE

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "rw_types.h"
#include "rw_core.h"
#include "rw_utils.h"

class RwFile {
public:
	RwFile(std::string fileName);
	~RwFile();

	virtual bool	openFile();
	virtual void	loadFile();
	size_t			getFileSize();
	std::string		getFileName();
	
protected:
	std::string		fileName;
	size_t			fileSize;
	uint_8			*data;
	FILE			*p_File;

	void			readSectionHeader(RwSectionHeader &sh, uint_8* buffer, size_t& ptr_pos);
};

#endif