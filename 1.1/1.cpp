// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include <vector>
#include <sstream>

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

//#define _AFX_SECURE_NO_WARNINGS
// nSize is buffer size
void ReplaceSpaces1(char* pStr, int nSize)
{
	std::string str(pStr, pStr + nSize);

	std::string::size_type nPos = str.find(" ");
	while (nPos != std::string::npos)
	{
		str.replace(nPos, 1, "%20");
		nPos = str.find(" ");
	}
	str.copy(pStr, nSize - 1);
	pStr[nSize - 1] = '\0';
}

// nSize is buffer size
void ReplaceSpaces2(char* pStr, int nSize)
{
//	char* pStrTmp = new char[nSize];
	std::unique_ptr<char> pStrTmp(new char[nSize]);
	char* pPos = pStrTmp.get();

	for (int i=0; i<nSize && (pStr[i] != '\0'); i++)
	{
		if (pStr[i] == ' ')
		{
			memcpy(pPos, "%20", 3);
			pPos +=3;
		}
		else
		{
			*pPos = pStr[i];
			++pPos;
		}
	}
	*pPos = '\0';

	memcpy(pStr, pStrTmp.get(), pPos-pStrTmp.get());

//	delete[] pStrTmp;
}

// nSize is string size excl zero
void ReplaceSpaces3(char* pStr, int nSize)
{
	int nSpaceCount = 0, nNewSize = 0;
	for (int i=0; i<nSize; ++i)
		if (pStr[i] == ' ')
			++nSpaceCount;
	nNewSize = nSize + nSpaceCount * 2;

	pStr[nNewSize] = '\0';
	for (int i=nSize-1; i>=0; --i)
	{
		if (pStr[i] == ' ')
		{
			pStr[nNewSize - 1] = '0';
			pStr[nNewSize - 2] = '2';
			pStr[nNewSize - 3] = '%';
			nNewSize -= 3;
		}
		else
		{
			pStr[nNewSize - 1] = pStr[i];
			nNewSize -= 1;
		}
	}
}

std::string Compress(std::string& str)
{
	if (str.size() <= 0)
		return str;

	std::ostringstream res;
//	std::string res;
	char cCurrChar = str[0];
	int nCount = 1;

	for(int i=1; i<str.size(); ++i)
	{
		if (cCurrChar == str[i])
			++nCount;
		else
		{
			res << cCurrChar << nCount;
// 			res.push_back(cCurrChar);
// 			res.push_back(std::to_string(i));
			cCurrChar = str[i];
			nCount = 1;
		}
	}

	res << cCurrChar << nCount;

	res.seekp(0, std::ios::end);
	if (str.size() < res.tellp())
		return str;
	else
		return res.str();
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

	char* pStr = new char[100];
	strcpy(pStr, "  34 678 ");
	ReplaceSpaces1(pStr, 100);
	assert(strcmp(pStr, "%20%2034%20678%20") == 0);
	strcpy(pStr, "  34 678 ");
	ReplaceSpaces2(pStr, 100);
	assert(strcmp(pStr, "%20%2034%20678%20") == 0);
	strcpy(pStr, "  34 678 ");
	ReplaceSpaces3(pStr, 9);
	assert(strcmp(pStr, "%20%2034%20678%20") == 0);

	assert(Compress(std::string("aabcccccaaa")) == "a2b1c5a3");

	return 0;
}

