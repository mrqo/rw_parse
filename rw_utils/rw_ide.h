#pragma once
#ifndef RW_IDE
#define RW_IDE

#include <vector>

#include "rw_file.h"
#include "rw_core.h"
#include "rw_ide_structure.h"

class RwIde : public RwFile {
public:
	RwIde(std::string fileName);
	~RwIde();

	bool openFile();
	void loadFile();
	void serialize();

private:
	std::vector<ObjEntryBase> objs;
	std::vector<ObjEntryBase> tobj;
};

#endif
