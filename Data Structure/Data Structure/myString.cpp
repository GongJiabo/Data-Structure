#include"myString.h"

SqString::SqString()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	length = 0;
}

SqString::~SqString()
{

}

int Strcmp(SqString s, SqString t)
{
	int i, comlen;
	if (s.length < t.length) comlen = s.length;
	else comlen = t.length;
	for (i = 0; i < comlen; i++)
	{
		if (s.data[i] > t.data[i])
			return 1;
		else if (s.data[i] < t.data[i])
			return -1;
	}
	if (s.length == t.length)
		return 0;
	else if (s.length > t.length)
		return 1;
	else return -1;
}

int index(SqString s, SqString t)
{
	int i = 0, j = 0;
	while (i < s.length && j < t.length)
	{
		if (s.data[i] == t.data[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= t.length)
		return(i - t.length);
	else
		return -1;
}

void maxsubstr(SqString s, SqString& t)
{
	int maxi = 0, maxlen = 0, len, i, j, k;
	i = 0;
	while (i < s.length)
	{
		j = i + 1;
		while (j < s.length)
		{
			if (s.data[i] == s.data[j])
			{
				len = 1;
				for (k = 1; s.data[i + k] == s.data[j + k]; k++)
					len++;
				if (len > maxlen)
				{
					maxi = i;
					maxlen = len;
				}
				j += len;
			}
			else j++;
		}
		i++;
	}
	t.length = maxlen;
	for (i = 0; i < maxlen; i++)
		t.data[i] = s.data[maxi + i];
}


//链串
LiString::LiString()
{
	head = new SNode;
	head->next = nullptr;
	head->data = '\0';
}

LiString::~LiString()
{
	//头结点也销毁
	SNode* pre = head;
	SNode* p = head->next;
	while (p != nullptr)
	{
		delete(pre);
		pre = p;
		p = pre->next;
	}
}

void LiString::Repl()
{
	SNode* p = head->next, * q;
	int find = 0;
	while (p->next != nullptr && find == 0)
	{
		if (p->data == 'a' && p->next->data == 'b')
		{
			p->data = 'x';
			p->next->data = 'z';
			q = new SNode;
			q->data = 'y';
			q->next = p->next;
			p->next = q;
			find = 1;
		}
	}
}