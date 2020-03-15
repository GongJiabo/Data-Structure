#pragma once
extern const int MaxSize;

//顺序栈
template<class ElemType>
class SqStack
{
private:
	ElemType data[MaxSize];
	int top;
public:
	SqStack();
	~SqStack();

	bool StackEmpty();
	bool Push(ElemType e);
	bool Pop(ElemType& e);
	bool GetTop(ElemType& e);

	bool Symmery(ElemType str[]);
};

//链栈
template<class ElemType>
struct LinkNode
{
	ElemType data;
	LinkNode* next;
};

template<class ElemType>
class LiStack
{
private:
	LinkNode<ElemType>* top;
public:
	LiStack();
	~LiStack();

	bool StackEmpty();
	void Push(ElemType e);
	void Pop(ElemType& e);
	bool GetTop(ElemType& e);

	bool Match(char exp[], int n);
};



//顺序栈的实现
template<class ElemType>
SqStack<ElemType>::SqStack()
{
	top = -1;
}

template<class ElemType>
SqStack<ElemType>::~SqStack()
{

}

template<class ElemType>
bool SqStack<ElemType>::StackEmpty()
{
	return(top == -1);
}

template<class ElemType>
bool SqStack<ElemType>::Push(ElemType e)
{
	if (top == MaxSize - 1)
		return false;
	top++;
	data[top] = e;
	return true;
}

template<class ElemType>
bool SqStack<ElemType>::Pop(ElemType& e)
{
	if (top == -1)
		return false;
	e = data[top];
	top--;
	return true;
}
template<class ElemType>
bool SqStack<ElemType>::GetTop(ElemType& e)
{
	if (top == -1)
		return false;
	e = data[top];
	return true;
}

template<class ElemType>
bool SqStack<ElemType>::Symmery(ElemType str[])
{
	int i;
	ElemType e;

	for (int i = 0; str[i] != '\0'; i++)
		Push(str[i]);

	for (i = 0; str[i] != '\0'; i++)
	{
		Pop(e);
		if (str[i] != e)
			return false;
	}
	return true;
}


//链栈的实现
template<class ElemType>
LiStack<ElemType>::LiStack()
{
	top = new LinkNode<ElemType>;
	top->next = nullptr;
}

template<class ElemType>
LiStack<ElemType>::~LiStack()
{
	LinkNode<ElemType>* p = top, * q = top->next;
	while (q != nullptr)
	{
		delete p;
		p = q;
		q = p->next;
	}
	delete p;
}


template<class ElemType>
bool LiStack<ElemType>::StackEmpty()
{
	return(top->next == nullptr);
}

template<class ElemType>
void LiStack<ElemType>::Push(ElemType e)
{
	LinkNode<ElemType>* p;
	p->data = e;
	p->next = top->next;
	top->next = p;
}

template<class ElemType>
void LiStack<ElemType>::Pop(ElemType& e)
{
	LinkNode<ElemType>* p;
	if (top->next == nullptr)
		return false;
	p = top->next;
	e = p->data;
	top->next = p->next;
	delete p;
	return true;
}

template<class ElemType>
bool LiStack<ElemType>::GetTop(ElemType& e)
{
	if (top->next == nullptr)
		return false;
	e = top->next->data;
	return true;
}

template<class ElemType>
bool LiStack<ElemType>::Match(char exp[], int n)
{
	int i = 0;
	char e;
	bool match = true;

	while (i < n && match)
	{
		if (exp[i] == '(')
			Push(exp[i]);
		else if (exp[i] == ')')
		{
			if (GetTop(e) == true)
			{
				if (e != '(')
					match = false;
				else
					Pop(e);
			}
			else match = false;
		}
		i++;
	}
	if (!StackEmpty())
		match = false;
	return match;
}