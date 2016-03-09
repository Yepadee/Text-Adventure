#include "stdafx.h"

Weapon::Weapon(string t, string n, int v, int min, int max)
: Item(t, n, v), minDmg(min), maxDmg(max)
{
}
void Weapon::print() {
	cout << "| " << type << " | " << name << " | " << minDmg << "-" << maxDmg << " dmg" <<" | " << value << "g |" << endl;
}
int Weapon::getPower() {
	random_device seed;
	mt19937 rand(seed());
	uniform_int_distribution<> range(minDmg, maxDmg);
	return range(rand);
}