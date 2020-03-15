#pragma once
extern const int MaxSize;

template<class ElemType>
struct TupNode
{
	int r;			//行号
	int c;			//列号
	ElemType d;		//元素值
};

template<class ElemType>
struct TSMatrix
{
	int rows;
	int cols;
	TupNode<ElemType> data[MaxSize];
};

template<class ElemType>
void CreateMat(TSMatrix<ElemType>& t, ElemType** A, int M, int N)
{
	int i, j;
	t.rows = M;
	t.cols = N;
	t.nums = 0;
	//按先行后列的方式扫描所有元素
	for (i = 0; i < M; i++)
	{
		for(j=0;j<N;j++)
			if (A[i][j] != 0)
			{
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j];
				t.nums++;
			}
	}
}

template<class ElemType>
bool Value(TSMatrix<ElemType>& t, ElemType x, int i, int j)
{
	int k = 0, k1;
	if (i >= t.rows || j > t.cols)
		return false;

	while (k<t.nums && i>t.data[k].r) k++;							//查找行
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c) k++;		//查找列

	//如果存在，修改
	if (t.data[k].r == i && t.data[k].c == j)
		t.data[k].d = x;

	//不存在则插入
	else
	{
		for (k1 = t.nums - 1; k1 >= k; k1--)
		{
			//后移一位
			t.data[k1 + 1].r = t.data[k1].r;
			t.data[k1 + 1].c = t.data[k1].c;
			t.data[k1 + 1].d = t.data[k1].d;
		}
		t.data[k].r = i;
		t.data[k].c = j;
		t.data[k].d = x;
		t.nums++;
	}
	return true;
}

// i,j位置的元素赋值给x
template<class ElemType>
bool Assign(TSMatrix<ElemType> t, ElemType& x, int i, int j)
{
	int k = 0;
	if (i >= t.rows || j >= t.cols)
		return false;

	while (k<t.nums && i>t.data[k].r) k++;							//查找行
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c) k++;		//查找列

	if (t.data[k].r == i && t.data[k].c == j)
		x = t.data[k].d;
	else
		x = 0;
	return true;
}

template<class ElemType>
void DispMat(TSMatrix<ElemType> t)
{
	int i;
	if (t.nums < 0)
		return;
	std::cout << t.rows << "   " << t.cols << "   " << t.nums << std::endl;
	std::cout << "--------------" << std::endl;
	for (i = 0; i < t.nums; i++)
		std::cout << t.rows << "   " << t.data[i].r << "   " << t.data[i].c << "   " << t.data[i].d << std::endl;
}

template<class ElemType>
void TranTat(TSMatrix<ElemType> t, TSMatrix<ElemType>& tb)
{
	int p, q = 0, v;
	tb.rows = t.cols;
	tb.cols = t.rows;
	tb.nums = t.nums;
	if (t.nums != 0)
	{
		for(v=0;v<t.cols;v++)
			for(p=0;p<t.nums;p++)
				if (t.data[p].c == v)
				{
					tb.data[q].r = t.data[p].c;
					tb.data[q].c = t.data[p].r;
					tb.data[q].d = t.data[p].d;
					q++;
				}
	}
}