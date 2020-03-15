#pragma once
extern const int MaxSize;

//顺序链表
template <class ElemType>
class SeqList
{
public:
    SeqList();                              //无参数构造方法
    SeqList(ElemType a[], int n);           //有参数构造方法
    ~SeqList();                             //析构函数

    int ListLength();                     //线性表长度
    bool ListEmpty();                     //判断链表是否为空
    ElemType GetElem(int i);              //按位查找
    int LocateElem(ElemType e);           //按值查找
    void ListInsert(int i, ElemType e);   //插入
    ElemType ListDelete(int i);           //删除
    void PrintList();                     //遍历

    //删除所有值为e的元素，空姐复杂度O(1)，时间复杂度O(n)
    void DelNode1(ElemType e);
    void DelNode2(ElemType e);
private:
    ElemType data[MaxSize];
    int length;
};

//单链表
template <class ElemType>
struct Node
{
    ElemType data;
    Node* next;
};

template <class ElemType>
class SLinkList
{
private:
    Node<ElemType>* head;

public:
    SLinkList();
    SLinkList(ElemType a[], int n);
    ~SLinkList();

    void CreateListF(ElemType a[], int n);          //从数组创建单链表-头插法
    void CreateListR(ElemType a[], int n);          //从数组创建单链表-尾插法

    bool ListEmpty();                               //判断链表是否为空
    int ListLength();                               //获得链表长度
    void PrintList();                               //遍历
    bool GetElem(int i, ElemType& e);               //获取序号为i的元素
    int LocateElem(ElemType e);                     //查找元素
    bool ListInsert(int i, ElemType e);             //在位置i插入元素
    bool ListDelete(int i, ElemType& e);            //删除位置i的元素，并通过参数e返回

    void DeleteMaxNode();                           //删除值最大的元素
    void Sort();                                    //使元素递增排序   
    void Reverse();                                 //元素倒置

    //L:a1,b1,a2,b2,...,an,bn
    //L1:a1,a2,a3....,an
    //L2:bn,bn-1,bn-2,....,b1
    void Split(SLinkList<ElemType>& L1, SLinkList<ElemType>& L2);           
};

//双向链表
template <class ElemType>
struct DNode
{
    ElemType data;
    DNode* prior;
    DNode* next;
};

template <class ElemType>
class DLinkList
{
private:
    DNode<ElemType>* head;
    
public:
    DLinkList();
    ~DLinkList();

    void CreatListF(ElemType a[], int n);
    void CreateListR(ElemType a[], int n);

    bool ListInsert(int i, ElemType e);
    bool ListDelete(int i, ElemType& e);
    void Reverse();
};

//顺序表实现
#pragma once
#include"LinearList.h"
#include <iostream>

template <class ElemType>
SeqList<ElemType>::SeqList()
{
    length = 0;
    for (int i = 0; i < MaxSize; i++)
        data[i] = 0;
}

template <class ElemType>
SeqList<ElemType>::SeqList(ElemType a[], int n)
{
    if (n > MaxSize)
        throw "数组长度超过顺序表最大长度";
    for (int i = 0; i < n; i++) {
        data[i] = a[i];
    }
    length = n;
}

template <class ElemType>
SeqList<ElemType>::~SeqList()
{
}

template <class ElemType>
int SeqList<ElemType>::ListLength()
{
    return length;
}

template <class ElemType>
bool SeqList<ElemType>::ListEmpty()
{
    return(length == 0);
}


template <class ElemType>
ElemType SeqList<ElemType>::GetElem(int i)
{
    if (i<0 || i>length)
        throw "查找位置非法";
    return data[i - 1];
}

template <class ElemType>
int SeqList<ElemType>::LocateElem(ElemType x)
{
    for (int i = 0; i < length; i++) {
        if (x == data[i])
            return i + 1;
    }
    return -1;
}

template <class ElemType>
void SeqList<ElemType>::ListInsert(int i, ElemType e)
{
    if (length >= MaxSize)
        throw "上溢异常";
    if (i<1 || i>length + 1)
        throw "位置异常";
    i = i - 1;
    for (int j = length; j >= i; j--)
    {
        data[j] = data[j - 1];
    }
    data[i] = e;
    length++;
}

template <class ElemType>
ElemType SeqList<ElemType>::ListDelete(int i)
{
    if (0 == length)
        throw "下溢异常";
    if (i<1 || i>length)
        throw "位置异常";
    ElemType x = data[i - 1];
    for (int j = i; j < length; j++) {
        data[j - 1] = data[j];
    }
    data[length - 1] = 0;
    length--;
    return x;

}


template <class ElemType>
void SeqList<ElemType>::PrintList()
{
    std::cout << "按序号依次遍历线性表中的各个元素" << std::endl;
    for (int i = 0; i < length; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

template <class ElemType>
void SeqList<ElemType>::DelNode1(ElemType e)
{
    int k = 0, i;
    for (i = 0; i < length; i++)
    {
        if (data[i] == !e)
        {
            data[k] = data[i];
            k++;
        }
    }
    length = k;
}

template <class ElemType>
void SeqList<ElemType>::DelNode2(ElemType e)
{
    int k = 0, i;
    while (i < length)
    {
        if (data[i] == e)
            k++;
        else
            data[i - k] = data[i];
        i++;
    }
    length = length - k;
}

//单链表实现
template <class ElemType>
SLinkList<ElemType>::SLinkList()
{
    head = new Node<ElemType>;
    head->next = nullptr;
}

template <class ElemType>
SLinkList<ElemType>::SLinkList(ElemType a[],int n)
{
    head = new Node<ElemType>;
    head->next = nullptr;
    //
    Node<ElemType>* r = new Node<ElemType>;
    r = head;
    for (int i = 0; i < n; i++)
    {
        Node<ElemType>* s = new Node<ElemType>;
        s->data = a[i];
        r->next = s;
        r=s;
    }
    r->next = nullptr;
}

template <class ElemType>
SLinkList<ElemType>::~SLinkList()
{
    //头结点也销毁
    Node<ElemType>* pre = head;
    Node<ElemType>* p = head->next;
    while (p != nullptr)
    {
        delete(pre);
        pre = p;
        p = pre->next;
    }

}

template <class ElemType>
void SLinkList<ElemType>::CreateListF(ElemType a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Node<ElemType>* s = new Node<ElemType>;
        s->data = a[i];
        s->next = head->next;
        head->next = s;
    }
}

template <class ElemType>
void SLinkList<ElemType>::CreateListR(ElemType a[], int n)
{
    Node<ElemType>* r = new Node<ElemType>;
    r = head;
    for (int i = 0; i < n; i++)
    {
        Node<ElemType>* s = new Node<ElemType>;
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = nullptr;
}

template <class ElemType>
bool SLinkList<ElemType>::ListEmpty()
{
    return(head->next == nullptr);
}

template <class ElemType>
int SLinkList<ElemType>::ListLength()
{
    int n = 0;
    Node<ElemType>* p = head;
    while (p->next != nullptr)
    {
        p = p->next;
        n++;
    }
    return n;
}

template <class ElemType>
void SLinkList<ElemType>::PrintList()
{
    Node<ElemType>* p = head;
    while (p->next)
    {
        p = p->next;
        std::cout << p->data << std::endl;
        
    }
}

template <class ElemType>
bool SLinkList<ElemType>::GetElem(int i, ElemType& e)
{
    int j = 0;
    Node<ElemType>* p = head;
    while (j < i && p!= nullptr)
    {
        j++;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    else
    {
        e = p->data;
        return true;
    }
}

template <class ElemType>
int SLinkList<ElemType>::LocateElem(ElemType e)
{
    int i = 1;
    Node<ElemType>* p = head->next;
    while (p != nullptr && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p == nullptr)
        return 0;
    else
        return i;
}

template <class ElemType>
bool SLinkList<ElemType>::ListInsert(int i, ElemType e)
{
    int j = 0;
    Node<ElemType>* p = head;
    while (j < i - 1 && p != nullptr)
    {
        j++;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    else
    {
        Node<ElemType>* ins = new Node<ElemType>;
        ins->data = e;
        ins->next = p->next;
        p->next = ins;
        return true;
    }
}

template <class ElemType>
bool SLinkList<ElemType>::ListDelete(int i, ElemType& e)
{
    int j = 0;
    Node<ElemType>* p=head;
    while (j < i - 1 && p != nullptr)
    {
        j++;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    else
    {
        Node<ElemType>* del = new Node<ElemType>;
        del = p->next;
        if (del == nullptr)
            return false;
        e = del->data;
        p->next = del->next;
        delete(del);
        return true;
    }
}

template <class ElemType>
void SLinkList<ElemType>::DeleteMaxNode()
{
    Node<ElemType>* p = head->next;
    Node<ElemType>* pre = head;
    Node<ElemType>* maxp = p;
    Node<ElemType>* maxpre = pre;

    while (p != nullptr)
    {
        if (maxp->data < p->data)
        {
            maxp = p;
            maxpre = pre;
        }
        pre = p;
        p = p->next;
    }
    maxpre->next = maxp->next;
    delete(maxp);
}

template <class ElemType>
void SLinkList<ElemType>::Sort()
{
    Node<ElemType>* p, * pre, * q;
    //从第二个元素拆分，开始插入排序
    p = head->next->next;
    head->next->next = nullptr;
    while (p != nullptr)
    {
        q = p->next;
        pre = head;
        while (pre->next != nullptr && pre->next->data < p->data)
            pre = pre->next;
        //查找到pre的元素data值大于p元素的位置进行插入
        p->next = pre->next;
        pre->next = p;
        p = q;
    }
}

template <class ElemType>
void SLinkList<ElemType>::Reverse()
{
    Node<ElemType>* p = head->next, * q;
    head->next = nullptr;
    while (p != nullptr)
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

template <class ElemType>
void SLinkList<ElemType>::Split(SLinkList<ElemType>& L1, SLinkList<ElemType>& L2)
{
    Node<ElemType>* p = head->next, * q, * r1;      //p指向第一个数据节点
    L1.head = head;                                 //L1利用原来的头节点(尾插法)
    r1 = L1.head;                                   //r1始终指向L1的尾节点
    L2.head->next = nullptr;                        //创建L2的头节点，设置指针域为NULLPTR
    //
    while (p != nullptr)
    {
        r1->next = p;
        r1 = p;

        p = p->next;
        q = p->next;

        p->next = L2.head->next;
        L2.head->next = p;

        p = q;
    }
    r1->next = nullptr;
}

//双向链表实现
template<class ElemType>
DLinkList<ElemType>::DLinkList()
{
    head = new DNode<ElemType>;
    head->next = nullptr;
    head->prior = nullptr;
}

template<class ElemType>
DLinkList<ElemType>::~DLinkList()
{
    //头结点也销毁
    DNode<ElemType>* pre = head;
    DNode<ElemType>* p = head->next;
    while (p != nullptr)
    {
        delete(pre);
        pre = p;
        p = pre->next;
    }
}

template<class ElemType>
void DLinkList<ElemType>::CreatListF(ElemType a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        DNode<ElemType>* s = new DNode<ElemType>;
        s->data = a[i];
        s->next = head->next;
        if (head->next != nullptr)
            head->next->prior = s;
        head->next = s;
        s->prior = head;
    }
}

template<class ElemType>
void DLinkList<ElemType>::CreateListR(ElemType a[], int n)
{
    DNode<ElemType>* s, * r;
    int i;
    r = head;
    for (i = 0; i < n; i++)
    {
        s = new DNode<ElemType>;
        s->data = a[i];
        r->next = s;
        s->prior = r;
        r = s;
    }
    r->next = nullptr;
}

template<class ElemType>
bool DLinkList<ElemType>::ListInsert(int i, ElemType e)
{
    int j = 0;
    DNode<ElemType>* p = head, * s;
    while (j < i - 1 && p != nullptr)
    {
        //查找第i-1个节点
        j++;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    else
    {
        s = new DNode<ElemType>;
        s->data = e;
        s->next = p->next;
        if (p->next != nullptr)
            p->next->prior = s;
        s->prior = p;
        p->next = s;
        return true;
    }
}

template<class ElemType>
bool DLinkList<ElemType>::ListDelete(int i, ElemType& e)
{
    int j = 0;
    DNode<ElemType>* p = head, * q;
    while (j < i - 1 && p != nullptr)
    {
        j++;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    else
    {
        q = p->next;
        if (q == nullptr)
            return false;
        e = q->data;
        p->next = q->next;
        if (p->next != nullptr)
            p->next->prior = p;
        delete q;
        return true;
    }
}

template<class ElemType>
void DLinkList<ElemType>::Reverse()
{
    DNode<ElemType>* p = head->next, * q;
    head->next = nullptr;
    //头插法倒置
    while (p != nullptr)
    {
        q = p->next;
        p->next = head->next;
        if (head->next != nullptr)
            head->next->prior = p;
        head->next = p;
        p->prior = head;
        p = q;
    }
}
