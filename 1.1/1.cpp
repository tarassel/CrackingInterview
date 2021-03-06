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
#include <memory>
#include <set>

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

	for(std::string::size_type i=1; i<str.size(); ++i)
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

void Transpose(int** matrix, const int n)
{
	int tmp;

	for (int i=0; i<n; ++i)
		for (int j=i; j<n; ++j)
		{
			tmp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tmp;
		}
}

void ReverseRows(int** matrix, const int n)
{
	int tmp;

	for (int i=0; i<n; ++i)
		for (int j=0; j<n/2; ++j)
		{
			tmp = matrix[i][j];
			matrix[i][j] = matrix[i][n - j - 1];
			matrix[i][n - j - 1] = tmp;
		}
}

void PrintMatrix(int** matrix, const int x, const int y)
{
	printf("\n");
	for (int i=0; i<y; ++i)
	{
		for (int j=0; j<x; ++j)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void Rotare(int** matrix, int n)
{
	printf("Input:\n");
	PrintMatrix(matrix, n, n);

	Transpose(matrix, n);

	printf("Transposed:\n");
	PrintMatrix(matrix, n, n);

	ReverseRows(matrix, n);

	printf("Out:\n");
	PrintMatrix(matrix, n, n);
}

/*class MakeNulls
{
public:
	enum RowCol{
		row,
		col
	};

	MakeNulls(int** matrix, RowCol rowcol, int len)
		: _matrix(matrix), _rowcol(rowcol), _len(len) {}
	void operator() (int elem)
	{
		for (int i=0; i<_len; ++i)
			if (_rowcol == row)
				_matrix[elem][i] = 0;
			else
				_matrix[i][elem] = 0;
	}
private:
	int** _matrix;
	RowCol _rowcol;
	int _len;
};*/

void SetZeros(int** matrix, int x, int y)
{
	std::set<int> rowsToNull, colsToNull;

	for (int i=0; i<y; ++i)
		for (int j=0; j<x; ++j)
			if (matrix[i][j] == 0)
			{
				rowsToNull.insert(i);
				colsToNull.insert(j);
			}

// 	MakeNulls nullRows(matrix, MakeNulls::RowCol::row, x);
// 	std::for_each(rowsToNull.begin(), rowsToNull.end(), nullRows);
// 	MakeNulls nullCols(matrix, MakeNulls::RowCol::col, y);
// 	std::for_each(colsToNull.begin(), colsToNull.end(), nullCols);

	for (std::set<int>::const_iterator i=rowsToNull.begin(); i!=rowsToNull.end(); ++i)
	{
		for (int j=0; j<x; ++j)
			matrix[*i][j] = 0;
	}
	for (std::set<int>::const_iterator i=colsToNull.begin(); i!=colsToNull.end(); ++i)
	{
		for (int j=0; j<y; ++j)
			matrix[j][*i] = 0;
	}
}

bool IsRotation(std::string& s1, std::string& s2)
{
	s2 += s2;
	if (s2.find(s1) == std::string::npos)
		return false;
	else
		return true;
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

	const int cnSize = 4;
	int matrix[cnSize][cnSize] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};
	int** pMatrix = new int*[cnSize];
	for (int i=0; i<cnSize; ++i)
		pMatrix[i] = new int[cnSize];
	for (int i=0; i<cnSize; ++i)
		for (int j=0; j<cnSize; ++j)
			pMatrix[i][j] = matrix[i][j];

	Rotare(pMatrix, cnSize);

	const int cnX = 4, cnY = 3;
	int matrix1[cnY][cnX] = {
		{1,2,3,0},
		{5,6,7,8},
		{9,0,1,2}
	};
	int** pMatrix1 = new int*[cnY];
	for (int i=0; i<cnY; ++i)
		pMatrix1[i] = new int[cnX];
	for (int i=0; i<cnY; ++i)
		for (int j=0; j<cnX; ++j)
			pMatrix1[i][j] = matrix1[i][j];
	printf("\nSetZeros IN:\n");
	PrintMatrix(pMatrix1, cnX, cnY);
	SetZeros(pMatrix1, cnX, cnY);
	printf("SetZeros OUT:\n");
	PrintMatrix(pMatrix1, cnX, cnY);

	std::string s1("waterbottle");
	std::string s2("erbottlewat");
	assert(IsRotation(s1, s2) == true);

	return 0;
}

