#pragma once

#ifndef RW_IDE_STRUCTURE
#define RW_IDE_STRUCTURE

#include <string>

// (III/VC/SA)
class ObjEntryBase {
public:
	unsigned int id;
	std::string modelName;
	std::string txdName;
};

// (III/VC/SA)
class ObjEntryType1 : public ObjEntryBase {
public:
	unsigned int meshCount;
	float drawDistance;
	int flags;
};

// (III/VC/SA)
class ObjEntryType2 : public ObjEntryType1 {
public:
	float drawDistance2;
};

// (III/VC/SA)
class ObjEntryType3 : public ObjEntryType2 {
public:
	float drawDistance3;
};

// (SA)
class ObjEntryType4 : public ObjEntryBase {
public:
	float drawDistance;
	int flags;
};

// (III/VC/SA)
class TobjEntryType1 : public ObjEntryType1 {
	int timeOn;
	int timeOff;
};

// (III/VC/SA)
class TobjEntryType2 : public ObjEntryType2 {
	int timeOn;
	int timeOff;
};

// (III/VC/SA)
class TobjEntryType3 : public ObjEntryType3 {
	int timeOn;
	int timeOff;
};

// (SA)
class TobjEntryType4 : public ObjEntryType4 {
	int timeOn;
	int timeOff;
};
#endif

