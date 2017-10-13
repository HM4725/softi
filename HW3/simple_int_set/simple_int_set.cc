#include "simple_int_set.h"
#include <iostream>

void SimpleIntSet::sortElements(){

/* Ignore this function if Count<2 */
	if(mElementCount<2) return;
/* sort integer */
	int hold;
	for(int i=1; i<mElementCount; ++i){
		for(int j=0; j<mElementCount-i;++j){
			if(mElements[j]>mElements[j+1]){
				hold=mElements[j];
				mElements[j]=mElements[j+1];
				mElements[j+1]=hold;
			}
		}
	}
/* Eliminate same element */
	int order=0;
	while(true){
		if(order==mElementCount-2){
			if(mElements[order]==mElements[order+1]){
				mElements[mElementCount-1]=0;
				mElementCount--;
			}
			else break;
		}
		else {
			if(mElements[order]==mElements[order+1]){
				for(int i=order; i<mElementCount-1; ++i)
					mElements[i]=mElements[i+1];
				mElements[mElementCount-1]=0;
				mElementCount--;
			}
			else	order++;
		}
	}
	
}

SimpleIntSet::SimpleIntSet(){
	mElements=new int[mElementCount];	
	mElementCount=0;
}

SimpleIntSet::SimpleIntSet(int *_elements, int _count){
	mElementCount=_count;
	mElements=new int[mElementCount];	
	for(int i=0;i<_count;++i)
		mElements[i]=_elements[i];
	sortElements();
}

SimpleIntSet::~SimpleIntSet(){
	std::cout<<"destructed"<<std::endl;
	delete[] mElements;
}

int* SimpleIntSet::elements() const {
	return mElements;
}

int SimpleIntSet::elementCount() const {
	return mElementCount;
}

SimpleIntSet* SimpleIntSet::unionSet(SimpleIntSet& _operand){
	int *operset=_operand.elements();
	for(int i=0; i<_operand.elementCount(); ++i){
		mElementCount++;
		mElements[mElementCount-1]=operset[i];
	} 
	sortElements(); 
	return this;
}

SimpleIntSet* SimpleIntSet::differenceSet(SimpleIntSet& _operand){
	int *operset=_operand.elements();
	for (int j=0;j<_operand.elementCount();++j){
		for (int i=0;i<mElementCount;++i){
			if((mElements[i]==operset[j])&&(i!=mElementCount-1)){
				for(int k=i;k<mElementCount-1;++k){
					mElements[k]=mElements[k+1];
				}
				mElementCount--;
				break;
			}
			else if((mElements[i]==operset[j])&&(i==mElementCount-1)){
				mElementCount--;
				break;
			}
		}
	}
	return this;
}

SimpleIntSet* SimpleIntSet::intersectSet(SimpleIntSet& _operand){
	int ISetCount=0;
	int *ISet=new int[ISetCount];
	int *operset=_operand.elements();
	for(int i=0;i<mElementCount;++i){
		for(int j=0;j<_operand.elementCount();++j){
			if(mElements[i]==operset[j]){
				ISetCount++;
				ISet[ISetCount-1]=mElements[i];
			}	
		}
	}
	mElementCount=ISetCount;
	for(int i=0;i<ISetCount;++i){
		mElements[i]=ISet[i];
	}
	delete[] ISet;
	return this;
}

void SimpleIntSet::printSet(){
	std::cout<<"{ ";
	for(int i=0;i<mElementCount;++i){
		std::cout<<mElements[i]<<" ";
	}
	std::cout<<"}"<<std::endl;
}
/* error
*** Error in `./test': free(): invalid next size (fast): 0x00000000019030a0 ***
메모리 문제??
궁금한점 :
	SimpleIntSet *left = NULL;
	SimpleIntSet *right = NULL; 
(x2)	SimpleIntSet *newSet = new SimpleIntSet(elements, elementCount);
	left = newSet;
	right = newSet;
	
	SimpleIntSet::unionSet(SimpleIntSet& _operand) : definition
	left->unionSet(*right); : call
	(argument -> & ???) (argument -> * ???)

	simple_int_set_main.cc : 63.
	delete elements -> delete [] elements 아님?
*/
