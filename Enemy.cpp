#include "stdafx.h"

Enemy::Enemy(string n, int mHp, int r, int min, int max)
: name(n), maxHp(mHp), reward(r), minDmg(min), maxDmg(max)
{
}
string Enemy::getName() {
	return name;
}
int Enemy::getHp() {
	return hp;
}
int Enemy::getMaxHp() {
	return maxHp;
}
int Enemy::getPower() {
	random_device seed;
	mt19937 rand(seed());
	uniform_int_distribution<> range(minDmg, maxDmg);
	return range(rand);
}
int Enemy::getReward() {
	return reward;
}
void Enemy::resetHp() {
	hp = maxHp;
}
void Enemy::removeHp(int amount) {
	hp -= amount;
}