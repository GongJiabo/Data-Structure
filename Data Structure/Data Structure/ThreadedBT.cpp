#include"ThreadedBT.h"


void Thread(TBTNode*& p)
{
	if (p != nullptr)
	{
		Thread(p->lchild);				//左子树线索化
		if (p->lchild == nullptr)		//前驱线索化
		{
			p->lchild = pre;			//建立当前节点的前驱线索
			p->ltag = 1;
		}
		else
			p->ltag = 0;
		if (pre->rchild == nullptr)			//后继线索化
		{
			pre->rchild = p;				//建立前驱节点的后继线索
			pre->rtag = 1;
		}
		else pre->rtag = 0;
		pre = p;
		Thread(p->rchild);
	}
}

TBTNode* CreateThread(TBTNode* b)
{
	//创建根节点
	TBTNode* root;
	root = new TBTNode;
	root->ltag = 0;
	root->rtag = 1;
	root->rchild = b;
	if (b == nullptr)
		root->lchild = b;
	else
	{
		root->lchild = b;
		pre = root;
		Thread(b);
		pre->rchild = root;
		pre->rtag = 1;
		root->rchild = pre;
	}
	return root;
}

void ThInOrder(TBTNode* tb)
{
	TBTNode* p = tb->lchild;
	while(p != tb)
	{
		while (p->ltag == 0)
			p = p->lchild;
		std::cout << p->data << "   ";
		//如果是线索就一直访问
		while (p->rtag == 1 && p->rchild != tb)
		{
			p = p->rchild;
			std::cout << p->data << "   ";
		}
		p = p->rchild;
	}
}