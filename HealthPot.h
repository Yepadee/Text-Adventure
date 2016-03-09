#pragma once
#include "Item.h"

using namespace std;

class HealthPot : public Item
{
public:
	HealthPot(string, string, int, int);
	int getPower();
	void print();
private:
	int power;
};

