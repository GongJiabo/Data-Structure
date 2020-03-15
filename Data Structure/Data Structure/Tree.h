#pragma once
const int MaxSons = 3;

//双亲存储结构
template<class ElemType>
struct PTree
{
	ElemType data;
	int parent;
};

//孩子链存储结构
template<class ElemType>
struct TSonNode
{
	ElemType data;
	TSonNode* sons[MaxSons];
};

//孩子兄弟链存储结构
template<class ElemType>
struct TSBNode
{
	ElemType data;
	TSBNode* hp;			//指向兄弟
	TSBNode* vp;			//指向孩子节点
	//
	TSBNode()
	{
		data = 0;
		hp = nullptr;
		vp = nullptr;
	}
};


/**************二叉树****************/

//二叉树的顺序存储结构
template<class ElemType>
ElemType SqBTree[100];

//二叉树的链式存储结构
template<class ElemType>
struct BTNode
{
	ElemType data;
	BTNode* lchild, * rchild;
	//
	BTNode()
	{
		data = 0;
		lchild = nullptr;
		rchild = nullptr;
	}
};

//基本操作
//创建二叉树:二叉树括号表示法->二叉树链表存储
//用ch扫描采用括号表示法的字符串
//1. 若ch='('：则将前面刚创建的节点作为双亲节点进栈，并置k=1，表示开始处理左孩子节点
//2. 若ch=')'：表示栈顶节点的左、右孩子节点处理完毕，退栈；
//3. 若ch='，':表示开始处理右孩子节点，置k=2；
//4. 其他情况(节点值)：
//		创建 *p节点作为栈顶节点的左孩子节点
//		当k=1时，将*p节点作为栈顶节点的左孩子节点；
//		当k=2时，将*p节点作为栈顶节点的右孩子节点。
template<class ElemType>
void CreateBTNode(BTNode<ElemType>*& b, char* str)
{
	BTNode<ElemType>* St[100], * p;
	int top = -1, k, j = 0;
	char ch;
	b = nullptr;
	ch = str[j];
	while (ch != '\0')
	{
		switch (ch)
		{
		case '(':
			top++;
			St[top] = p;
			k = 1;
			break;
		case ')':
			top--;
			break;
		case ',':
			k = 2;
			break;
		default:
			p = new BTNode<ElemType>;
			p->data = ch;
			p->lchild = p->rchild = nullptr;
			if (b = nullptr)
				b = p;
			else
			{
				switch (k)
				{
				case 1:
					St[top]->lchild = p;
					break;
				case 2:
					St[top]->rchild = p;
					break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

//销毁二叉树
template<class ElemType>
void Destroy(BTNode<ElemType>*& b)
{
	if (b == nullptr)
		return;
	else
	{
		Destroy(b->lchild);
		Destroy(b->rchild);
		delete b;
	}
}

//查找节点
template<class ElemType>
BTNode<ElemType>* FindNode(BTNode<ElemType>* b, ElemType x)
{
	BTNode<ElemType>* p;
	if (b == nullptr)
		return nullptr;
	else if (b->data == x) return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != nullptr) return p;
		else return FindNode(b->rchild, x);
	}
}

//查找孩子节点
template<class ElemType>
BTNode<ElemType>* LchildNode(BTNode<ElemType>* p)
{
	return p->lchild;
}

template<class ElemType>
BTNode<ElemType>* RchildNode(BTNode<ElemType>* p)
{
	return p->rchild;
}

//求二叉树的高度
template<class ElemType>
int BTNodeDepth(BTNode<ElemType>* b)
{
	int lchilddep = 0, rchilddep = 0;
	if (b == nullptr) return 0;
	else
	{
		lchilddep = BTNodeDepth(b->lchild);
		rchilddep = BTNodeDepth(b->rchild);
		return (lchilddep > rchilddep) ? (lchilddep + 1) : (rchilddep + 1);
	}
}

//输出二叉树
template<class ElemType>
void DispBTNode(BTNode<ElemType>* b)
{
	if (b != nullptr)
	{
		std::cout << b->data;
		if (b->lchild != nullptr || b->rchild != nullptr)
		{
			std::cout << "(";
			DispBTNode(b->lchild);
			if (b->rchild != nullptr)
				std::cout << ",";
			DispBTNode(b->rchild);
			std::cout << ")";
		}
	}
}

//二叉树遍历递归算法
//先序遍历
template<class ElemType>
void PreOrder(BTNode<ElemType>* b)
{
	if (b != nullptr)
	{
		//访问根节点
		std::cout << b->data << "   ";
		//访问左子数
		PreOrder<ElemType>(b->lchild);
		//访问右子树
		PreOrder<ElemType>(b->rchild);
	}
}

//中序遍历
template<class ElemType>
void InOrder(BTNode<ElemType>* b)
{
	if (b != nullptr)

	{	//访问左子数
		InOrder<ElemType>(b->lchild);
		//访问根节点
		std::cout << b->data << "   ";
		//访问右子树
		InOrder<ElemType>(b->rchild);
	}
}

//后序遍历
template<class ElemType>
void PostOrder(BTNode<ElemType>* b)
{
	if (b != nullptr)

	{	//访问左子数
		PostOrder<ElemType>(b->lchild);
		//访问右子树
		PostOrder<ElemType>(b->rchild);
		//访问根节点
		std::cout << b->data << "   ";
	}
}

//层次遍历
template<class ElemType>
void LevelOrder(BTNode<ElemType>* b)
{
	const int MSIZE = 100;
	BTNode<ElemType>* p;
	BTNode<ElemType>* qu[MSIZE];			//定义环形队列，存放节点指针
	int front, rear;						//定义队头和队尾指针
	front = rear = 0;						//置队列为空队列
	rear++;
	qu[rear] = b;
	while (front != rear)					//队列不为空循环
	{
		front = (front + 1) % MSIZE;
		p = qu[front];						//队头出队列
		std::cout << p->data << "   ";		//访问节点
		if (p->lchild != nullptr)
		{
			rear = (rear + 1) % MSIZE;
			qu[rear] = p->lchild;
		}
		if (p->rchild != nullptr)
		{
			rear = (rear + 1) % MSIZE;
			qu[rear] = p->rchild;
		}
	}
}

//层次遍历算法的应用
//假设二叉树采用二叉链存储结构，设计一个算法
//输出从根节点到每个叶子节点的逆路径
template<class ElemType>
void AllPath(BTNode<ElemType>* b)
{
	struct snode
	{
		BTNode<ElemType>* node;				//存放当前节点指针
		int parent;							//存放双亲节点在队列中的位置
	};										//定义非环形队列
	snode qu[100];
	BTNode<ElemType>* q;
	int front, rear, p;
	front = rear = -1;
	//
	rear++;
	qu[rear].node = b;
	qu[rear].parent = -1;
	while (front != rear)
	{
		front++;
		q = qu[front].node;
		if (q->lchild == nullptr && q->rchild == nullptr)
		{
			p = front;
			while (qu[p].parent != -1)
			{
				std::cout << qu[p].node->data << "->";
				p = qu[p].parent;
			}
			std::cout << qu[p].node->data << std::endl;
		}
		if (q->lchild != nullptr)
		{
			rear++;
			qu[rear].node = q->lchild;
			qu[rear].parent = front;
		}
		if (q->rchild != nullptr)
		{
			rear++;
			qu[rear].node = q->rchild;
			qu[rear].parent = front;
		}
	}
};

//计算二叉树中节点的个数
template<class ElemType>
int CountNodes(BTNode<ElemType>* b)
{
	if (b == nullptr)
		return 0;
	else
		return CountNodes(b->lchild) + CountNodes(b->rchild) + 1;
}

//计算二叉树中叶子节点的个数
template<class ElemType>
int LeafNodes(BTNode<ElemType>* b)
{
	int num1, num2;
	if (b == nullptr)
		return 0;
	else if (b->lchild == nullptr && b->rchild == nullptr)
		return 1;
	else
	{
		num1 = LeafNodes(b->lchild);
		num2 = LeafNodes(b->rchild);
		return (num1 + num2);
	}
}

//复制二叉树b->t
template<class ElemType>
void CopyTree(BTNode<ElemType>* b, BTNode<ElemType>* t)
{
	if (b == nullptr)
		t = nullptr;
	else
	{
		//基于先序遍历
		t = new BTNode<ElemType>;
		t->data = b->data;
		CopyTree(b->lchild, t->lchild);
		CopyTree(b->rchild, t->rchild);
	}
}

//交换二叉树的左右子树
//f(b,t)=t=nullptr				   如果b==nullpltr
//f(b,t)=复制节点*b产生*t节点；    其他情况
//f(b->lchild,t->rchild)
//f(b->rchild,t->lchild)
template<class ElemType>
void SwapTree(BTNode<ElemType>* b, BTNode<ElemType>* t)
{
	if (b == nullptr)
		t = nullptr;
	else
	{
		//基于先序遍历
		t = new BTNode<ElemType>;
		t->data = b->data;
		SwapTree(b->lchild, t->rchild);
		SwapTree(b->rchild, t->lchild);
	}
}

//求值为x的节点的层次
template<class ElemType>
int FindLevel(BTNode<ElemType>* b, ElemType x, int h)
{
	int l;
	//空树返回0
	if (b == nullptr)
		return 0;
	else if (b->data == x)
		return h;
	else
	{
		l = FindLevel(b->lchild, x, h + 1);
		if (l == 0)
			return FindLevel(b->rchild, x, h + 1);
		else
			return l;
	}
}

//通过先序遍历和中序遍历的结果构造二叉树
//先序+中序
BTNode<char>* CreateBT1(char* pre, char* in, int n)
{
	BTNode<char>* s;
	char* p;
	int k;
	if (n <= 0)
		return nullptr;
	//创建根节点，为先序遍历中的第一个字符*pre
	s = new BTNode<char>;
	s->data = *pre;
	//在in中寻找*pre的位置k
	for (p = in; p < in + n; p++)
		if (*p == *pre)
			break;
	//长度k
	k = p - in;
	//构造左子树
	s->lchild = CreateBT1(pre + 1, in, k);
	//构造右子树
	s->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1);
	return s;
}

//中序+后序
BTNode<char>* CreateBT2(char* post, char* in, int n)
{
	BTNode<char>* b;
	char r, * p;
	int k;
	if (n <= 0)
		return nullptr;
	//创建根节点，为后序遍历中的最后一个字符*(post+n-1)
	r = *(post + n - 1);
	b = new BTNode<char>;
	b->data = r;
	for (p = in; p < in + n; p++)
		if (*p == r)
			break;
	k = p - in;
	//
	b->lchild = CreateBT2(post, in, k);
	b->rchild = CreateBT2(post + k, p + 1, n - k - 1);
	return b;
}

//将二叉树的顺序存储结构转换成二叉链表存储结构
//USEAGE: trans1(str,0)
BTNode<char>* trans1(char* a, int i)
{
	const int SQMAXSIZE = 100;
	BTNode<char>* b;
	if (i > SQMAXSIZE)
		return nullptr;
	if (a[i] == '#')
		return nullptr;			//当节点不存在时返回空
	b = new BTNode<char>;
	b->data = a[i];
	b->lchild = trans1(a, 2 * i);
	b->rchild = trans1(a, 2 * i + 1);
	return b;
}

//链式存储->顺序存储
template <class ElemType>
BTNode< ElemType>* trans(BTNode<ElemType>* b, ElemType* a, int i)
{
	if (b != nullptr)
	{
		a[i] = b->data;
		trans2(b->lchild, a, 2 * i);
		trans2(b->rchild, a, 2 * i + 1);
	}
}


//求二叉树中度为2的节点个数
template<class ElemType>
int dnodes(BTNode<ElemType>* b)
{
	if (b = nullptr)
		return 0;
	if (b->lchild != nullptr && b->rchild != nullptr)
		return 1 + dnodes(b->lchild) + dnodes(b->rchild);
	else
		return  dnodes(b->lchild) + dnodes(b->rchild);
}

//求二叉树中第k层的节点个数
template<class ElemType>
void knumber(BTNode<ElemType>* b, int h, int k, int& n)
{
	if (b == nullptr)
		return;
	else
	{
		//当前访问的节点在第k层时，n++
		if (h == k)
			n++;
		else if (h < k)
		{
			knumber(b->lchild, h + 1, k, n);
			knumber(b->rchild, h + 1, k, n);
		}

	}
}

//求二叉树b的宽度
//即节点数最多的一层
template<class ElemType>
void levelnumber(BTNode<ElemType>* b, int h, int a[])
{
	if (b == nullptr)
		return;
	else
	{
		a[h]++;
		levelnumber(b->lchild, h + 1, a);
		levelnumber(b->rchild, h + 1, a);
	}
}

template<class ElemType>
int BTWidth1(BTNode<ElemType>* b)
{
	int width = 0, i;
	int a[100];
	for (i = 1; i < 100; i++)
		a[i] = 0;
	levelnumber(b, 1, a);
	i = 1;
	while (a[i] != 0)
	{
		if (a[i] > width)
			width = a[i];
		i++;
	}
	return width;
}

//采用层次遍历求二叉树的宽度
template<class ElemType>
int BTWidth(BTNode<ElemType>* b)
{
	struct
	{
		int lno;					//节点的层次
		BTNode<ElemType>* p;		//节点指针
	}Qu[100];						//定义非环形队列
	int front, rear;
	int lnum, width, i, n;
	front = rear = 0;
	//
	if (b != nullptr)
	{
		rear++;
		Qu[rear].p = b;
		Qu[rear].lno = 1;
		whlie(rear != front)
		{
			front++;
			b = Qu[front].p;			//出队节点p
			lnum = Qu[front].lno;
			if (b->lchild != nullptr)	//有左孩子，将其进队
			{
				rear++;
				Qu[rear].p = b->lchild;
				Qu[rear].lno = lnum + 1;
			}
			if (b->rchild != nullptr)		//有右孩子，将其进队
			{
				rear++;
				Qu[rear].p = b->rchild;
				Qu[rear].lno = lnum + 1;
			}
		}
	}
	//
	width = 0;
	lnum = 1; 
	i = 1;
	while (i <= rear)
	{
		n = 0;
		while (i <= rear && Qu[i].lno == lnum)
		{
			n++;
			i++;
		}
		lnum = Qu[i].lno;
		if (n > width)
			width = n;
	}
	return width;
}