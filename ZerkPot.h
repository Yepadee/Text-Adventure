#pragma once
#include "Item.h"

using namespace std;

class ZerkPot : public Item
{
public:
	ZerkPot(string, string, int, int);
	int getPower();
	void print();
private:
	int power;
};

