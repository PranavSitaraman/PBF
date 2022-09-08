#pragma once
#include "PBF.hpp"
template <class T>
class NaivePBF
{
private:
	unsigned long m, n, k, gen = 0;
	long double p;
	std::vector<boost::dynamic_bitset<>*> x;
	std::vector<std::function<unsigned long(T, unsigned long)>> hashes;
public:
	NaivePBF(unsigned long nn, long double pp, std::vector<std::function<unsigned long(T, unsigned long)>> hash)
	{
		n = nn;
		p = pp;
		m = -(n * log(p) * log(M_E)) / (log(2) * log(2));
		k = (m * log(2)) / (n * log(M_E));
		x.push_back(new boost::dynamic_bitset<>(m, 0));
		if (hash.size() != k) throw std::invalid_argument(std::to_string(k) + " hash functions required, " + std::to_string(hash.size()) + " found");
		else hashes = std::vector<std::function<unsigned long(T, unsigned long)>>(hash);
	}
	void insert(T elem)
	{
		x.push_back(new boost::dynamic_bitset<>(*x[gen++]));
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) x[gen]->set(hash(elem, m));
	}
	bool find(T elem)
	{
		boost::dynamic_bitset<>* i = new boost::dynamic_bitset<>(m);
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) i->set(hash(elem, m));
		if ((*i & *x[gen]) == *i) return true;
		return false;
	}
	bool find(T elem, unsigned long generation)
	{
		boost::dynamic_bitset<>* i = new boost::dynamic_bitset<>(m);
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) i->set(hash(elem, m));
		if ((*i & *x[generation]) == *i) return true;
		return false;
	}
	unsigned long size() { return gen; }
	~NaivePBF()
	{
		x.clear();
		x.shrink_to_fit();
		hashes.clear();
		hashes.shrink_to_fit();
	}
};