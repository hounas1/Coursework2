#include "Datastructure.h"

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

DataStructure::DataStructure() {
	pStruct = new HEADER_E();
}

DataStructure::DataStructure(char* pFilename) {
	fstream file;
	file.open(pFilename, fstream::in | fstream::binary);

	if (!file.good()) {
		cout << "Opening file failed" << endl;
		return;
	}

	string fileLine;
	while (getline(file, fileLine)) {
		ITEM10* pItem = new ITEM10;
		if (fileLine.find(' ', 0) == string::npos){
			return;
		}
		int pos1 = fileLine.find(' ', 0), pos2 = fileLine.find(' ', pos1 + 1), length = 0;
		pItem->pID = new char[length = fileLine.substr(0, pos2).length() + 1];
		strcpy_s(pItem->pID, length, fileLine.substr(0, pos2).c_str());
		pos1 = fileLine.find(' ', pos2 + 1);
		pItem->Code = stoul(fileLine.substr(pos2 + 1, pos1 - pos2), 0, 0);
		pos2 = fileLine.find(' ', pos1 + 1);
		pItem->Date.Day = stoi(fileLine.substr(pos1 + 1, pos2 - pos1), 0, 0);
		pos1 = fileLine.find(' ', pos2 + 1);
		pItem->Date.pMonth = new char[length = fileLine.substr(pos2 + 1, pos1 - pos2 - 1).length() + 1];
		strcpy_s(pItem->Date.pMonth, length, fileLine.substr(pos2 + 1, pos1 - pos2 - 1).c_str());
		pos2 = fileLine.find('\n', pos1 + 1); 
		pItem->Date.Year = stoi(fileLine.substr(pos1 + 1, pos2 - pos1), 0, 0);
		pItem->pNext = 0;
		*this += pItem;
	}
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

DataStructure::DataStructure(const DataStructure& Original) {
	HEADER_E* pOriginalHeader = Original.pStruct;
	HEADER_E* pNewHeader = pOriginalHeader;
	while (pNewHeader) {
		if (pNewHeader->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pNewHeader->ppItems[i]);
				while (pItem != nullptr) {
					ITEM10* pNewItem = new ITEM10;
					pNewItem->pID = pItem->pID;
					pNewItem->Code = pItem->Code;

					pNewItem->Date.Day = pItem->Date.Day;
					pNewItem->Date.pMonth = pItem->Date.pMonth;
					pNewItem->Date.Year = pItem->Date.Year;

					pNewItem->pNext = nullptr;

					*this += pNewItem;

					pItem = pItem->pNext;
				}
			}
		}
		pNewHeader = pNewHeader->pNext;
	}
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

ITEM10* DataStructure::GetItem(char* pID) {
	HEADER_E* pHeader = pStruct;
	while (pHeader != nullptr) {
		if (pHeader->ppItems != nullptr && pHeader->cBegin == *pID) {
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

void DataStructure::operator+=(ITEM10* pNewItem) {
	if (!pNewItem || !pNewItem->pID) {
		cout << "Invalid item or ID" << endl;
		return;
	}

	pNewItem->pNext = NULL;
	char firstChar = *(pNewItem->pID);
	char secondChar = FindSecondLetter(pNewItem->pID);

	// Check if the pStruct's pItems are nullptr
	if (pStruct != nullptr && pStruct->ppItems == nullptr) {
		// Replace pStruct with the new header
		pStruct = new HEADER_E{
			new void* [26](),
			firstChar,
			nullptr
		};
	}

	HEADER_E** ppCurrentStruct = &pStruct;
	while (*ppCurrentStruct && (*ppCurrentStruct)->cBegin != firstChar) {
		ppCurrentStruct = &(*ppCurrentStruct)->pNext;
	}

	// If header is not found, create a new header
	if (*ppCurrentStruct == NULL) {
		*ppCurrentStruct = new HEADER_E{
			new void* [26](),
			firstChar,
			NULL
		};
	}

	// Create new pointer to correct header
	HEADER_E* pNewStruct = *ppCurrentStruct;

	int index = secondChar - 'A';
	ITEM10** ppItem = reinterpret_cast<ITEM10**>(&pNewStruct->ppItems[index]);

	// Check if item already exists
	for (ITEM10* pItem = *ppItem; pItem != nullptr; pItem = pItem->pNext) {
		if (strcmp(pItem->pID, pNewItem->pID) == 0) {
			cout << "Item " << pNewItem->pID << " exists!" << endl;
			return;
		}
	}

	// Insert the new item
	pNewItem->pNext = *ppItem;
	*ppItem = pNewItem;
}



void DataStructure::operator-=(char* pID) {
	HEADER_E* pHeader = pStruct;
	int itemCounter;
	int itemFound = 0;
	int itemIndex = 0;
	while (pHeader) {
		if (pHeader->ppItems != nullptr && pHeader->cBegin == *pID) {
			itemCounter = 0;
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeader->ppItems[i]);
				ITEM10* pItemPrevious = nullptr;
				while (pItem != nullptr) {
					itemCounter++;
					if (strcmp(pItem->pID, pID) == 0) { //item found
						itemFound = 1;
						itemIndex = i; //we have to save the index, but not return yet,
						//because we need to find out if the array has more items
						if (pItemPrevious != nullptr) { //item is linked to last item
							pItemPrevious->pNext = nullptr;
							delete pItem;
							return;
						}
						if (pItem->pNext != nullptr) { //item is linked to next item
							pItemPrevious = pItem;
							pHeader->ppItems[i] = pItemPrevious;
							delete pItem;
							return;
						}
					}
					pItemPrevious = pItem;
					pItem = pItem->pNext;
				}
			}
			if (itemFound) {
				if (itemCounter > 1) { //not the last item in header
					delete pHeader->ppItems[itemIndex];
					pHeader->ppItems[itemIndex] = nullptr;
				}
				else { //last item in header, have to also delete the header
					if (pHeader->pPrior == nullptr) { //first header
						pHeader->pNext->pPrior = nullptr;
						pStruct = pHeader->pNext;
						delete pHeader->ppItems[itemIndex];
						pHeader->ppItems[itemIndex] = nullptr;
						delete pHeader;
					}
					else if (pHeader->pNext == nullptr) { //last header
						pHeader->pPrior->pNext = nullptr;
						delete pHeader->ppItems[itemIndex];
						pHeader->ppItems[itemIndex] = nullptr;
						delete pHeader;
					}
					else { //headers present on both sides
						pHeader->pPrior->pNext = pHeader->pNext;
						pHeader->pNext->pPrior = pHeader->pPrior;
						delete pHeader->ppItems[itemIndex];
						pHeader->ppItems[itemIndex] = nullptr;
						delete pHeader;
					}
				}
				return;
			}
		}
		pHeader = pHeader->pNext;
	}
	cout << "Item " << pID << " not found" << endl;
}


DataStructure& DataStructure::operator=(const DataStructure& Right) {
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

	HEADER_E* pHeaderRight = Right.pStruct;
	HEADER_E* pHeaderNew = pHeaderRight;
	while (pHeaderNew) {
		if (pHeaderNew->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeaderNew->ppItems[i]);
				while (pItem != nullptr) {
					ITEM10* pNewItem = new ITEM10;
					pNewItem->pID = pItem->pID;
					pNewItem->Code = pItem->Code;

					pNewItem->Date.Day = pItem->Date.Day;
					pNewItem->Date.pMonth = pItem->Date.pMonth;
					pNewItem->Date.Year = pItem->Date.Year;

					pNewItem->pNext = nullptr;

					*this += pNewItem;

					pItem = pItem->pNext;
				}
			}
		}
		pHeaderNew = pHeaderNew->pNext;
	}
	return *this;
}

int DataStructure::operator==(DataStructure& Other) {
	HEADER_E* pOriginal = pStruct;
	HEADER_E* pOther = Other.pStruct;


	while (pOriginal != nullptr && pOther != nullptr) {
		if (pOriginal->ppItems != nullptr && pOther->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItemOriginal = reinterpret_cast<ITEM10*>(pOriginal->ppItems[i]);
				ITEM10* pItemOther = reinterpret_cast<ITEM10*>(pOther->ppItems[i]);
				while (pItemOriginal != nullptr && pItemOther != nullptr) {
					if (!strcmp(pItemOriginal->pID, pItemOther->pID) &&
						pItemOriginal->Code == pItemOther->Code &&
						pItemOriginal->Date.Day == pItemOther->Date.Day &&
						!strcmp(pItemOriginal->Date.pMonth, pItemOther->Date.pMonth) &&
						pItemOriginal->Date.Year == pItemOther->Date.Year) {
					}
					else { //item does not have same elements
						return 0;
					}
					pItemOriginal = pItemOriginal->pNext;
					pItemOther = pItemOther->pNext;
				}
				if (pItemOriginal != nullptr || pItemOther != nullptr) {
					return 0;
				}
			}	
		}
		if ((pOriginal->ppItems != nullptr) != (pOther->ppItems != nullptr)) {
				return 0;
		}
		pOriginal = pOriginal->pNext;
		pOther = pOther->pNext;
	}

	if (pOriginal != nullptr || pOther != nullptr) { //one datastrure has more headers
		return 0;
	}
	
	return 1;
}

void DataStructure::Write(char* pFilename) {
	fstream file;
	file.open(pFilename, fstream::out | fstream::binary);
	
	if (!file.good()) {
		cout << "Error opening file" << endl;
		return;
	}

	string strBuf;
	HEADER_E* pHeader = this->pStruct;

	while (pHeader != nullptr) {
		if (pHeader->ppItems != nullptr) {
			for (int i = 0; i < 26; i++) {
				ITEM10* pItem = reinterpret_cast<ITEM10*>(pHeader->ppItems[i]);
				while (pItem != nullptr) {
					strBuf += string(pItem->pID) + ' ' + to_string(pItem->Code) + ' ' +
						to_string(pItem->Date.Day) + ' ' + string(pItem->Date.pMonth) + ' ' +
						to_string(pItem->Date.Year) + '\n';
					pItem = pItem->pNext;
				}	
			}
		}
		pHeader = pHeader->pNext;
	}
	file.write(strBuf.c_str(), strBuf.length());
	file.close();
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

