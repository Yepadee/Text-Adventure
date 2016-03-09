#pragma once
#include "stdafx.h"

using namespace std;
class Player
{
public:
	Player();
	//SetUp
	void setRace(int);
	void setProf(int);
	void setName(string);

	//Player Info:
	string getName();
	int getRace();
	int getProf();
	int getLevel();
	void addLevel();

	//Hp:
	void addHp(int);
	void removeHp(int);
	void resetHp();
	int getHp();
	int getMaxHp();

	//Money:
	void addFunds(int);
	void removeFunds(int);
	int getFunds();
	bool hasFunds(int);

	//Inventory:
	void addItem(int);
	void removeItem(int);
	void equipItem(int);
	void uneqipItem();
	int getWepInHand();
	vector<int> getInv();

private:
	friend class boost::serialization::access;
	template<class Archive>
	void Player::serialize(Archive & ar, const unsigned int version) {
		ar & race;
		ar & prof;
		ar & name;
		ar & level;
		ar & hp;
		ar & balance;
		ar & wepInHand;
		ar & inv;
	}
	//Player Defined:
	int race;
	int prof;
	string name;
	//Comp Defined:
	int level;
	int maxHp;
	int hp;
	int balance;
	int wepInHand;
	vector<int> inv;
};

