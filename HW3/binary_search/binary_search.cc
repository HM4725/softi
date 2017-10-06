#include"binary_search.h"

void BinarySearch::sortArray(){
/*sort integer*/
	int hold;
	for(int i=1; i<mArrayCount; ++i){
		for(int j=0; j<mArrayCount-i; ++j){
			if(mArray[j]>mArray[j+1]){
				hold=mArray[j];
				mArray[j]=mArray[j+1];
				mArray[j+1]=hold;
			}
		}
	}
/*Eliminate same element*/
	int order=0;
	while(true){
		if(mArray[order]==mArray[order+1]&&order!=mArrayCount-2){
			for(int i=order;i<mArrayCount-1;++i)
				mArray[i]=mArray[i+1];
			mArray[mArrayCount-1]=0;
			mArrayCount--;
		}
		else if(mArray[order]==mArray[order+1]&&order==mArrayCount-2){
			mArray[mArrayCount-1]=0;
			mArrayCount--;
			break;
		}
		else if(order==mArrayCount-2)	break;
		else 	order++;
	}
}

BinarySearch::BinarySearch(){
	mArrayCount=0;
	mArray=new int[mArrayCount];
}

BinarySearch::BinarySearch(int *_array, int _arrayCount){
	mArrayCount=_arrayCount;
	mArray=new int[mArrayCount];
	for(int i=0; i<mArrayCount; ++i)
		mArray[i]=_array[i];
}

BinarySearch::~BinarySearch(){
	delete[] mArray;
}

int BinarySearch::getIndex(int _element){
	int midpoint;
	
}
