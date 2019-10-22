#include "SSNSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	SSNSet s;
	assert(s.size() == 0);
	ItemType x = 1223334444;
	assert(s.add(x));
	assert(s.size() == 1);
	assert(!s.add(x));
	assert(s.size() == 1);
	assert(s.add(123123));
	s.print();

	cout << "Passed all tests" << endl;
}