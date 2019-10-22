#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
	GenomeMatcherImpl(int minSearchLength);
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:

	int min_length;
	std::vector<Genome> genes;
	Trie<DNAMatch> t;
	struct nameIndex
	{
		std::string name;
		int length;
		int index;

		nameIndex(int k, const std::string& s, int i) : length(k), name(s), index(i) {}
		bool operator < (const nameIndex& nm) const
		{
			return (name < nm.name);
		}
	};
	
	struct tempGenMatch
	{
		std::string name;
		double proportion;
		bool operator < (const tempGenMatch& temp) const
		{
			return(proportion > temp.proportion) || ((proportion == temp.proportion) && (name < temp.name));

		}
	};

};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	min_length = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	genes.push_back(genome);
	for (size_t k = 0; k < genome.length() - min_length + 1; k++)
	{
		string s;
		genome.extract(k, min_length, s);
		DNAMatch dna;
		dna.position = k;
		dna.genomeName = genome.name();
		dna.length = min_length;
		t.insert(s, (dna));
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return min_length;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (fragment.size() < minimumLength)
		return false;
	if (minimumLength < minimumSearchLength())
		return false;
	int origSize = matches.size();
	int check = 0;
	vector<DNAMatch> holder = t.find(fragment.substr(0, min_length), exactMatchOnly);
	vector<bool> checker;
	for (size_t k = 0; k < holder.size(); k++)
	{
		checker.push_back(true);
	}

	for (size_t i = 0; i < holder.size(); i++)
	{
		for (size_t j = 0; j < genes.size(); j++)
		{
			int forCheck = 0;
			if (holder[i].genomeName == genes[j].name())
			{
				forCheck = 1;
				if (holder[i].position + holder[i].length > genes[j].length())
				{
					checker[i] = false;
					break;
				}

				bool hasBeenFalse = false;
				string temp;
				bool asdf = genes[j].extract(holder[i].position, fragment.size(), temp);
				if (!asdf)
					return false;
				for (size_t k = 0; k < fragment.size(); k++)
				{
					if (fragment[k] != temp[k] && exactMatchOnly)
					{
						break;
					}
					if (fragment[k] != temp[k] && !hasBeenFalse)
					{
						if (k >= min_length)
							holder[i].length++;
						hasBeenFalse = true;
					}
					else if (fragment[k] != temp[k] && hasBeenFalse)
					{
						break;
					}
					else if (k >= (min_length))
						holder[i].length++;
				}
			}
			if (forCheck == 1)
				break;
		}
	}
	string tempName = "";
	int tempLength;
	int index;
	//vector<DNAMatch> tempHolder = holder;
	vector<nameIndex> nam;
	for (size_t k = 0; k < holder.size(); k++)
	{
		nameIndex tempNameIndex(holder[k].length, holder[k].genomeName, k);
		nam.push_back(tempNameIndex);
	}

	
	std::sort(nam.begin(), nam.end());

	
	for (size_t k = 0; k < holder.size(); k++)
	{
		if (nam[k].length < minimumLength)
		{
			checker[nam[k].index] = false;
			continue;
		}
		if (nam[k].name != tempName)
		{
			tempName = nam[k].name;
			tempLength = nam[k].length;
			index = nam[k].index;
			continue;
		}
		if (nam[k].length > tempLength)
		{
			checker[index] = false;
			index = nam[k].index;
			tempLength = nam[k].length;
		}
		else
		{
			checker[nam[k].index] = false;
		}
	}
	for (size_t k = 0; k < holder.size(); k++)
	{
		if (checker[k])
		{
			matches.push_back(holder[k]);
		}
	}
	if (matches.size() == origSize)
		return false;
	return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	double percent = matchPercentThreshold / 100;
	if (fragmentMatchLength < min_length)
		return false;
	int numSeq = (query.length() / fragmentMatchLength);
	vector<int> count;
	for (int k = 0; k != genes.size(); k++)
	{
		count.push_back(0);
	}
	vector<DNAMatch> temp;
	for (int k = 0; k < numSeq; k++)
	{

		string dink;
		bool check = query.extract(k*fragmentMatchLength, fragmentMatchLength, dink);
		if (!check)
			return false;
		findGenomesWithThisDNA(dink, fragmentMatchLength, exactMatchOnly, temp);
	}

	for (int j = 0; j != temp.size(); j++)
	{
		for (int i = 0; i != genes.size(); i++)
		{
			if (temp[j].genomeName == genes[i].name())
			{
				count[i]++;
				break;
			}
		}
	}
	vector<tempGenMatch> tempGen;
	for (int k = 0; k != count.size(); k++)
	{
		if (count[k] > 0)
		{
			double check = count[k] / (double)numSeq;
			if (check >= percent)
			{
				tempGenMatch g;
				g.name = genes[k].name();
				g.proportion = check;
				tempGen.push_back(g);
			}
		}
	}
	sort(tempGen.begin(), tempGen.end());
	for (int k = 0; k < tempGen.size(); k++)
	{
		GenomeMatch g;
		g.genomeName = tempGen[k].name;
		g.percentMatch = tempGen[k].proportion * (double)100;
		results.push_back(g);
	}

	return true;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
	m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
	delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
	m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
	return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
