#include "stdafx.h"

using namespace std;
ZerkPot::ZerkPot(string t, string n, int v, int p)
: Item(t, n, v), power(p)
{
}
void ZerkPot::print() {
	cout << "| " << type << " | " << name << " | +" << power << "% Dmg (3 turns) | " << value << "g |" << endl;
}
int ZerkPot::getPower() {
	return power;
}