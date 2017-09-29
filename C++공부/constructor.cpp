#include<iostream>

class TEST{
public:
	TEST()  /*constructor*/
//		:m_nData(0); //1.???
	{
		std::cout<<"TEST()"<<std::endl;
		m_nData=0; //2
	}

	~TEST(){	/*destructor*/
		std::cout<<"~TEST()"<<std::endl;
	}
	int m_nData=0;	//3. C++11
	
};

TEST hm;

int main(){
	std::cout<<"Begin of main()"<<std::endl;
	//compare!
	TEST *pTest =(TEST*)malloc(sizeof(TEST));
	free(pTest); // No call!, pTest : memory which can store instance.

	TEST *pNewTest = new TEST;
	delete pNewTest; // call!, pNewTest : instance
	
	std::cout<<"End of main()"<<std::endl;
	return 0;
}//--> The destructing point of local varaibles --> destructor call!

/*
C : The starting point of code is main().
C++ : Constructor of the class can be, too.
*/
