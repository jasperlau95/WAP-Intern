#include "storelist.h"

extern string book_address;
extern string cash_address;
extern string book_log_address;
extern string cash_log_address;

void Storelist::LoadStoreList()
{
	Store store;
	string str;
	ifstream fin("Store.csv"); // Store.txt
	if(!fin) // If can't open
	{ 
		cerr << "Store.csv can't open" << endl;
		abort(); // Exit
	}
	while (getline(fin, str)) 
	{
		size_t i = str.find(","); // Find fisrt spacebar
		store.SetName(str.substr(0, i)); // Divide str by spacebar
		store.SetAddress(str.substr(i+1));
		store.SetBookAddress(str.substr(0, i) + "/Book.csv");
		store.SetCashAddress(str.substr(0, i) + "/Cash.txt");
		store.SetBookLogAddress(str.substr(0, i) + "/BookLog.txt");
		store.SetCashLogAddress(str.substr(0, i) + "/CashLog.txt");

		StoreArray.push_back(store); // Add to lib.UserArray
	}
	fin.close(); // Close User.txt
}

void Storelist::LoadLib(int storeNum)
{
	book_address = StoreArray[storeNum-1].GetBookAddress();
	cash_address = StoreArray[storeNum-1].GetCashAddress();
	book_log_address = StoreArray[storeNum-1].GetBookLogAddress();
	cash_log_address = StoreArray[storeNum-1].GetCashLogAddress();

	lib.LoadBook();	// Load Book.txt
	lib.LoadCash();	// Load Cash.txt
}