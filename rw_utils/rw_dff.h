/*		rw_dff.h	Written by Marek Iwaniuk (c).
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/03/2017 (MM/DD/YYYY)
*/

#pragma once

#ifndef RW_DFF
#define RW_DFF

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "basic_types.h"
#include "rw_utils.h"
#include "rw_dff_structure.h"
#include "rw_file.h"


class RwDff : public RwFile {
public:
	RwDff(std::string fileName);
	~RwDff();
	void			serialize();
	void			printFileStructure();
	std::vector<Vec3<float> >		getVertexInformation();
	std::vector<Vec3PlusFlag<int> > getFaceInformation();
	std::vector<Vec2<int> >			getTextureMappingInformation();
	std::vector<Vec3<float> >		getNormalInformation();
	std::vector<ColorRGBA>			getColorInformation();
private:
	RwClump*		clumps;
	
	/* --- Reading functions --- */
	void			readSectionHeader(RwSectionHeader &sh, uint_8* buffer, size_t &ptr_pos);
	void			readFrameListData(RwFrameListData &frd, uint_8* buffer, size_t &ptr_pos);
	void			readClumpData(RwClumpData &cd, uint_8* buffer, size_t &ptr_pos);
	void			readGeometryListData(RwGeometryListData &gld, uint_8* buffer, size_t &ptr_pos);
	void			readGeometryData(RwGeometryData &gd, uint_8* buffer, size_t &ptr_pos);
	void			readMaterialListData(RwMaterialListData &mld, uint_8* buffer, size_t &ptr_pos);
	void			readMaterialData(RwMaterialData &md, uint_8* buffer, size_t &ptr_pos);
	void			readTextureData(RwTextureData &td, uint_8* buffer, size_t &ptr_pos);
	void			readStringData(RwString &s, uint_8* buffer, size_t &ptr_pos);
};

#endif

