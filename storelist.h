#ifndef STORELIST_H
#define STORELIST_H

#include <string>
#include "library.h"
#include "store.h"

extern Library lib;

class Storelist {
public:
	void LoadStoreList();
	void LoadLib(int storeNum);
	vector<Store> StoreArray; // Store all stores in vector
};

#endif