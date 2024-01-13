
#include "Datastructure.h"

int main(){
	/// 
	/// TEST CASE 1
	/// 
	DataStructure pDataStructure;

	/// 
	/// TEST CASE 2
	/// 
	for (int i = 0; i < 10; i++) {
		ITEM10* item = (ITEM10*)GetItem(10);
		pDataStructure += item;
	}
	/// 
	/// TEST CASE 3
	/// 
	cout << endl << "||DATASTRUCTURE AFTER ADDING 10 ITEMS||" << endl << endl;
	cout << pDataStructure << endl << endl;

	/// 
	/// TEST CASE 4
	/// 
	cout << "||" << pDataStructure.GetItemsNumber() << " items in datastructure||" << endl;
	
	/// 
	/// TEST CASE 5 AND 6
	/// 
	char srch[][20] = { "Light Cyan", "X X" };
	for (int i = 0; i < 2; i++) {
		ITEM10* pSrchItem = pDataStructure.GetItem(srch[i]);
		cout << endl << "||Searching for item: " << srch[i] << "||" << endl;
		if (pSrchItem != NULL) {
			cout << "Item found: ";
			cout << pSrchItem->pID << "|" << pSrchItem->Code << endl;
		}
		else {
			cout << "Item not found" << endl;
		}
	}

	/// 
	/// TEST CASE 7
	/// 
	DataStructure pDataStructureCopy = pDataStructure;
	cout << endl << "||Copy of original datastructure||" << endl;
	cout << pDataStructureCopy << endl;



	return 0;
}
