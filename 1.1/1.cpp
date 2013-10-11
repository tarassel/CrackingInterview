// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <functional>

bool IsThereDuplicates(char* str, int nLen)
{
	for (int i=0; i<nLen; i++)
	{
		for (int j=i+1; j<nLen; j++)
		{
			if (str[i] == str[j])
				return true;
		}
	}

	return false;
}

void reverse(char* str)
{
	int nLen = strlen(str);
	char buf;

	for (int i=0; i<nLen/2; i++)
	{
		buf = str[i];
		str[i] = str[nLen-i-1];
		str[nLen-i-1] = buf;
	}
}

bool IsAnnagram1(std::string& str1, std::string& str2)
{
	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());

	return str1 == str2;
}

/*template<class _TFreqTable, class _TElem>
struct ModyFreqTable : public std::binary_function<_TFreqTable, _TElem, bool>
{
	bool operator()(_TFreqTable& freqTable, _TElem element) const
	{
		//freqTable.insert(std::make_pair(element, ++freqTable[element]));
		freqTable[element] = freqTable[element] + 1;
	}
};*/
class ModyFreqTable
{
	std::map<char, int>& _freq;
public:
	ModyFreqTable(std::map<char, int>& freq): _freq(freq) {}
	void operator()(char c)
	{
		_freq[c] = _freq[c] + 1;
	}
};

bool IsAnnagram2(std::string& str1, std::string& str2)
{
	std::map<char, int> freq1;
	std::map<char, int> freq2;
	
	std::for_each(str1.cbegin(), str1.cend(), ModyFreqTable(freq1));
	std::for_each(str2.cbegin(), str2.cend(), ModyFreqTable(freq2));

	return freq1 == freq2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 1.1
	char* str1 = "qwertyuiop12098765";
	char* str2 = "afghjkl;'|frewq12";

	assert(IsThereDuplicates(str1, strlen(str1)) == false);
	assert(IsThereDuplicates(str2, strlen(str2)) == true);

	// 1.2
	str1 = new char[7];
	memcpy(str1, "qwerty", 7);
	str2 = "ytrewq";

	reverse(str1);
	assert(strcmp(str1, str2) == 0);

	// 1.3
	std::string cstr1("qwerty");
	std::string cstr2("ewqtry");
	std::string cstr3("wQrety");

	assert(IsAnnagram1(cstr1, cstr2) == true);
	assert(IsAnnagram1(cstr1, cstr3) == false);

	cstr1 = "qwerty";
	cstr2 = "ewqtry";
	cstr3 = "wQeete";
	assert(IsAnnagram2(cstr1, cstr2) == true);
	assert(IsAnnagram2(cstr1, cstr3) == false);

	return 0;
}

