#include "stdafx.h"

using namespace std;
Player::Player()
{
	race = -1;
	level = 0;
	maxHp = 100;
	hp = maxHp;
	balance = 0;
	wepInHand = 0;
}
//SetUp
void Player::setRace(int r) {
	race = r;
}
void Player::setProf(int p) {
	prof = p;
}
void Player::setName(string n) {
	name = n;
}

//Player Info:
int Player::getRace() {
	return race;
}
int Player::getProf() {
	return prof;
}
string Player::getName() {
	return name;
}
int Player::getLevel() {
	return level;
}
void Player::addLevel() {
	level += 1;
}

//HP:
void Player::addHp(int amount) {
	hp += amount;
}
void Player::removeHp(int amount) {
	hp -= amount;
}
void Player::resetHp() {
	hp = maxHp;
}
int Player::getHp() {
	return hp;
}
int Player::getMaxHp() {
	return maxHp;
}

//Money:
void Player::addFunds(int amount) {
	cout << "You gained " << amount << " gold!" << endl;
	balance += amount;
}
void Player::removeFunds(int amount) {
	balance -= amount;
}
int Player::getFunds() {
	return balance;
}
bool Player::hasFunds(int amount) {
	return (balance - amount >= 0);
}


//Inventory:
void Player::addItem(int itemID) {
	inv.push_back(itemID);
}
void Player::removeItem(int itemID) {
	for (int i = 0; i < inv.size(); i++) {
		if (inv[i] == itemID) {
			inv.erase(inv.begin() + i);
			return;
		}
	}
}
void Player::equipItem(int itemID) {
	wepInHand = itemID;
	removeItem(itemID);
}
void Player::uneqipItem() {
	if (wepInHand != 0) {
		addItem(wepInHand);
		wepInHand = 0;
	}
}
int Player::getWepInHand() {
	return wepInHand;
}
vector<int> Player::getInv() {
	return inv;
}
