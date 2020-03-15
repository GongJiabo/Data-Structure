#include"Sol.h"
#include<iostream>

bool mgpath(int xi, int yi, int xe, int ye, int** mg)
{
	int i, j, k, di, find;
	//定义栈并初始化
	StType st;
	st.top = -1;
	//初始位置入栈
	st.top++;
	st.data[st.top].i = xi;
	st.data[st.top].j = yi;
	st.data[st.top].di = -1;
	mg[xi][yi] = -1;
	//栈不空时循环
	while (st.top > -1)
	{
		i = st.data[st.top].i;
		j = st.data[st.top].j;
		di = st.data[st.top].di;
		//找到出口，输出结果
		if (i == xe && j == ye)
		{
			std::cout << "迷宫路径如下:" << std::endl;
			for (k = 0; k <= st.top; k++)
			{
				std::cout << "(" << st.data[k].i << "," << st.data[k].j << ")";
				if ((k + 1) % 5 == 0)
					std::cout << std::endl;
			}
			std::cout << std::endl;
			return true;
		}
		find = 0;
		while (di < 4 && find == 0)
		{
			di++;
			switch (di)
			{
			case 0:
				i = st.data[st.top].i - 1;
				j = st.data[st.top].j;
				break;
			case 1:
				i = st.data[st.top].i;
				j = st.data[st.top].j + 1;
				break;
			case 2:
				i = st.data[st.top].i + 1;
				j = st.data[st.top].j;
				break;
			case 3:
				i = st.data[st.top].i;
				j = st.data[st.top].j - 1;
				break;
			}
			if (mg[i][j] == 0)
				find = 1;
		}
		if (find == 1)
		{
			st.data[st.top].di = di;
			st.top++;
			st.data[st.top].i = i;
			st.data[st.top].j = j;
			st.data[st.top].di = -1;
			mg[i][j] = -1;
		}
		else
		{
			//退栈
			mg[st.data[st.top].i][st.data[st.top].j] = 0;
			st.top--;
		}
	}
	return false;
}

bool mgpath1(int xi, int yi, int xe, int ye, int** mg)
{
	//搜索路径为:(xi,yi)->(xe,ye)
	int i, j, find = 0, di;
	//定义顺序队
	QuType qu;
	qu.front = qu.rear = -1;
	//(xi,yi)进队
	qu.rear++;
	qu.data[qu.rear].i = xi;
	qu.data[qu.rear].j = yi;
	qu.data[qu.rear].pre = -1;
	//将其赋值为-1，以避免回过来重复搜索
	mg[xi][yi] = -1;
	//队列不空进行循环
	while (qu.front != qu.rear && !find)
	{
		//出队
		qu.front++;
		i = qu.data[qu.front].i;
		j = qu.data[qu.front].j;
		if (i == xe && j == ye)
		{
			find = 1;
			//输出
			//print(qu, qu.front);
			return true;
		}
		for (di = 0; di < 4; di++)
		{
			switch (di)
			{
			case 0:
				i = qu.data[qu.front].i - 1;
				j = qu.data[qu.front].j;
				break;
			case 1:
				i = qu.data[qu.front].i;
				j = qu.data[qu.front].j + 1;
				break;
			case 2:
				i = qu.data[qu.front].i + 1;
				j = qu.data[qu.front].j;
				break;
			case 3:
				i = qu.data[qu.front].i;
				j = qu.data[qu.front].j-1;
				break;
			}
			if (mg[i][j] == 0)
			{
				qu.rear++;
				qu.data[qu.rear].i = i;
				qu.data[qu.rear].j = j;
				qu.data[qu.rear].pre = qu.front;
				mg[i][j] = -1;
			}
		}
	}
	return false;
}

int count_sol = 0;
void mgpath_all(int xi, int yi, int xe, int ye, int** mg, PathType path)
//求解路径为:(xi,yi)->(xe,ye)
{
	int di, k, i, j;
	if (xi == xe && yi == ye)
	{
		path.data[path.length].i = xi;
		path.data[path.length].j = yi;
		path.length++;
		std::cout << "迷宫路径" << count_sol << "如下:" << std::endl;
		for (k = 0; k < path.length; k++)
		{
			std::cout << path.data[k].i << "\t" << path.data[k].j;
			if ((k + 1) % 5 == 0)
				std::cout << std::endl;
		}
	}
	else
	{
		if (mg[xi][yi] == 0)
		{
			di = 0;
			while (di < 4)
			{
				switch (di)
				{
				case 0:
					i = xi - 1;
					j = yi;
					break;
				case 1:
					i = xi;
					j = yi + 1;
					break;
				case 2:
					i = xi + 1;
					j = yi;
				case 3:
					i = xi;
					j = yi - 1;
					break;
				}
				path.data[path.length].i = xi;
				path.data[path.length].j = yi;
				path.length++;
				mg[xi][yi] = -1;
				//
				mgpath_all(i, j, xe, ye, mg, path);
				path.length--;
				mg[xi][yi] = 0;
				di++;
			}
		}
	}
}

void swap(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void perm(int a[], int n, int k)
{
	int i, j;
	if (k == 0)
	{
		for (j = 0; j < n; j++)
			std::cout << "   " << a[j];
		std::cout << std::endl;
	}
	else
	{
		for (i = 0; i <= k; i++)
		{
			swap(a[k], a[i]);
			perm(a, n, k - 1);
			swap(a[k], a[i]);
		}
	}
}