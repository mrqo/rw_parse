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

#endif