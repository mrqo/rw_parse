#pragma once
#ifndef RW_CORE
#define RW_CORE

#include "rw_types.h"

enum RwFileVersion : uint_32 {
	rwVERSION_30002		= 0x00000302,	// alpha GTA3, geometry is being kept in atomics (PS2)
	rwVERSION_30004		= 0x00000304,	// GTA3 (PS2)
	rwVERSION_300010	= 0x00000310,	// GTA3 (PS2, Win (MultiDff and Generic))
	rwVERSION_3200		= 0x0800FFFF,	// GTA3 (Win)
	rwVERSION_3302		= 0x0C02FFFF,	// GTAVC (Win)
	rwVERSION_3403		= 0x1003FFFF,	// GTAIII / GTAVC (Xbox)
	rwVERSION_3405		= 0x1005FFFF,	// GTAVC (Android)
	rwVERSION_3500		= 0x1400FFFF,	// GTAIII (Android)
	rwVERSION_3603		= 0x1803FFFF	// GTASA
};

enum RwBinSectionType : uint_32 {
	rwDATA				= 0x0001,		// 1
	rwSTRING			= 0x0002,		// 2
	rwEXTENSION			= 0x0003,		// 3
	rwTEXTURE			= 0x0006,		// 6
	rwMATERIAL			= 0x0007,		// 7
	rwMATERIALLIST		= 0x0008,		// 8
	rwFRAMELIST			= 0x000E,		// 14
	rwGEOMETRY			= 0x000F,		// 15
	rwCLUMP				= 0x0010,		// 16
	rwATOMIC			= 0x0014,		// 20
	rwTEXTURENATIVE		= 0x0015,		// 21
	rwTEXTUREDICTIONARY = 0x0016,		// 22
	rwGEOMETRYLIST		= 0x001A,		// 26
	rwMATERIALSPLIT		= 1294,			// 1294
	rwFRAME				= 0x0253F2FE	// 39056126		
};

enum RwIdeSectionType : uint_32 {
	rwOBJS				= 0x0001,
	rwTOBJ				= 0x0002,
	rwPATH				= 0x0003,
	rw2DFX				= 0x0004,
	rwANIM				= 0x0005,
	rwTXDP				= 0x0006
};

// SectionHeader
class RwSectionHeader {
public:
	uint_32 sectionType;
	uint_32 sectionSize;
	uint_32 versionNumber;
};
// --- 

#endif