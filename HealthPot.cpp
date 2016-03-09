#include "stdafx.h"

HealthPot::HealthPot(string t, string n, int v, int p)
: Item(t, n, v), power(p)
{
}

void HealthPot::print() {
	cout << "| " << type << " | " << name << " | +"<< power << " Hp | "<< value << "g |" << endl;
}
int HealthPot::getPower() {
	return power;
}