#include"binary_search.h"

void BinarySearch::sortArray(){

/*Ignore this function if Count<2 */
	if(mArrayCount<2) return;
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
		if(order==mArrayCount-2){
			if(mArray[order]==mArray[order+1]){
				mArray[mArrayCount-1]=0;
				mArrayCount--;
			}
			else break;
		}
		else	{
			if(mArray[order]==mArray[order+1]){
				for(int i=order;i<mArrayCount-1;++i)
					mArray[i]=mArray[i+1];
				mArray[mArrayCount-1]=0;
				mArrayCount--;
			}
			else order++;
		}
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
	sortArray();
}

BinarySearch::~BinarySearch(){
	delete[] mArray;
}

int BinarySearch::getIndex(int _element){
	int start=0,mid,end=mArrayCount-1;
	while(start<end){
		mid=(start+end)/2;	
		if(_element>mArray[mid])
			start=mid+1;
		else end=mid;
	}

	return (_element==mArray[start])?start:-1;
}
