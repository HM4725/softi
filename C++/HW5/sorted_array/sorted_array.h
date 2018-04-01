#include<vector>
#include<iostream>
using namespace std;
/* using namespace std; 를 써주지않으면
   vector does not name a type이 뜸. */

class SortedArray{
public:
	SortedArray();
	~SortedArray();
	void AddNumber(int num);

	vector<int> GetSortedAscending() const;
	vector<int> GetSortedDescending() const;
	int GetMax() const;
	int GetMin() const;

private:
	vector<int> numbers_;
};
