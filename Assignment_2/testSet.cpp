#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	Set s;
	assert(s.empty());
	ItemType x = "arepa";
	assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
	s.insert("c");
	assert(!s.empty());
	s.insert("a");	//inserting smallest
	assert(s.size() == 2);
	assert(s.get(1, x) && x == "c");
	s.insert("b");	//inserting an element that is neither largest nor smallest
	assert(s.get(1, x) && x == "b");
	assert(s.get(2, x) && x == "c");
	s.insert("d");
	assert(s.get(3, x) && x == "d");
	assert(s.get(2, x) && x == "c");
	assert(s.get(1, x) && x == "b");
	assert(s.get(0, x) && x == "a");
	s.insert("a");	//checking duplicate case
	s.insert("z");	//inserting largest
	assert(s.get(4, x) && x == "z");
	s.insert("h");	//inserting an element that is neither largest nor smallest, and is towards the right of the index
	assert(s.get(5, x) && x == "z");
	assert(s.get(4, x) && x == "h");
	assert(s.get(3, x) && x == "d");
	assert(s.get(2, x) && x == "c");
	assert(s.get(1, x) && x == "b");
	assert(s.get(0, x) && x == "a");
	s.insert("");	//inserting smallest
	assert(s.get(6, x) && x == "z");
	assert(s.get(5, x) && x == "h");
	assert(s.get(4, x) && x == "d");
	assert(s.get(3, x) && x == "c");
	assert(s.get(2, x) && x == "b");
	assert(s.get(1, x) && x == "a");
	assert(s.get(0, x) && x == "");
	assert(s.contains("z"));
	assert(s.contains("h"));
	assert(s.contains("d"));
	assert(s.contains("c"));
	assert(s.contains("b"));
	assert(s.contains("a"));
	assert(s.contains(""));
	s.erase("c");	//erasing a middle element
	assert(s.get(5, x) && x == "z");
	assert(s.get(4, x) && x == "h");
	assert(s.get(3, x) && x == "d");
	assert(s.get(2, x) && x == "b");
	assert(s.get(1, x) && x == "a");
	assert(s.get(0, x) && x == "");
	s.erase("b");	//erasing another middle element, checking for any parity issues
	assert(s.get(4, x) && x == "z");
	assert(s.get(3, x) && x == "h");
	assert(s.get(2, x) && x == "d");
	assert(s.get(1, x) && x == "a");
	assert(s.get(0, x) && x == "");
	s.erase("");	//erasing smallest
	assert(s.get(3, x) && x == "z");
	assert(s.get(2, x) && x == "h");
	assert(s.get(1, x) && x == "d");
	assert(s.get(0, x) && x == "a");
	s.erase("z");	//erasing largest
	assert(s.get(2, x) && x == "h");
	assert(s.get(1, x) && x == "d");
	assert(s.get(0, x) && x == "a");
	Set k;
	assert(k.empty());
	k.swap(s);	//testing swap
	assert(s.empty());
	assert(k.get(2, x) && x == "h");
	assert(k.get(1, x) && x == "d");
	assert(k.get(0, x) && x == "a");



	cout << "Passed all tests" << endl;
}