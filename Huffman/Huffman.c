#include<stdio.h>
#include<malloc.h>
#include"Huffman.h"

void Select(HuffmanTree HT, int n, int select[2])
{
	int minum = 0, i;      
	for (i = 1; i <= n; i++)     // 找到第一个最小值    
	{
		if (HT[i].parent == 0)//找还未成为子树的节点
		{
			minum = i;         
			break;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
			if (HT[i].weight < HT[minum].weight)
				minum = i;
	}
	select[0] = minum;

	
	for (i = 1; i <= n; i++)// 找到第二个最小值
	{
		if (HT[i].parent == 0 && i != select[0])
		{
			minum = i;
			break;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != select[0])//找还未成为子树的节点，且与第一个不同
			if (HT[i].weight < HT[minum].weight)
				minum = i;
	}
	select[1] = minum;
}

HuffmanTree * CreatHuff(HuffmanTree HT, int *w, char *a, int n)
{
	int m, select[2], i;
	m = n * 2 - 1;  // 总结点的个数   

	for (i = 1; i <= n; i++) // 叶子结点的初始化 
	{
		HT[i].weight = w[i];
		HT[i].sign = a[i];
		HT[i].parent = 0;
		HT[i].lc = 0;
		HT[i].rc = 0;
	}

	for (i = n + 1; i <= m; i++)   // 非叶子结点的初始化   
	{
		HT[i].weight = 0;
		HT[i].sign = ' ';
		HT[i].parent = 0;
		HT[i].lc = 0;
		HT[i].rc = 0;
	}

	for (i = n + 1; i <= m; i++)     // 选出两个权值最小的树，建哈夫曼树  
	{
		Select(HT, i - 1, select);
		HT[select[0]].parent = i;     
		HT[select[1]].parent = i;
		HT[i].lc = select[0];          
		HT[i].rc = select[1];
		HT[i].weight = HT[select[0]].weight + HT[select[1]].weight;   // 新树的权
		
		
	}   
	return HT;
}