// simple_int_set.h
// Implement your simple_int_set.cc

#ifndef __hw03__simple_int_set__
#define __hw03__simple_int_set__

#define MAX_SIZE 1024
#include<set>
using namespace std;
class SimpleIntSet
{
private:
    int *mElements;
    int mElementCount;
    set<int> tempset;
    static set<int> resultset;

    explicit SimpleIntSet();
    
public:
    explicit SimpleIntSet(int *_elements, int _count);
    ~SimpleIntSet();
    
    int *elements() const; // return sorted array
    int elementCount() const;
    
    SimpleIntSet *unionSet(SimpleIntSet& _operand);
    SimpleIntSet *differenceSet(SimpleIntSet& _operand);
    SimpleIntSet *intersectSet(SimpleIntSet& _operand);

    static set<int> SetIntersection(const set<int>& set0, const set<int>& set1);
    static set<int> SetUnion(const set<int>& set0, const set<int>& set1);
    static set<int> SetDifference(const set<int>& set0, const set<int>& set1);    
    void printSet();
};


#endif
