#pragma once
#include "PBF.hpp"
template <class T>
class SinglePBF
{
private:
	unsigned long m;
public:
	boost::dynamic_bitset<>* x;
	SinglePBF(unsigned long mm)
	{
		m = mm;
		x = new boost::dynamic_bitset<>(m, 0);
	}
	void insert(T elem, std::vector<std::function<unsigned long(T, unsigned long)>> hashes)
	{
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) x->set(hash(elem, m));
	}
	bool find(T elem, std::vector<std::function<unsigned long(T, unsigned long)>> hashes)
	{
		boost::dynamic_bitset<>* i = new boost::dynamic_bitset<>(m);
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) i->set(hash(elem, m));
		if ((*i & *x) == *i) return true;
		return false;
	}
	~SinglePBF()
	{
		delete x;
	}
};