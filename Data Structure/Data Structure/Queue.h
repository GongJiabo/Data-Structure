#pragma once
extern const int MaxSize;

//顺序队列
template<class ElemType>
class SqQueue
{
private:
	ElemType data[MaxSize];
	int front;
	int rear;
public:
	SqQueue();
	~SqQueue();

	bool QueueEmpty();
	bool enQueue(ElemType e);
	bool deQueue(ElemType& e);

	//环形队列
	//队空:rear=front
	//队满(约定):(rear+1)%MaxSize=front
	//进队:rear=(rear+1)%MaxSize
	//出队:front=(front+1)%MaxSize
	//
	//已知front、rear,求队中元素个数count
	//count=(rear-front+MaxSize)%MaxSize
	//
	//已知front、count,求rear
	//rear=(front+count)%MaxSize
	//
	//已知rear、count,求front
	//front=(rear-count+MaxSize)%MaxSize
};

//链队
template<class ElemType>
struct QNode
{
	ElemType data;
	QNode* next;
};

template<class ElemType>
class LiQueue
{
private:
	QNode<ElemType>* front;
	QNode<ElemType>* rear;
public:
	LiQueue();
	~LiQueue();

	bool QueueEmpty();
	void enQueue(ElemType e);
	void deQueue(ElemType& e);
};

//顺序队列实现
template<class ElemType>
SqQueue<ElemType>::SqQueue()
{
	front = -1;
	rear = -1;
}

template<class ElemType>
SqQueue<ElemType>::~SqQueue()
{

}

template<class ElemType>
bool SqQueue<ElemType>::QueueEmpty()
{
	return(front == rear);
}

template<class ElemType>
bool SqQueue<ElemType>::enQueue(ElemType e)
{
	if (rear = MaxSize - 1)
		return false;
	rear++;
	data[rear] = e;
	return true;
}

template<class ElemType>
bool SqQueue<ElemType>::deQueue(ElemType& e)
{
	//队列为空，下溢
	if (front == rear)
		return false;
	front++;
	e = data[front];
	return true;
}

//链队实现
template<class ElemType>
LiQueue<ElemType>::LiQueue()
{
	front = new QNode<ElemType>;
	rear = new QNode<ElemType>;
	front = nullptr;
	rear = nullptr;
}

template<class ElemType>
LiQueue<ElemType>::~LiQueue()
{
	QNode<ElemType> * p = front, * r;
	if (p != nullptr)
	{
		r = p->next;
		while (r != nullptr)
		{
			delete p;
			p = r;
			r = p->next;
		}
	}
	delete p;
}

template<class ElemType>
bool LiQueue<ElemType>::QueueEmpty()
{
	return(rear == nullptr);
}

template<class ElemType>
void LiQueue<ElemType>::enQueue(ElemType e)
{
	QNode<ElemType>* p = new QNode<ElemType>;
	p->data = e;
	p->next = nullptr;
	//如果链队为空，则新节点即是队首节点又是队尾节点
	if (rear == nullptr)
		front = rear = p;
	else
	{
		rear->next = p;
		rear = p;
	}
}

template<class ElemType>
void LiQueue<ElemType>::deQueue(ElemType& e)
{
	QNode<ElemType>* t;
	if (rear == nullptr) return false;
	t = front;
	//只有一个节点时
	if (front == rear)
		front = rear = nullptr;
	else
		front = front->next;
	e = t->data;
	delete t;
}