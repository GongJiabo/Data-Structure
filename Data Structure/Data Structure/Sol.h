#pragma once

//用栈求解迷宫路径


struct Box
{
	int i;		//行号
	int j;		//列号
	int di;		//方向
};

struct StType
{
	Box data[100];
	int top;
};

bool mgpath(int xi, int yi, int xe, int ye, int** mg);


//用队列求解迷宫问题
struct QBox
{
	int i, j;
	int pre;		//本路径中上一个方块在队列中的下标
};

struct QuType
{
	QBox data[100];
	int front;
	int rear;
};

bool mgpath1(int xi, int yi, int xe, int ye, int** mg);


//递归求解所有迷宫问题的解
struct DBox
{
	int i;
	int j;
};

struct PathType
{
	DBox data[100];
	int length;
};


void mgpath_all(int xi, int yi, int xe, int ye, int** mg, PathType path);


//输出数组元素的全排列
void swap(int& a, int& b);
void perm(int a[], int n, int k);