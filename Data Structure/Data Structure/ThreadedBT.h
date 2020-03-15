#pragma once
#include<iostream>

typedef char ElemType;

struct TBTNode
{
	ElemType data;				//节点数据域
	int ltag, rtag;				//增加的线索标记  ltag==1 -> lchild为左线索
	TBTNode* lchild;			//左孩子或线索指针		
	TBTNode* rchild;			//右孩子或线索指针
};


//建立中序线索二叉树
TBTNode *pre;				//全局变量
//1.对以*p为根节点的二叉树子树的中序线索化
void Thread(TBTNode*& p);
//2.对以二叉链存储的二叉树b进行线索化，并返回线索化后头结点的指针root
TBTNode* CreateThread(TBTNode* b);



//遍历线索二叉树
//中序线索二叉树遍历
void ThInOrder(TBTNode* tb);