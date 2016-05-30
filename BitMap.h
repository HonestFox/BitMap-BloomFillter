#pragma once

#include <iostream>
#include <vector>
//位图
using namespace std;
class BitMap
{
public:
	BitMap(size_t n)
		:_size(0)
	{
		_a.resize( (n >> 5) + 1);
	}
	void Set(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if ((_a[index] & (1 << num)) == 0)	//不存在的话，添加并增加_size
		{
			_a[index] |= (1 << num);
			_size++;
		}
	}
	void ReSet(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if ((_a[index] & (1 << num)) != 0)	//存在的话，移除并减小_size
		{
			_a[index] &= ~(1 << num);
			_size--;
		}
	}
	bool Test(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		return _a[index] & (1 << num);
	}
protected:
	vector<size_t> _a;
	size_t _size;
};




/*

=====================================================================================
				布隆过滤器
=====================================================================================
*/

struct __HashFunc1
{
	size_t SDBMHash(char *str)
	{
		size_t hash = 0;
		while (*str)
		{
			hash = (*str++) + (hash << 6) + (hash << 16) - hash;
		}
		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string &key)
	{
		return (SDBMHash((char*)key.c_str()));
	}
};


struct __HashFunc2
{
	unsigned int RSHash(char *str)
	{
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		while (*str)
		{
			hash = hash * a + (*str++);
			a *= b;
		}

		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string &key)
	{
		return (RSHash((char*)key.c_str()));
	}
};

struct __HashFunc3
{
	unsigned int RSHash(char *str)
	{
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		while (*str)
		{
			hash = hash * a + (*str++);
			a *= b;
		}

		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string &key)
	{
		return (RSHash((char*)key.c_str()));
	}
};
struct __HashFunc4
{
	unsigned int JSHash(char *str)
	{
		unsigned int hash = 1315423911;

		while (*str)
		{
			hash ^= ((hash << 5) + (*str++) + (hash >> 2));
		}

		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string &key)
	{
		return (JSHash((char*)key.c_str()));
	}
};
struct __HashFunc5
{
	unsigned int PJWHash(char *str)
	{
		unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
		unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt * 3) / 4);
		unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
		unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
		unsigned int hash = 0;
		unsigned int test = 0;

		while (*str)
		{
			hash = (hash << OneEighth) + (*str++);
			if ((test = hash & HighBits) != 0)
			{
				hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
			}
		}

		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string &key)
	{
		return (PJWHash((char*)key.c_str()));
	}
};

//布隆过滤器
template<
class HashFunc1 = __HashFunc1,
class HashFunc2 = __HashFunc2,
class HashFunc3 = __HashFunc3,
class HashFunc4 = __HashFunc4,
class HashFunc5 = __HashFunc5
>
class BloomFillter
{
public:
	BloomFillter(size_t n)
		:_capacity(_GetNextPrime(n))
		,_bm(_capacity)
	{}

	void Set(const string &key)
	{
		size_t hash1 = HashFunc1()(key);
		size_t hash2 = HashFunc2()(key);
		size_t hash3 = HashFunc3()(key);
		size_t hash4 = HashFunc4()(key);
		size_t hash5 = HashFunc5()(key);
		_bm.Set(hash1 % _capacity);
		_bm.Set(hash2 % _capacity);
		_bm.Set(hash3 % _capacity);
		_bm.Set(hash4 % _capacity);
		_bm.Set(hash5 % _capacity);

	}

	bool Test(const string &key)
	{
		size_t hash1 = HashFunc1()(key);
		if (!_bm.Test(hash1 % _capacity))
		{
			return false;
		}
		size_t hash2 = HashFunc2()(key);
		if (!_bm.Test(hash2 % _capacity))
		{
			return false;
		}
		size_t hash3 = HashFunc3()(key);
		if (!_bm.Test(hash3 % _capacity))
		{
			return false;
		}
		size_t hash4 = HashFunc4()(key);
		if (!_bm.Test(hash4 % _capacity))
		{
			return false;
		}
		size_t hash5 = HashFunc5()(key);
		if (!_bm.Test(hash5 % _capacity))
		{
			return false;
		}
		return true;
	}


protected:
	size_t _GetNextPrime(size_t n)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (int i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > n)
			{
				return _PrimeList[i];
			}
		}
		return n;
	}
protected:
	size_t _capacity;
	BitMap _bm;
};
