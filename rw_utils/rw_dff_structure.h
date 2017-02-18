/*		rw_dff_structure.h	Written by Marek Iwaniuk (c).
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/07/2017 (MM/DD/YYYY)
*/

#pragma once

#ifndef RW_DFF_STRUCTURE
#define RW_DFF_STRUCTURE

#include "rw_types.h"
#include "rw_core.h"

enum RwSectionType : uint_32 {
	rwDATA			= 1,
	rwSTRING		= 2,
	rwEXTENSION		= 3,
	rwTEXTURE		= 6,
	rwMATERIAL		= 7,
	rwMATERIALLIST	= 8,
	rwFRAMELIST		= 14,
	rwGEOMETRY		= 15,
	rwCLUMP			= 16,
	rwATOMIC		= 20,
	rwGEOMETRYLIST	= 26,
	rwMATERIALSPLIT = 1294,
	rwFRAME			= 39056126
};

enum RwGeometryDataFlags : uint_16 {
	rwOBJECT_VERTEX_TRISTRIP				= 0x01,
	rwOBJECT_VERTEX_POS						= 0x02,
	rwOBJECT_VERTEX_TEXTURED				= 0x04,
	rwOBJECT_VERTEX_PRELIT					= 0x08,
	rwOBJECT_VERTEX_NORMALS					= 0x10,
	rwOBJECT_VERTEX_LIGHT					= 0x20,
	rwOBJECT_VERTEX_MODULATE_MATERIAL_COLOR = 0x40,
	rwOBJECT_VERTEX_TEXTURED_2				= 0x80
};

// SectionHeader
class RwSectionHeader {
public:
	uint_32 sectionType;
	uint_32 sectionSize;
	uint_32 versionNumber;
};
// --- 

// Section: Frame List
class RwFrameListData : public RwSectionHeader {
public:
	const size_t		ROT_MAT_DIM = 9;
	uint_32				frameCount;

	class RwFrameListChunk {
	public:
		float_32*	rotationalMatrix;	// [ROT_MAT_DIM]
		float_32	coordinatesOffsetX;
		float_32	coordinatesOffsetY;
		float_32	coordinatesOffsetZ;
		uint_32		parentFrame;	// 0xFFFFFFFF = NONE
		uint_32		unk1;
	} *frameInformation;	// [frameCount]
};

class RwFrame : public RwSectionHeader {
public:
	uint_8* frameName;					// [sectionSize] - should be interpreted as string
};

class RwFrameListExtension : public RwSectionHeader {
public:
	RwFrame frame;
};

class RwFrameList : public RwSectionHeader {
public:
	RwFrameListData				data;
	RwFrameListExtension*		extensions;
};
// ---

// Section: Geometry
class RwGeometryData : public RwSectionHeader {
public:
	class RwGeometryDataHeader {
	public:
		uint_16 flags;
		uint_16 unk1;
		uint_32 triangleCount;
		uint_32 vertexCount;
		uint_32 morphTargetCount;
	} dataHeader;

	class RwGeometryDataLightingHeader { // IF versionNumber = 4099 - according to not complete documentation
	public:
		float_32 ambient;
		float_32 diffuse;
		float_32 specular;
	} lightingHeader;


	class RwGeometryDataColorInformationChunk { // if rwOBJECT_VERTEX_PREILIT in flags
	public:
		uint_8 red;
		uint_8 green;
		uint_8 blue;
		uint_8 alpha;
	} *colorInformation; // [vertexCount]

	class RwGeometryDataTextureMappingInformationChunk { // if rwOBJECT_VERTEX_TEXTURED in flags
	public:
		float_32 u;
		float_32 v;
	} *textureMappingInformation; // [vertexCount]

	class RwGeometryDataFaceInformation {
	public:
		uint_16 vertex2; // this 
		uint_16 vertex1; // is
		uint_16 flags;	 // weird
		uint_16 vertex3; // order
	} *faceInformation; // [triangleCount]

	class RwGeometryDataNonameInfo {
	public:
		float_32 boundingSphereX;
		float_32 boundingSphereY;
		float_32 boundingSphereZ;
		float_32 boundingSphereR;
		uint_32 hasPosition;
		uint_32 hasNormals;
	} nonameInfo;

	class RwGeometryDataVertexInformationChunk {
	public:
		float_32 x;
		float_32 y;
		float_32 z;
	} *vertexInformation; // [vertexCount]


	class RwGeometryDataNormalInformationChunk { // if rwOBJECT_VERTEX_NORMAL in flags
	public:
		float_32 x;
		float_32 y;
		float_32 z;
	} *normalInformation; // [vertexCount]
};

class RwMaterialData : public RwSectionHeader {
public:
	uint_32 unk1;
	uint_8 R;
	uint_8 G;
	uint_8 B;
	uint_8 A; // should it be like this???
	uint_32 unk2;
	uint_32 textureCount;
	float_32 unkPosX;
	float_32 unkPosY;
	float_32 unkPosZ;
};

class RwTextureData : public RwSectionHeader {
public:
	uint_16 textureFilterModeFlags;
	uint_16 unk;
};

class RwString : public RwSectionHeader {
public:
	std::string text;
};

class RwTextureExtension : public RwSectionHeader {
	// May contain Sky Mipmap Val
};

class RwTexture : public RwSectionHeader {
public:
	RwTextureData	data;
	RwString		textureName;
	RwString		textureAlphaName;
	RwTextureExtension extension;
};

class RwMaterialExtension : public RwSectionHeader {
	// meant to be void.. don't ask
};

class RwMaterial : public RwSectionHeader {
public:
	RwMaterialData		data;
	RwTexture*			textures;
	RwMaterialExtension extension;
};

class RwMaterialListData : public RwSectionHeader {
public:
	uint_32 materialCount;
	uint_32 *arrayOfUnks; // Filled with '-1's, [materialCount] - it wasn't mentioned in docs.
};

class RwMaterialList : public RwSectionHeader {
public:
	RwMaterialListData	data;
	RwMaterial*			materials;
};

class RwMaterialSplit {
public:
	class Header {
	public:
		uint_32 triangleStrip;
		uint_32 splitCount;
		uint_32 faceCount;
	} header;

	class RwGeometryListInfoChunk {
	public:
		uint_32 faceIndex;
		uint_32 materialIndex;

		class RwGeometryListVertexInfoChunk {
		public:
			uint_32 vertex1;
		} *vertexInformation; // [faceIndex]
	} *splitInformation; // [splitCount]
};

class RwGeometryExtension : public RwSectionHeader {
public:
	RwMaterialSplit materialSplit;
};

class RwGeometry : public RwSectionHeader {
public:
	RwGeometryData		data;
	RwMaterialList		materialList;
	RwGeometryExtension extension;
};
// ---

// Section: Geometry List
class RwGeometryListData : public RwSectionHeader {
public:
	uint_32 geometryCount;
};

class RwGeometryList : public RwSectionHeader {
public:
	RwGeometryListData	data;
	RwGeometry			*geometries;
};
// ---

// Section: Atomic
class RwAtomicData : public RwSectionHeader {
public:
	uint_32 frameNumber;
	uint_32 geometryNumber;
	uint_32 unk1;
	uint_32 unk2;
};

class RwAtomic : public RwSectionHeader {
public:
	RwAtomicData data;
};
// ---

// Section: Clump
class RwClumpData : public RwSectionHeader {
public:
	uint_32 objectCount;
	uint_32 unk1;
	uint_32 unk2;
};

class RwClump : public RwSectionHeader {
public:
	RwClumpData		data;
	RwFrameList		frameList;
	RwGeometryList	geometryList;
	RwAtomic		atomic; //multiple?? but how many
};
// ---

#endif