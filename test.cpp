#include <iostream>
#include "BitMap.h"
using namespace  std;
void TestBitMap()
{
	BitMap bm(100);
	bm.Set(12);
	bm.Set(21);
	bm.Set(32);
	bm.Set(45);
	bm.Set(80);
	bm.Set(66);
	bm.Set(99);
	bm.Set(99);

	cout << "12: " << bm.Test(12) << endl;
	cout << "21: " << bm.Test(21) << endl;
	cout << "32: " << bm.Test(32) << endl;
	cout << "45: " << bm.Test(45) << endl;
	cout << "80: " << bm.Test(80) << endl;
	cout << "102: " << bm.Test(66) << endl;
	cout << "99: " << bm.Test(99) << endl;
	cout << "77: " << bm.Test(77) << endl;

	bm.ReSet(45);
	bm.ReSet(45);

	cout << endl;
	cout << "12: " << bm.Test(12) << endl;
	cout << "21: " << bm.Test(21) << endl;
	cout << "32: " << bm.Test(32) << endl;
	cout << "45: " << bm.Test(45) << endl;
	cout << "80: " << bm.Test(80) << endl;
	cout << "102: " << bm.Test(66) << endl;
	cout << "99: " << bm.Test(99) << endl;
	cout << "77: " << bm.Test(77) << endl;
}

void TestBitMap1()
{
	BitMap bm(100);
	bm.Set(12);
	cout << "12: " << bm.Test(12) << endl;
}

void TestBloomFilter()
{
	BloomFillter<> bf(100);
	bf.Set("NiuX");
	bf.Set("DiaoSi");
	bf.Set("porgrammer");
	bf.Set("Coder");

	cout << bf.Test("NiuX") << endl;
	cout << bf.Test("DiaoSi") << endl;
	cout << bf.Test("porgrammer") << endl;
	cout << bf.Test("Coder") << endl;
	cout << bf.Test("coder") << endl;


}
int main()
{
	TestBloomFilter();
	return 0;
}
