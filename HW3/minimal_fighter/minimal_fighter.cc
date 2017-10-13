#include "minimal_fighter.h"

MinimalFighter::MinimalFighter(){
	mHp=0;
	mPower=0;
	mStatus=Invalid;
}

MinimalFighter::MinimalFighter(int _hp, int _power){
	mHp=_hp;
	mPower=_power;
	if(mHp>0)
		mStatus=Alive;
	else mStatus=Dead;
}


int MinimalFighter::hp() const {
	return mHp;
}

int MinimalFighter::power() const {
	return mPower;
}

FighterStatus MinimalFighter::status() const {
	return mStatus;
}
void MinimalFighter::setHp(int _hp){
	mHp=_hp;
	if (mHp<=0)
		mStatus=Dead;
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
