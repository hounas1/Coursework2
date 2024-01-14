#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <filesystem>
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
	DataStructure(); //creates empty data structure

	~DataStructure(); //deletes all items, vectors of pointers and headers

	DataStructure(const DataStructure& Original); //Copy constructor

	int GetItemsNumber(); //returns current number of items in data structure

	ITEM10* GetItem(char* pID); //Returns pointer to item with specified ID

	void operator+=(ITEM10* pNewItem); //Adds new item into data structure

	void operator-=(char* pID); //removes item with specified ID

	int operator==(DataStructure& Other); //compares two datastructures

	void Write(char* pFilename); //writes data structure into specified file

	friend ostream& operator<<(ostream& ostr, const DataStructure& str); //prints all items
};