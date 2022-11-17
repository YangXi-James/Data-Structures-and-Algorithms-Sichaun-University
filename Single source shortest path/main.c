#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#define MAX 9999999
typedef struct    
{       char *vexs[20]; //顶点向量       
       int edges[10][10];     //邻接矩阵    
	   int path[10][10];     //路径矩阵
}MGraph,* pMGraph;  

void initialize(pMGraph city)//初始化矩阵
{
	int i,j;
	
	city->vexs[0] = "Chengdu" ;
	city->vexs[1] = "Beijing";
	city->vexs[2] = "Shanghai";
	city->vexs[3] = "Taiwan";
	city->vexs[4] = "Xianggang";
	city->vexs[5] = "Aomen";
	city->vexs[6] = "Shenzhen";
	city->vexs[7] = "Chongqing";
	city->vexs[8] = "Guangzhou";
	city->vexs[9] = "Hangzhou";
	
	int a[10][10] =
	{                   MAX,1874,1976,MAX,MAX,MAX ,2358,302,1503,1921,
						2041,MAX,1318,MAX,4313,MAX,2372,1970,2302,1279,
						2167,1325,MAX,1063,1931,1592,1623,1672,1725,173,
						MAX,MAX,1102,MAX,856,1023,888,MAX,925,MAX,
						MAX,4312,2001,856,MAX,108,52,MAX,141,1772,
						MAX,MAX,85,1560,102,MAX,102,MAX,169,1856,
						2490,2400,1634,888,56,86,MAX,1317,139,1464,
						313,2078,1682,MAX,MAX,MAX,1356,MAX,1201,1614,
						1510,2298,1750,1080,152,158,139,1202,MAX,1613,
						2270,1477,168,MAX,1688,1815,1452,1617,1631,MAX
	};

	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			city->edges[i][j] = a[i][j];//给城市结构体赋值


	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			city->path[i][j] = j;//给经过路径赋初值为上一个节点

}

void findpath(pMGraph G,char city1[20],char city2[20])
{
	int i,j,k,number1,number2,number3,number4;
	char *path1[10];
	for (i = 0; i < 10; i++)
	{
		if (strcmp(city1, G->vexs[i]) == 0)
		{
			number3=number1 = i;//记录城市1下标
			break;
		}
		
	}
	for (i = 0; i < 10; i++)
	{
		if (strcmp(city2, G->vexs[i])== 0)
		{
			number4=number2 = i;//记录城市2下标
			break;
		}
	}

	for (i = 0; i < 10; i++)//利用Floyd算法找到最短路径，并记录其路径。
	{
		for (j = 0; j < 10; j++)
		{
			for (k = 0; k < 10; k++)
				if (G->edges[j][k] > G->edges[j][i] + G->edges[i][k])
				{
					G->edges[j][k] = G->edges[j][i] + G->edges[i][k];
					G->path[j][k] = G->path[j][i];
				}
		}
	}
		
	for (i = 0; i < 10; i++)//将到自己的路径赋值为不可达
		G->edges[i][i] = MAX;

	i = 0;
	while (G->path[number3][number4] != number4)//将路径储存在字符串数组中
	{
		
		number3 = G->path[number3][number4];
		path1[i] = G->vexs[number3];
		i++;
	}

	
	if (G->edges[number1][number2] != MAX)//如果可达则输出路径和距离
	{
		printf("经过路径为%s->", city1);
		for (j = 0; j < i; j++)
		{
			printf("%s->", path1[j]);
		}
		printf("%s\n", city2);
		printf("%s和%s两个城市之间的最短距离为%d。\n", city1, city2, G->edges[number1][number2]);	
	}
	else if (strcmp(city1,city2) == 0)
		printf("%s和%s是同一个城市！\n", city1, city2);
	else 
		printf("%s和%s两个城市之间不可到达！\n", city1, city2);

}

int main()
{
	char city1[1000];
	char city2[1000];
	int i,j,choice,cnt=0;
	char *citys[10] = { "Chengdu" , "Beijing"  , "Shanghai"  , "Taiwan" , "Xianggang"
		,"Aomen"  , "Shenzhen" , "Chongqing" , "Guangzhou", "Hangzhou"};
	pMGraph city = (pMGraph)malloc(sizeof(MGraph));
	printf("                     请在以下10个城市间任意选择两个城市\n");
	printf("Chengdu,Beijing,Shanghai,Taiwan,Xianggang,Aomen,Shenzhen,Chongqing,Guangzhou,Hangzhou\n");
	
	while (true)
	{
		initialize(city);
		printf("请输入出发城市：\n");
		printf(">");
		scanf("%s", city1);
		printf("请输入到达城市：\n");
		printf(">");
		scanf("%s", city2);
		cnt = 0;
		for (i = 0; i < 10; i++)
		{
			if (strcmp(city1, citys[i]) == 0 || strcmp(city2, citys[i]) == 0)//判断输入是否合法
			{
				cnt++;
				if (strcmp(city1, city2) == 0)
					cnt++;
			}
			if (cnt == 2)
			{
				findpath(city, city1, city2);//如果输入正确，寻找最小路径
				break;
			}
		}
			if(cnt!=2)
				printf("输入有误！\n");
				
		     printf("若要继续查找请按1。\n");
			 printf(">");
			 scanf("%d", &choice);
			 if (choice != 1)
				 break;
	}
}