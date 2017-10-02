#include "minimal_fighter.h"

MinimalFighter::MinimalFighter(){
	this->mHp=0;
	this->mPower=0;
	this->mStatus=Invalid;
}

MinimalFighter::MinimalFighter(int _hp, int _power){
	this->mHp=_hp;
	this->mPower=_power;
	if(mHp>0)
		this->mStatus=Alive;
	else this->mStatus=Dead;
}


int MinimalFighter::hp() const {
	return this->mHp;
}

int MinimalFighter::power() const {
	return this->mPower;
}

FighterStatus MinimalFighter::status() const {
	return this->mStatus;
}
void MinimalFighter::setHp(int _hp){
	this->mHp=_hp;
	if (this->mHp<=0)
		this->mStatus=Dead;
}

void MinimalFighter::hit(MinimalFighter *_enemy){
	this->setHp(this->mHp - _enemy->mPower);
	_enemy->setHp(_enemy->mHp - this->mPower);

}

void MinimalFighter::attack(MinimalFighter *_target){
	_target->setHp(_target->mHp - this->mPower);
	this->mPower=0;

}

void MinimalFighter::fight(MinimalFighter *_enemy){
	while(true){
		this->setHp(this->mHp - _enemy->mPower);
		_enemy->setHp(_enemy->mHp - this->mPower);

		if(this->mHp<=0 || _enemy->mHp<=0)
			break;
	}
}
