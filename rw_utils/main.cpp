// rw_utils.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rw_dff.h"

int main()
{
	RwDff *LODroad15 = new RwDff("C:\\Users\\HP\\Desktop\\rw-parse\\Debug\\dff\\LODroad15.dff");
	LODroad15->openFile();
	LODroad15->loadFile();
	LODroad15->serialize();
	LODroad15->printFileStructure();

	RwDff *newramp2 = new RwDff("C:\\Users\\HP\\Desktop\\rw-parse\\Debug\\dff\\newramp2.dff");
	newramp2->openFile();
	newramp2->loadFile();
	newramp2->serialize();
	newramp2->printFileStructure();

	system("PAUSE");
	delete LODroad15;
	delete newramp2;
    return 0;
}

