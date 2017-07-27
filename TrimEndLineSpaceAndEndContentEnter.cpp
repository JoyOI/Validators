#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct RetInfo{
	bool flag;
	char *ptr;
	RetInfo(){};
	RetInfo(bool f, char *p) :flag(f), ptr(p)
	{
	}
};

const int AC_CODE = 0, PE_CODE = 1, WA_CODE = 2;//return code
const int MaxSize = 100 * 1024 * 1024;//100MB
char OutData[MaxSize], StdData[MaxSize];//Data
char *OutPtr, *StdPtr;//Data pointer
int CountLine = 1;
//Var and arr
int AC();
int WA();
int PE();
//Return information
inline bool IsBlank1(const char t);
inline bool IsBlank2(const char t);
RetInfo EndOfLine(char* p);
bool EndOfFile(char* p);
char* SkipBlank(char* p);
//Functions for Judge()
int Judge();

int main(int argc, char* argv[], char* envp[])
{
	FILE *OutDataFP,*StdDataFP;
	if (argc < 3)
	{
		OutDataFP = fopen("out.txt","r");
		StdDataFP = fopen("std.txt","r");
	}
	else
    	{
        	OutDataFP = fopen(argv[1],"r");
		StdDataFP = fopen(argv[2],"r");
    	}

	fread(OutData,sizeof(char),MaxSize,OutDataFP);
	fread(StdData,sizeof(char),MaxSize,StdDataFP);
	auto RET = Judge();
	fclose(OutDataFP);
	fclose(StdDataFP);
	return RET;
}

int AC()
{
	return AC_CODE;
}

int WA()
{
	char *StdPtrT = max((char*)StdData, StdPtr - 10), *OutPtrT = max((char*)OutData, OutPtr - 10);
	int i;
	cout << "<p>第<span style='color:red'>" << CountLine << "</span>行与答案输出不匹配</p>" << endl;
	cout << "<p>答案输出：</p><pre>";
	if (StdPtrT != StdData)
		cout << "...";
	for (; StdPtrT != StdPtr; ++StdPtrT)
		cout << *StdPtrT;
	for (i = 0; i < 10 && *StdPtrT != '\0'; ++i, ++StdPtrT)
		cout << *StdPtrT;
	if (*StdPtrT != '\0')
		cout << "...";
	cout << "</pre>" << endl;
	cout << "<p>选手输出：</p><pre>";
	if (OutPtrT != OutData)
		cout << "...";
	for (; OutPtrT != OutPtr; ++OutPtrT)
		cout << *OutPtrT;
	for (i = 0; i < 10 && *OutPtrT != '\0'; ++i, ++OutPtrT)
		cout << *OutPtrT;
	if (*OutPtrT != '\0')
		cout << "...";
	cout << "</pre>" << endl;
	return WA_CODE;
}

int PE()
{
	return PE_CODE;
}

inline bool IsBlank1(const char t)
{
	return t == ' ' || t == '\r' || t == '\t';
}

inline bool IsBlank2(const char t)
{
	return t == ' ' || t == '\r' || t == '\t' || t == '\n';
}

char* SkipBlank(char* p)
{
	while (IsBlank2(*p))
	{
		if (*p == '\n')
			++CountLine;
		++p;
	}
	return p;
}

RetInfo EndOfLine(char* p)
{
	while (IsBlank1(*p))
		++p;
	return RetInfo(*p == '\n' || *p == '\0', p);
}

bool EndOfFile(char* p)
{
	while (IsBlank2(*p))
		++p;
	return *p == '\0';
}

int Judge()
{
	RetInfo ret1, ret2;
	bool Skip = false;
	StdPtr = StdData;
	OutPtr = OutData;
	while (*StdPtr != '\0' && *OutPtr != '\0')
	{
		if (*StdPtr == '\n')
			++CountLine;
		if (*StdPtr != *OutPtr)
		{
			ret1 = EndOfLine(StdPtr);
			ret2 = EndOfLine(OutPtr);
			if (ret1.flag && ret2.flag)
			{
				StdPtr = ret1.ptr;
				OutPtr = ret2.ptr;
			}
			else
			{
				StdPtr = SkipBlank(ret1.ptr);
				OutPtr = SkipBlank(ret2.ptr);
				Skip = true;
			}
			if (*StdPtr != *OutPtr && *StdPtr != '\0' && *OutPtr != '\0')
				return WA();
		}
		++StdPtr;
		++OutPtr;
	}
	if (EndOfFile(StdPtr) == false || EndOfFile(OutPtr) == false)
		return WA();
	return Skip ? PE() : AC();
}
