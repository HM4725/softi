#include "simple_int_set.h"
#include <iostream>
SimpleIntSet::SimpleIntSet(){
	mElements=new int[mElementCount];	
	mElementCount=0;
}

SimpleIntSet::SimpleIntSet(int *_elements, int _count){
	resultset.clear();	//static variable 이므로 다시 사용할 땐 초기화 시켜줘야함.
	mElementCount=_count;
	mElements=new int[mElementCount];
	for(int i=0;i<_count;++i)
		mElements[i]=_elements[i];

	for(int i=0; i!=mElementCount;++i)
		tempset.insert(mElements[i]);	//tempset에 대입

}

SimpleIntSet::~SimpleIntSet(){
	delete[] mElements;
}

int* SimpleIntSet::elements() const {
	return mElements;
}

int SimpleIntSet::elementCount() const {
	return mElementCount;
}

SimpleIntSet* SimpleIntSet::unionSet(SimpleIntSet& _operand){
	SetUnion(this->tempset,_operand.tempset);
	return this;
}

SimpleIntSet* SimpleIntSet::differenceSet(SimpleIntSet& _operand){
	SetDifference(this->tempset,_operand.tempset);
	return this;
}

SimpleIntSet* SimpleIntSet::intersectSet(SimpleIntSet& _operand){
	SetIntersection(this->tempset,_operand.tempset);
	return this;
}

void SimpleIntSet::printSet(){
	std::cout<<"{ ";
	for(set<int>::iterator itr=resultset.begin();itr!=resultset.end();++itr){
		std::cout<<*itr<<" ";
	}
	std::cout<<"}"<<std::endl;
}

set<int> SimpleIntSet::SetUnion(const set<int>& set0,const set<int>& set1){
	for(set<int>::iterator itr=set0.begin();itr!=set0.end();++itr){
		resultset.insert(*itr);
	}
	for(set<int>::iterator itr=set1.begin();itr!=set1.end();++itr){
		resultset.insert(*itr);
	}

	return resultset;
}
set<int> SimpleIntSet::SetIntersection(const set<int>& set0,const set<int>& set1){
	for(set<int>::iterator itr0=set0.begin();itr0!=set0.end();++itr0){
		for(set<int>::iterator itr1=set1.begin();itr1!=set1.end();++itr1){
			if(*itr0==*itr1){
				resultset.insert(*itr0);
			}
		}
	}
	return resultset;
}
set<int> SimpleIntSet::SetDifference(const set<int>& set0,const set<int>& set1){
	resultset=set0;
	for(set<int>::iterator itr0=resultset.begin();itr0!=resultset.end();++itr0){
		for(set<int>::iterator itr1=set1.begin();itr1!=set1.end();++itr1){
			if(*itr0==*itr1){
				resultset.erase(itr0);
			}
		}
	}	//erase(iterator) -> iterator가 가리키는 값을 지움
	/*for(set<int>::iterator itr=set1.begin();itr!=set1.end();++itr){
		resultset.erase(*itr);
	}*/	//erase(int) -> 그 int값을 가지는 값을 모두 지움
	return resultset;
}


set<int> SimpleIntSet::resultset; // static 변수 선언 !! 해줘야함.
