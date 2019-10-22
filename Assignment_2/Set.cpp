#include "Set.h"
#include <iostream>
using namespace std;

Set::Set()
{
	count = 0;
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
	if (count >= DEFAULT_MAX_ITEMS)
		return false;

	if (count == 0)
	{
		a[count] = value;
		count++;
		return true;
	}
	int max = count;
	int min = 0;
	int x = 0;
	int mid = (count) / 2;
	while (x == 0)
	{

		if (mid < 0)
			return false;

		if (a[mid] == value)
		{
			return false;
		}

		if (a[mid] > value)
		{
			if (mid == 0)
			{
				if (count == 1)
				{
					a[1] = a[0];
					a[0] = value;
					count++;
					return true;
				}

				for (int k = count; k > 0; k--)
				{
					a[k] = a[k - 1];
				}
				a[mid] = value;
				count++;
				return true;
			}

			if (a[mid - 1] < value)
			{
				for (int k = count; k > mid; k--)
				{
					a[k] = a[k - 1];
				}
				a[mid] = value;
				count++;
				return true;
			}
			max = mid;
			mid = (max + min) / 2;
		}

		if (a[mid] < value)
		{
			if (mid == (count - 1))
			{
				a[count] = value;
				count++;
				return true;
			}

			if (a[mid + 1] > value)
			{
				for (int k = count; k > mid + 1; k--)
				{
					a[k] = a[k - 1];
				}
				a[mid + 1] = value;
				count++;
				return true;
			}

			min = mid;
			mid = (max + min) / 2;
		}
	}
}

bool Set::erase(const ItemType& value)
{

	if (count <= 0)
	{
		return false;
	}
	int max = count;
	int min = 0;
	int x = 0;
	int mid = (count) / 2;
	while (x == 0)
	{

		if (mid < 0)
			return false;

		if (a[mid] == value)
		{
			for (int k = mid; k < count - 1; k++)
			{
				a[k] = a[k + 1];
			}
			count--;
			return true;
		}

		if (a[mid] > value)
		{
			if (mid == 0)
			{
				return false;
			}

			max = mid;
			mid = (max + min) / 2;
		}

		if (a[mid] < value)
		{
			if (mid == (count - 1))
			{
				return false;
			}

			min = mid;
			mid = (max + min) / 2;
		}
	}
}

bool Set::contains(const ItemType& value) const
{
	if (count <= 0)
	{
		return false;
	}
	int max = count;
	int min = 0;
	int x = 0;
	int mid = (count) / 2;
	while (x == 0)
	{

		if (mid < 0)
			return false;

		if (a[mid] == value)
		{
			return true;
		}

		if (a[mid] > value)
		{
			if (mid == 0)
			{
				return false;
			}

			max = mid;
			mid = (max + min) / 2;
		}

		if (a[mid] < value)
		{
			if (mid == (count - 1))
			{
				return false;
			}

			min = mid;
			mid = (max + min) / 2;
		}
	}
}

bool Set::get(int i, ItemType& value) const
{
	if (i >= 0 && i < count)
	{
		value = a[i];
		return true;
	}

	else   
		return false;
}

void Set::swap(Set& other)
{
	ItemType bemp[DEFAULT_MAX_ITEMS];
	for (int k = 0; k < count; k++)
	{
		bemp[k] = a[k];
	}

	for (int k = 0; k < other.count; k++)
	{
		a[k] = other.a[k];
	}

	for (int k = 0; k < count; k++)
	{
		other.a[k] = bemp[k];
	}

	int temp = count;
	count = other.count;
	other.count = temp;
}
