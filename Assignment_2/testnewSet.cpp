#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	Set x;
	Set y(2);

	const ItemType a = "a";
	const ItemType b = "b";
	const ItemType c = "c";
	const ItemType d = "d";

	assert(y.insert(a));
	assert(y.insert(b));
	assert(!y.insert(a));
	assert(!y.insert(c));
	
	assert(x.insert(a));
	assert(x.contains("a"));
	Set z = x;
	assert(z.contains("a"));
	z.swap(y);
	assert(z.contains("a"));
	assert(z.contains("b"));
	assert(y.contains("a"));
	y.swap(z);
	assert(y.contains("a"));
	assert(y.contains("b"));
	assert(z.contains("a"));
	y.swap(z)
	y = z;
	assert(z.contains("a"));
	assert(z.contains("b"));
	assert(y.contains("a"));
	assert(y.contains("b"));



	cout << "nice" << endl;

}
