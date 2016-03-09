#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon(string t, string n, int v, int min, int max);
	void print();
	int getPower();
private:
	int minDmg;
	int maxDmg;
};

