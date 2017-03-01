/*		rw_txd_structure.h	Written by Marek Iwaniuk (c).
*		Txd structure documentation https://www.gtamodding.com/wiki/Texture_Native_Struct
*		Created on 25/07/2017 (MM/DD/YYYY)
*/

#pragma once

#ifndef RW_TXD_STRUCTURE
#define RW_TXD_STRUCTURE

#include "rw_types.h"
#include "rw_core.h"

enum RwFilterMode {
	rwFILTER_NONE				= 0x00,
	rwFILTER_NEAREST			= 0x01,
	rwFILTER_LINEAR				= 0x02,
	rwFILTER_MIP_NEAREST		= 0x03,
	rwFILTER_MIP_LINEAR			= 0x04,
	rwFILTER_LINEAR_MIP_NEAREST = 0x05,
	rwFILTER_LINEAR_MIP_LINEAR  = 0x06
};

enum RwAddressingMode {
	rwWRAP_NONE		= 0x00,
	rwWRAP_WRAP		= 0x01,
	rwWRAP_MIRROR	= 0x02,
	rwWRAP_CLAMP	= 0x03
};

enum RwRasterFormat {
	rwFORMAT_DEFAULT	= 0x0000,
	rwFORMAT_1555		= 0x0100,
	rwFORMAT_565		= 0x0200,
	rwFORMAT_4444		= 0x0300,
	rwFORMAT_LUM8		= 0x0400,
	rwFORMAT_8888		= 0x0500,
	rwFORMAT_888		= 0x0600,
	rwFORMAT_555		= 0x0A00,

	rwFORMAT_EXT_AUTO_MIPMAP	= 0x1000,
	rwFORMAT_EXT_PAL8			= 0x2000,
	rwFORMAT_EXT_PAL4			= 0x4000,
	rwFORMAT_EXT_MIPMAP			= 0x8000
};

class RwTextureNativeData : public RwSectionHeader {
public:
	struct {
		uint_32 platformId;
		uint_8	filterMode;
		uint_8	uAddressing : 4;
		uint_8	vAddressing : 4;
		uint_16 pad;
		uchar_8 name[32];
		uchar_8 maskName[32];
	} textureFormat;

	struct {
		uint_32 rasterFormat;

		union {
			uint_32 d3dFormat;	// SA in (D3DFORMAT)
			uint_32 hasAlpha;	// III/VC
		};

		uint_16	width;
		uint_16	height;
		uint_8 depth;
		uint_8 numLevels;
		uint_8 rasterType;

		union {
			uchar_8 compression;	// III/VC

			struct {				// SA
				uint_8 alpha : 1;
				uint_8 cubeTexture : 1;
				uint_8 autoMipMaps : 1;
				uint_8 isNotRwCompatible : 1;
				uint_8 pad : 4;
			};
		};
	} rasterFormat;

};

class RwTextureNativeExtension : public RwSectionHeader {
public:
};

class RwTextureNative : public RwSectionHeader {
public:
	RwTextureNativeData			data;
	RwTextureNativeExtension	extension;
};

class RwTextureDictionaryData : public RwSectionHeader {
public:
	union {
		struct {
			uint_16 textureCount;
			uint_16 deviceId;		// 1 for D3D8, 2 for D3D9, 6 for PlayStation 2, 8 for XBOX
		} rwNewer;

		struct {
			uint_32 textureCount;
		} rwOlder;
	};
};

class RwTextureDictionaryExtension : public RwSectionHeader {
public:
};

class RwTextureDictionary : public RwSectionHeader {
public:
	RwTextureDictionaryData			data;
	RwTextureNative*				textures;
	RwTextureDictionaryExtension	extension;
};

#endif
