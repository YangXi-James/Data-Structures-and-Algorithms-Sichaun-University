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
	printf("|           ��ӭʹ��ѹ����ѹϵͳ��         |\n");
	printf("+---+---------+------+----------+----------+\n");
	printf("|                <1> ѹ��                  |\n");
	printf("|                <2> ��ѹ                  |\n");
	printf("|                <3> �˳�                  |\n");
	printf("+---+---------+------+----------+----------+\n");
	while (true)
	{
	  printf(">������Ҫִ�еĲ���:");
      scanf("%d", &choice);
	  if (choice == 1)//ѡ��1����ѹ��
	  {
		  printf(">������Ҫѹ�����ļ�����:\n");
		  scanf("%s", name);
		  printf(">������ѹ�����ļ�������:\n");
		  scanf("%s", name2);
		  compress(name,name2);
	  }
	  else if (choice == 2)//ѡ��2�����ѹ
	  {
		  printf(">������Ҫ��ѹ���ļ�������:\n");
		  scanf("%s", name);
		  printf(">�������ѹ���ļ�������:\n");
		  scanf("%s", name2);
		  decompree( name,  name2);
		
	  }
	  else//�����˳�
		  exit(1);
	}
	

}