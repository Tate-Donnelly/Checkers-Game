//============================================================================
// Name        : HW___5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Tests.h"
#include "Production.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	printf("Starting\n");
	Tests* tsP = new Tests();
	if(tsP->tests())
	{
		Production* pP = new Production();
		if(pP->prod(argc, argv))
		{
			cout <<"Production passed." << endl;
		}
		delete(pP);
	}
	else
	{
		cout <<"Not all tests passed." << endl;
	}
	delete(tsP);
	return 0;
}
