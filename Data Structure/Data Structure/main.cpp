#include"LinearList.h"
#include"myString.h"
#include"Queue.h"
#include"Sol.h"
#include"SparseMatrix.h"
#include"Stack.h"
#include"Tree.h"
#include<iostream>

const int MaxSize = 100;

int main() {

    int a[7] = { 1, 2, 3, 4, 5, 6, 7 };
    SeqList<int> list(a, 7);
    list.PrintList();

    list.ListInsert(1, 0);
    list.PrintList();

    int x = list.ListDelete(8);
    std::cout << "删除的元素:" << x << std::endl;
    list.PrintList();

    int p = list.LocateElem(4);
    std::cout << "元素4的位置:" << p << std::endl;


    SLinkList<int> llist;
    llist.CreateListF(a, 7);
    int e=211,ee;
    llist.ListInsert(5, e);
    llist.ListDelete(2, ee);
    llist.PrintList();
    //
    std::cout << "删除最大元素" << std::endl;
    llist.DeleteMaxNode();
    llist.PrintList();

    std::cout << "排序" << std::endl;
    llist.Sort();
    llist.PrintList();

    std::cout << "倒置" << std::endl;
    llist.Reverse();
    llist.PrintList();
    std::cout << std::endl;

   
    BTNode<int>* ta = new BTNode<int>;
    BTNode<int>* tb = new BTNode<int>;
    BTNode<int>* tc = new BTNode<int>;
    BTNode<int>* td = new BTNode<int>;
    BTNode<int>* te = new BTNode<int>;
    ta->data = 1;
    tb->data = 2;
    tc->data = 3;
    td->data = 4;
    te->data = 5;
    ta->lchild = tb;
    ta->rchild = tc;
    tb->lchild = td;
    tb->rchild = te;
    int high = BTNodeDepth<int>(ta);
    PostOrder<int>(ta);
    std::cout<<std::endl;
    LevelOrder<int>(ta);
    std::cout << std::endl;
    AllPath<int>(ta);


   //system("pause");
    return 0;
}
