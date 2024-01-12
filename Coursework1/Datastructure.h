#pragma once

#include <iostream>
#include <string.h>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"

using namespace std;

#define TRUE		1
#define FALSE		0

#pragma warning( disable : 4996) //for using strcpy


class DataStructure {
public:
	HEADER_E* pStruct;
public:
	DataStructure();
	~DataStructure();
	int GetItemsNumber();
	ITEM10* GetItem(char* pID);
	friend ostream& operator<<(ostream& ostr, const DataStructure& str);
	void operator+=(ITEM10* pNewItem);
	
};