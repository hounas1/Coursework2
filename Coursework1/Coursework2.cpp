
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
	DataStructure(char *pFilename);
	~DataStructure();
	DataStructure(const DataStructure &original);
public:
	void PrintDataStructure(HEADER_E *pStruct);
};

DataStructure::DataStructure() {
	pStruct = GetStruct5(10, 30);
}


DataStructure::DataStructure(char* pFilename) {

}


DataStructure::~DataStructure() {

}


DataStructure::DataStructure(const DataStructure &original) {

}

void DataStructure::PrintDataStructure(HEADER_E *pStruct){
	HEADER_E* pStructTemp = pStruct;
	int i = 1;
	while (pStructTemp != NULL) {
		cout << "HEADER:" << pStructTemp->cBegin << "\n";
		void** ppItem = pStructTemp->ppItems;
		for (int j = 0; j < 25; j++) {
			ITEM10* pItem = (ITEM10*)ppItem[j];
			while (pItem != NULL) {
				cout << " | " << i << ") " << pItem->pID << pItem->Code;
				cout << " " << pItem->Date.Day << "/" << pItem->Date.pMonth << "/" << pItem->Date.Year << "\n";
				pItem = pItem->pNext;
				i++;
			}
		}
		pStructTemp = pStructTemp->pNext;
	}
}



int main(){
	DataStructure pStructure;

	pStructure.PrintDataStructure(pStructure.pStruct);

	return 0;
}
