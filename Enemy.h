#pragma once
#include "Enemy.h"
#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string, int, int, int, int);
	string getName();
	int getHp();
	int getMaxHp();
	int getPower();
	int getReward();
	void resetHp();
	void removeHp(int);
private:
	string name;
	int hp;
	int maxHp;
	int minDmg;
	int maxDmg;
	int reward;
};

