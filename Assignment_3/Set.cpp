#include "Set.h"
#include <iostream>
using namespace std;

Set::Set()
{
	head = nullptr;
	count = 0;
}

Set::Set(const Set& other)
{
	head = nullptr;
	count = 0;
	ItemType x;
	for (int k = 0; k < other.count; k++)
	{
		other.get(k, x);
		insert(x);
	}
}

Set& Set::operator= (const Set& other)
{
	if (this != &other)
	{
		Set temp(other);
		swap(temp);
	}
	return *this;
}

Set::~Set()
{
	if (count == 0)
		return;

	if (count == 1)
	{
		delete head;
		return;
	}

	Node* p;
	for (p = head; p->next != nullptr; p = p->next)	//this sets p to the largest value in the list
		;
	for (p = p->prev; p != nullptr; p = p->prev)	//deletes every next value, stops when hits nullptr thus NOT DELETING head
	{
		delete p->next;
	}
	delete head;	//delete head
}

bool Set::empty() const
{
	return (count == 0);
}

int Set::size() const
{
	return count;
}

bool Set::insert(const ItemType& value)
{
	Node* p;
	p = head;
	if (count == 0)	//when size is 1
	{
		Node* newGuy = new Node;
		head = newGuy;
		head->next = nullptr;
		head->data = value;
		head->prev = nullptr;
		count++;
		return true;
	}
	else if (count == 1)	//when size is 1
	{
		if (value == head->data)	//case where value is equal to the only thing
		{
			return false;
		}
		else if (value < head->data)	//case where value is smallest
		{
			Node* newGuy = new Node;
			newGuy->data = head->data;
			newGuy->next = nullptr;
			newGuy->prev = head;
			head->next = newGuy;
			head->data = value;
			count++;
			return true;
		}
		else	//case where value is largest
		{
			Node* newGuy = new Node;
			newGuy->data = value;
			newGuy->prev = head;
			newGuy->next = nullptr;
			head->next = newGuy;
			count++;
			return true;
		}
	}

	if (value <= head->data)	//when value is less than the smallest
	{
		if (value == head->data)	//if equal, return false
		{
			return false;
		}
		Node* newGuy = new Node;
		newGuy->next = head->next;
		newGuy->data = head->data;
		head->next->prev = newGuy;
		head->data = value;
		head->next = newGuy;
		newGuy->prev = head;
		count++;
		return true;
	}
	else	//when value is larger than the smallest
	{
		for (p = head; (value >= p->data) && (p->next != nullptr); p = p->next)
			;
		if (p->next == nullptr )	//if the second restriction is tripped
		{
			if (value > p->data)	//if the second AND the first are tripped
			{
				Node* newGuy = new Node;
				newGuy->data = value;
				newGuy->prev = p;
				newGuy->next = nullptr;
				p->next = newGuy;
				count++;
				return true;
			}
			else		//only the second restriction tripped
			{
				Node* newGuy = new Node;
				newGuy->data = value;
				p->prev->next = newGuy;
				newGuy->next = p;
				newGuy->prev = p->prev;
				p->prev = newGuy;
				count++;
				return true;
			}
		}
		else		//first restriction only
		{
			Node* newGuy = new Node;
			newGuy->data = value;
			newGuy->next = p;
			newGuy->prev = p->prev;
			p->prev->next = newGuy;
			p->prev = newGuy;
			count++;
			return true;
		}
	}
	return false;
}

bool Set::erase(const ItemType& value)
{
	Node* p;
	if (count == 0)	//special cases 0 and 1
		return false;

	else if(count == 1)
	{
		p = head;
		if (p->data == value)
		{
			delete p;
			head = nullptr;
			count--;
			return true;
		}
	}

	for (p = head; p != nullptr; p = p->next)	//p != nullptr when youre actually doing stuff with the pointer, p->!= nullptr when youre just finding it
	{
		if (value == p->data)
		{
			if (p->next == nullptr)	//special case, if value is largest thing
			{
				p->prev->next = nullptr;
				delete p;
				count--;
				return true;
			}
			else if (p->prev == nullptr)	//special case, if value is smallest thing
			{
				head = p->next;
				head->prev = nullptr;
				delete p;
				count--;
				return true;
			}
			else		//normal case
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete p;
				count--;
				return true;
			}
		}
	}
	return false;
}

bool Set::contains(const ItemType& value) const
{
	for (Node* p = head; p != nullptr; p = p->next)
	{
		if (p->data == value)
			return true;
	}
	return false;
}

bool Set::get(int pos, ItemType& value) const
{
	Node* p = head;
	if (pos >= 0 && pos < count)
	{
		for (int k = 0; k < pos; k++)
		{
			p = p->next;
		}
		value = p->data;
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{
	Node* temp = head;
	head = other.head;
	other.head = temp;
	int bemp = count;
	count = other.count;
	other.count = bemp;
}


void subtract(const Set& s1, const Set& s2, Set& result)
{
	result = s1;
	ItemType x;
	Set s3 = s2;

	for (int k = 0; k < s3.size(); k++)
	{
		s3.get(k, x);
		result.erase(x);
	}
}

void unite(const Set& s1, const Set& s2, Set& result)
{
	result = s1;
	ItemType x;
	Set s3 = s2;
	for (int k = 0; k < s3.size(); k++)
	{
		s3.get(k, x);
		result.insert(x);
	}
}
