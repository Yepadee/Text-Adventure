#include "stdafx.h"

Item::Item(string t, string n, int v)
: type(t), name(n), value(v)
{
}
string Item::getType() {
	return type;
}
string Item::getName() {
	return name;
}
int Item::getValue() {
	return value;
}
void Item::print() {
	cout << "| " << type << " | " << name << " | " << value << "g |" << endl;
}
int Item::getPower() { return 0; }