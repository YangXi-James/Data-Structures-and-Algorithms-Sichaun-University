#include<stdio.h>
#include<stdbool.h>
#include"operate.h"
#include"Huffman.h"
int main()
{
	int choice;
	char name[100];
	char name2[100];
	HuffmanTree HT=NULL;
	printf("+---+---------+------+----------+----------+\n");
	printf("|           欢迎使用压缩解压系统！         |\n");
	printf("+---+---------+------+----------+----------+\n");
	printf("|                <1> 压缩                  |\n");
	printf("|                <2> 解压                  |\n");
	printf("|                <3> 退出                  |\n");
	printf("+---+---------+------+----------+----------+\n");
	while (true)
	{
	  printf(">请输入要执行的操作:");
      scanf("%d", &choice);
	  if (choice == 1)//选择1进入压缩
	  {
		  printf(">请输入要压缩的文件名字:\n");
		  scanf("%s", name);
		  printf(">请输入压缩后文件的名字:\n");
		  scanf("%s", name2);
		  compress(name,name2);
	  }
	  else if (choice == 2)//选择2进入解压
	  {
		  printf(">请输入要解压的文件的名字:\n");
		  scanf("%s", name);
		  printf(">请输入解压后文件的名字:\n");
		  scanf("%s", name2);
		  decompree( name,  name2);
		
	  }
	  else//其余退出
		  exit(1);
	}
	

}