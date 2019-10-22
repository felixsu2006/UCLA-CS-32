#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
	GenomeImpl(const string& nm, const string& sequence);
	static bool load(istream& genomeSource, vector<Genome>& genomes);
	int length() const;
	string name() const;
	bool extract(int position, int length, string& fragment) const;
private:
	string m_name;
	string dna;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
	m_name = nm;
	dna = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
	string name;
	string dna = "";
	string temp;
	int lines = 0;
	int check = 0;
	bool prevWasLine = false;
	std::vector<string> names;
	std::vector<string> dnas;
	while (getline(genomeSource, temp))
	{
		if (temp.size() == 0)
			return false;
		if (temp[0] == '>')
		{
			check++;
			if (temp.size() == 1)
				return false;
			if (prevWasLine == true)
				return false;
			
			//getline(infile, name);
			//infile.ignore(10000, '\n');
			
			prevWasLine = true;
			if (dna == "" && check == 2)
				return false;
			
			lines++;
			if (check == 2)
			{
				genomes.push_back(Genome(name, dna));
				check = 1;
			}
			name = temp.substr(1);
			dna = "";
			continue;
		}
		else 
		{
			prevWasLine = false;
			if (lines == 0)
				return false;
			lines++;
			for (int k = 0; k != temp.size(); k++)
			{
				temp[k] = toupper(temp[k]);
				if (toupper(temp[k]) != 'A' && toupper(temp[k]) != 'C' && toupper(temp[k]) != 'T' && toupper(temp[k]) != 'G' && toupper(temp[k]) != 'N')
					return false;
			}
			dna += temp;
		}

	}
	if (dna != "")
		genomes.push_back(Genome(name, dna));
	else
		return false;

	return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
	return dna.size();  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
	return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	size_t i = position + length;
	if ((i) > dna.size())
		return false;
	fragment = dna.substr(position, length);
	return true;  // This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
	m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
	delete m_impl;
}

Genome::Genome(const Genome& other)
{
	m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
	GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
	delete m_impl;
	m_impl = newImpl;
	return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
	return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
	return m_impl->length();
}

string Genome::name() const
{
	return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
	return m_impl->extract(position, length, fragment);
}
