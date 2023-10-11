
#include <iostream>
#include <string.h>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"

#define TRUE		1
#define FALSE		0

#pragma warning( disable : 4996) //for using strcpy


class DataStructure {
public:
	HEADER_E* pStruct;
public:
	DataStructure();
	DataStructure(char *pFilename);
	~DataStructure();
	DataStructure(const DataStructure &original);
private:
	HEADER_E* InitStruct();
};

HEADER_E* InitStruct() {
	HEADER_E* pStructTemp = GetStruct5(10, 30);

	return pStructTemp;
}

DataStructure::DataStructure() {
	pStruct = InitStruct();
}


DataStructure::DataStructure(char* pFilename) {

}


DataStructure::~DataStructure() {

}


DataStructure::DataStructure(const DataStructure &original) {

}



int main(){
	DataStructure pStructure;


	return 0;
}
