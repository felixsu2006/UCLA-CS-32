#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>


template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
private:
	struct Node
	{
		std::vector<ValueType> vals;
		std::vector<Node*> children;
		char label;
	};
	Node* root;
	void deleteHelp(Node* n);
	void printHelp(Node* n);
	std::vector<ValueType> findHelp(std::string s, Node* n, bool exactMatchOnly) const;
	
};

/*
template<typename ValueType>
void Trie<ValueType>::print()
{
	printHelp(root);
}

template<typename ValueType>
void Trie<ValueType>::printHelp(Node* n)
{
	std::cerr << n->label << std::endl;
	for (int j = 0; j != n->vals.size(); j++)
	{
		std::cerr << n->vals[j] << " ";
		if (j == n->vals.size() - 1)
			std::cerr << std::endl;
	}


	for (int k = 0; k != n->children.size(); k++)
	{
		printHelp(n->children[k]);
	}
}
*/
template<typename ValueType>
Trie<ValueType>::Trie()
{
	root = new Node;
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
	deleteHelp(root);
	delete root;
}

template<typename ValueType>
void Trie<ValueType>::deleteHelp(Node* n)
{
	for (typename std::vector<Node*>::iterator it = n->children.begin(); it != n->children.end();)
	{
		deleteHelp(*it);
		delete (*it);
		it = n->children.erase(it);
	}
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
	deleteHelp(root);
	delete root;
	root = new Node;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
	Node* temp;
	temp = root;
	for (int k = 0; k != key.size(); k++)
	{
		if (temp->children.size() == 0)
		{
			Node* dank = new Node;
			dank -> label = key[k];
			temp->children.push_back(dank);
			temp = temp->children[0];
		}
		for (int j = 0; j != temp->children.size(); j++)
		{
			if (temp->children[j]->label == key[k])
			{
				temp = temp->children[j];
				break;
			}
			if (j == temp->children.size() - 1)
			{
				Node* dank = new Node;
				dank->label = key[k];
				temp->children.push_back(dank);
			}
		}
		if (k == key.size() - 1)
		{
			temp->vals.push_back(value);
		}
	}
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelp(std::string s, Node* n, bool exactMatchOnly) const
{
	std::vector<ValueType> returnVals;
	for (int k = 0; k != n->children.size(); k++)
	{
		
		if (exactMatchOnly == false)
		{
			if (s.size() == 1)
			{
				std::vector<ValueType> a = n->children[k]->vals;
				returnVals.insert(returnVals.end(), a.begin(), a.end());
				continue;
			}
			if (n->children[k]->label == s[0])
			{
				std::vector<ValueType> c = findHelp(s.substr(1, s.size() - 1), n->children[k], false);
				returnVals.insert(returnVals.end(), c.begin(), c.end());
				continue;
			}
			std::vector<ValueType> a = findHelp(s.substr(1, s.size() - 1), n->children[k], true);
			returnVals.insert(returnVals.end(), a.begin(), a.end());
			continue;
		}
		if (n->children[k]->label == s[0])
		{
			if (s.size() == 1)
			{
				std::vector<ValueType> a = n->children[k]->vals;
				returnVals.insert(returnVals.end(), a.begin(), a.end());
				break;
			}
			//std::cerr << "asd";
			std::vector<ValueType> b = findHelp(s.substr(1, s.size() - 1), n->children[k], exactMatchOnly);
			returnVals.insert(returnVals.end(), b.begin(), b.end());
		}
	}
	return returnVals;

}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
	if (key == "")
		return {};
	for (int k = 0; k != root->children.size(); k++)
	{
		if (root->children[k]->label == key[0])
			return findHelp(key.substr(1, key.size() - 1), root->children[k], exactMatchOnly);
	}
	return {};
}
#endif // TRIE_INCLUDED
