#include "Datastructure.h"

DataStructure::DataStructure() {
	pStruct = new HEADER_E [26]();
}

char FindSecondLetter(char* pNewItemID) {
	char* pSecondId = (char*)' ', secondChar;
	char* pSpace = strchr(pNewItemID, ' '); // find the second word of ID
	if (!pSpace) {
		return 0;
	}
	pSecondId = pSpace + 1;
	secondChar = *(pSecondId);
	return secondChar;
}

ITEM10* DataStructure::GetItem(char* pID) {
	HEADER_E* pHeader = pStruct;
	while (pHeader != nullptr) {
		if (pHeader->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeader->ppItems[i]);
				while (pItem != nullptr) {
					if (strcmp(pItem->pID, pID) == 0) {
						return pItem;
					}
					pItem = pItem->pNext;
				}
			}
		}
		pHeader = pHeader->pNext;
	}
	return NULL;
}

int DataStructure::GetItemsNumber() {
	int n = 0;
	HEADER_E* pHeader = pStruct;
	if (!pStruct) {
		cout << "Data Structure is empty!" << endl;
		return n;
	}
	while (pHeader != nullptr) {
		if (pHeader->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeader->ppItems[i]);
				while (pItem != nullptr) {
					n++;
					pItem = pItem->pNext;
				}
			}
		}
		pHeader = pHeader->pNext;
	}
	return n;
}

ostream& operator<<(ostream& ostr, const DataStructure& str) {
	int n = 1;
	HEADER_E* pHeader = str.pStruct;
	if (!str.pStruct) {
		cout << "Data Structure is empty!" << endl;
		return ostr;
	}
	while (pHeader != nullptr) {
		if (pHeader->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeader->ppItems[i]);
				//ITEM10* pItem = (ITEM10*)pHeader->ppItems[i];
				while (pItem != nullptr) {
					ostr << n++ << ") "<< "[" << i++ << "]" << "[" << pHeader->cBegin << "] ";
					ostr << pItem->pID << "|" << pItem->Code << "|";
					ostr << pItem->Date.Day << "/" << pItem->Date.pMonth << "/" << pItem->Date.Year << endl;
					pItem = pItem->pNext;
				}
			}
		}
		pHeader = pHeader->pNext;
	}
	return ostr;
}

void DataStructure::operator+=(ITEM10* pNewItem) {
	if (!pNewItem || !pNewItem->pID) {
		cout << "Invalid item or ID" << endl;
		return;
	}

	pNewItem->pNext = NULL;
	char firstChar = *(pNewItem->pID);
	char secondChar = FindSecondLetter(pNewItem->pID);
	 
	HEADER_E** ppCurrentStruct = &pStruct;
	while (*ppCurrentStruct && (*ppCurrentStruct)->cBegin != firstChar) {
		ppCurrentStruct = &(*ppCurrentStruct)->pNext;
	}
	//if header is not found
	if (*ppCurrentStruct == NULL) {
		*ppCurrentStruct = new HEADER_E{
			new void* [26](),
			firstChar,
			NULL
		};
	}
	//create new pointer to correct header
	HEADER_E* pNewStruct = *ppCurrentStruct;

	int index = secondChar - 'A';
	ITEM10** ppItem = reinterpret_cast<ITEM10**>(&pNewStruct->ppItems[index]);

	//check if item already exists
	for (ITEM10* pItem = *ppItem; pItem != nullptr; pItem = pItem->pNext) {
		if (strcmp(pItem->pID, pNewItem->pID) == 0) {
			cout << "Item " << pNewItem->pID << " exists!" << endl;
			return;
		}
	}

	pNewItem->pNext = *ppItem;
	*ppItem = pNewItem;
}


DataStructure::~DataStructure() {
	while (pStruct) {
		HEADER_E* pHeader = pStruct;
		pStruct = pStruct->pNext;
		if (pHeader->ppItems) { //check if items are present
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = static_cast<ITEM10*>(pHeader->ppItems[i]);
				while (pItem) {
					ITEM10* pItemTemp = pItem->pNext; //save next item, to delete current
					delete pItem;
					pItem = pItemTemp;
				}
			}
			delete[] pHeader->ppItems;
		}
		delete pHeader;
	}
}