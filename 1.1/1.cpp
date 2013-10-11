// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <cstring>
#include <string>
#include <algorithm>

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

bool IsAnnagram2(std::string& str1, std::string& str2)
{
	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());

	return str1 == str2;
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

	assert(IsAnnagram2(cstr1, cstr2) == true);
	assert(IsAnnagram2(cstr1, cstr3) == false);

	return 0;
}

