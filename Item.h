#pragma once
#include <string>

using namespace std;
class Item
{
public:
	Item(string t, string n, int v);
	string getType();
	string getName();
	int getValue();
	virtual void print();
	virtual int getPower();
	
protected:
	string  type;
	string name;
	int value;
	
};

