#pragma once
#include "PBF.hpp"
#include "SinglePBF.hpp"
template <class T>
class PBF1
{
private:
	unsigned long m, n, g, t, u, l;
	long double p;
	SinglePBF<T>* sbf;
	std::vector<SinglePBF<T>*> bfs;
	std::vector<std::function<unsigned long(T, unsigned long)>> hashes;
	void insert(unsigned long index, unsigned long l, unsigned long r, T elem, unsigned long time)
	{
		bfs[index - 1]->insert(elem, hashes);
		if (time <= (l + r) / 2 && index * 2 <= u) insert(index * 2, l, (l + r) / 2, elem, time);
		else if (index * 2 + 1 <= u) insert(index * 2 + 1, (l + r) / 2 + 1, r, elem, time);
	}
	bool query(unsigned long index, unsigned long l, unsigned long r, T elem, unsigned long start, unsigned long end)
	{
		if (start <= l && r <= end) return bfs[index - 1]->find(elem, hashes);
		if (r - l + 1 == g && start <= r && end >= l)
		{
			for (unsigned long j = std::max(start, l); j <= std::min(end, r); j++)
			{
				boost::dynamic_bitset<>* i = new boost::dynamic_bitset<>(m);
				for (std::function<unsigned long(T, unsigned long)> hash : hashes) i->set((hash(elem, m) + j) % m);
				if ((*i & *(sbf->x)) == *i) return true;
			}
		}
		if (start <= (l + r) / 2 && end >= l && index * 2 <= u) if (query(index * 2, l, (l + r) / 2, elem, start, end)) return true;
		if (start <= r && end >= (l + r) / 2 + 1 && index * 2 + 1 <= u) if (query(index * 2 + 1, (l + r) / 2 + 1, r, elem, start, end)) return true;
		return false;
	}
public:
	PBF1(unsigned long nn, long double pp, unsigned long gg, unsigned long tt, std::vector<std::function<unsigned long(T, unsigned long)>> hash)
	{
		n = nn;
		p = pp;
		t = tt;
		t = powl(2.0, ceil(log(t) / log(2)));
		g = gg;
		g = powl(2.0, floor(log(g) / log(2)));
		l = ceil(log(ceil((long double)(t) / (long double)(g))) / log(2)) + 1;
		u = powl(2.0, l) - 1;
		m = ceil((-(n * log(p) * log(M_E)) / (log(2) * log(2))) / (u + 1));
		hashes = std::vector<std::function<unsigned long(T, unsigned long)>>(hash);
		sbf = new SinglePBF<T>(m);
		for (unsigned long i = 0; i < u; i++) bfs.push_back(new SinglePBF<T>(m));
	}
	void insert(T elem, unsigned long time)
	{
		for (std::function<unsigned long(T, unsigned long)> hash : hashes) sbf->x->set((hash(elem, m) + time) % m);
		insert(1, 1, t, elem, time);
	}
	bool query(T elem, unsigned long start, unsigned long end)
	{
		return query(1, 1, t, elem, start, end);
	}
	~PBF1()
	{
		delete sbf;
		for (SinglePBF<T>* i : bfs) delete i;
		bfs.clear();
		bfs.shrink_to_fit();
		hashes.clear();
		hashes.shrink_to_fit();
	}
};
