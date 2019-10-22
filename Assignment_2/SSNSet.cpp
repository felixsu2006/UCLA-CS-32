#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
	count = 0;
}

bool SSNSet::add(unsigned long ssn)
{
	if (s.insert(ssn))
	{
		count++;
		return true;
	}
	return false;
}

int SSNSet::size() const
{
	return s.size();
}

void SSNSet::print() const
{
	ItemType x;
	for (int k = 0; k < count; k++)
	{
		s.get(k, x);
		cout << x << endl;
	}
}
