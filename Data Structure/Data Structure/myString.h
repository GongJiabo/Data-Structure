#pragma once
const int MAXSIZE = 100;

//顺序串
class SqString
{
private:
	int data[MAXSIZE];
	int length;

public:
	SqString();
	~SqString();

	//比较字符串大小
	//相等：0
	//大于：1
	//小于：-1
	friend int Strcmp(SqString s, SqString t);
	
	//寻找子串
	friend int index(SqString s, SqString t);

	//求最长重复子串
	friend void maxsubstr(SqString s, SqString& t);

	//StrAssign(cstr);
	//StrCopy(t);
	//StrEqual(t);
	//StrLength();
	//Concat(s,t);
	//SubStr(int i, int j);
};

//链串
struct SNode
{
	char data;
	SNode* next;
};

class LiString
{
private:
	SNode* head;

public:
	LiString();
	~LiString();

	void Repl();
};