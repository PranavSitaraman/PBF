#pragma once
#include "PBF.hpp"
#include "SinglePBF.hpp"
template <class T>
class PBF2
{
private:
	unsigned long m, n, t, u;
	long double p;
	std::vector<std::function<unsigned long(T, unsigned long)>> hashes;
	std::vector<SinglePBF<T>*> bfs;
	bool query(unsigned long index, unsigned long l, unsigned long r, T elem, unsigned long start, unsigned long end)
	{
		if (start <= l && r <= end)
		{
			unsigned long ll = floor(log(index) / log(2));
			unsigned long g = powl(2, u - 1 - ll);
			unsigned long j = ceil((long double)l / g);
			boost::dynamic_bitset<>* i = new boost::dynamic_bitset<>(m);
			for (std::function<unsigned long(T, unsigned long)> hash : hashes) i->set((hash(elem, m) + j) % m);
			if ((*i & *(bfs[ll]->x)) == *i) return true;
		}
		if (start <= (l + r) / 2 && end >= l && index * 2 <= powl(2, u) - 1) if (query(index * 2, l, (l + r) / 2, elem, start, end)) return true;
		if (start <= r && end >= (l + r) / 2 + 1 && index * 2 + 1 <= powl(2, u) - 1) if (query(index * 2 + 1, (l + r) / 2 + 1, r, elem, start, end)) return true;
		return false;
	}
public:
	PBF2(unsigned long nn, long double pp, unsigned long tt, std::vector<std::function<unsigned long(T, unsigned long)>> hash)
	{
		n = nn;
		p = pp;
		t = powl(2.0, ceil(log(tt) / log(2)));
		u = ceil(log(t) / log(2)) + 1;
		m = ceil((-(n * log(p) * log(M_E)) / (log(2) * log(2))) / (u));
		hashes = std::vector<std::function<unsigned long(T, unsigned long)>>(hash);
		for (unsigned long i = 0; i < u; i++) bfs.push_back(new SinglePBF<T>(m));
	}
	void insert(T elem, unsigned long time)
	{
		for (unsigned long i = 0; i < u; i++)
		{
			unsigned long val = ceil(time / powl(2, u - 1 - i));
			for (std::function<unsigned long(T, unsigned long)> hash : hashes) bfs[i]->x->set((hash(elem, m) + val) % m);
		}
	}
	bool query(T elem, unsigned long start, unsigned long end)
	{
		return query(1, 1, t, elem, start, end);
	}
	~PBF2()
	{
		for (SinglePBF<T>* i : bfs) delete i;
		bfs.clear();
		bfs.shrink_to_fit();
		hashes.clear();
		hashes.shrink_to_fit();
	}
};