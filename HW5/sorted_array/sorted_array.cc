#include"sorted_array.h"
SortedArray::SortedArray(){}
SortedArray::~SortedArray(){}

void SortedArray::AddNumber(int num){
	numbers_.push_back(num);
	
	int arraysize=numbers_.size();

	/*bubble sort*/
	for(int i=1;i<arraysize;++i){
		for(int j=0;j<arraysize-i;++j){
			if(numbers_[j]>numbers_[j+1])
				std::swap(numbers_[j],numbers_[j+1]);
		}
	}
}

vector<int> SortedArray::GetSortedAscending() const{
	vector<int> result;
	result.reserve(numbers_.size());

	for(vector<int>::const_iterator itr=numbers_.cbegin();itr!=numbers_.cend();itr++){
		result.push_back(*itr);
	}

	return result;
}

vector<int> SortedArray::GetSortedDescending() const{
	vector<int> result;
	result.reserve(numbers_.size());

	for(vector<int>::const_reverse_iterator itr=numbers_.crbegin();itr!=numbers_.crend();itr++){
		result.push_back(*itr);
	}

	return result;
}

int SortedArray::GetMax() const{
	return numbers_[numbers_.size()-1];
}

int SortedArray::GetMin() const{
	return numbers_[0];
}



