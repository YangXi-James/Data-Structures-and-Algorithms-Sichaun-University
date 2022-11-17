#include<stdio.h>
#include"stack.h"
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include"numberstack.h"
#include<math.h>
struct compare
{
	char sign;
	int  number;
};
struct compare mysign[6] = { {'(',999} ,{')',-1} ,{'*',5},{'/',5},{'+',1},{'-',1} };//���岻ͬ�������Ȩֵ

 int getstackvalue(pstack change)//���ڷ���ջ���������Ȩֵ
{
	 int z,value=-9999;
	 for (z = 0; z < 6; z++)
	 {
		 if (getval(change) == mysign[z].sign)
		 {
			 value = mysign[z].number;
		 }
	 }
	 return value;
}

 int serch_sign(char input)//���ڵõ���ǰ�����Ƿ����������������򷵻ش������Ȩֵ
 {
	 int i;
	 for (i = 0; i < 6; i++)
	 {
		 if (input == mysign[i].sign)
			 return i;
	 }
	 return -1;
 }

 void check(char input[100])//���ڼ������Ĵ���
 {
	 int i, number = 0, key0 = 0, key = 0,key1=0, key2 = 0, key3 = 0, key4 = 0,key5=0;
	 pstack checkit = (pstack)malloc(sizeof(stack));
	 for (i = 0; input[i] != '\0'; i++)
	 {
		 if ( (input[i] < '0'  || input[i] > '9') && input[i] != '.' && input[i] != '#'  &&  serch_sign(input[i]) == -1 && key==0)//�ж��Ƿ�����Ƿ��ַ�
		 {
			 printf("���벻�Ϸ���\n");
			 number = 1;
			 key = 1;
		 }

		 if (input[i] == '.' && key0==0)//������ַ�Ϊ��.�����Ҹ����δ��ִ�й�

		 {
			 if (input[i - 1]<'0' || input[i - 1]>'9')
			 {
				 printf("С����ǰ�����֣�\n");
				 number = 1;
				 key0 = 1;
			 }
		 }

		 if (serch_sign(input[i]) != -1)//����������
		 {
			 if (input[i - 1] == '.'&& key1==0)//����������֮ǰ�ǡ�.��
			 {
				 printf("С����������֣�\n");
				 number = 1;
				 key1 = 1;
			 }
			 if (input[i - 1] == '#' && key2==0  )//����������֮ǰ�ǡ�#��
			 {
				 printf("���Ų��Ϸ���\n");
				 number = 1;
				 key2 = 1;
			 }
			 if (input[i-1] !=')' && input[i] !='(' &&(i==0 || serch_sign(input[i-1]) != -1) && key3==0)//�����������������Ҳ�������
			 {
				 printf("�����ʹ�ò��Ϸ���\n");
				 number = 1;
				 key3 = 1;
			 }
			 if (input[i] == '(')//����������ţ���ջ
			 {
				 push(checkit, input[i]);
			 }
			 if (input[i] == ')')
			 {
				 if (empty(checkit)==true || pop(checkit) != '(' && key4==0)//���ջ��û��ƥ��������ţ���δ��ִ�й�
				 {
					 printf("ǰ���Ų�ƥ�䣡\n");
					 number = 1;
					 key4 = 1;
				 }
			 }
		 }
	 }
	 if (empty(checkit) == false && key5==0)//���ջ�л��С�(��
	 {
		 printf("�����Ų�ƥ�䣡\n");
		 key5 = 1;
		 number = 1;
	 }
	 if (number == 1)//������������һ����ִ�У�����������˳�����
	 {
		 getchar();
		 getchar();
		 exit(0);
	 }
 }

 void caculatenumber(numberpstack caculate, char output)//����ջ���������ֽ��е�ǰ������ļ��㣬������������ջ
 {

	 float number1, number2, number;
	
		 number2 = popnumber(caculate);
		 number1 = popnumber(caculate);
		 if (output == '+')
			 number = number1 + number2;
		 else if (output == '-')
			 number = number1 - number2;
		 else if (output == '*')
			 number = number1 * number2;
		 else
			 number = number1 / number2;
		 pushnumber(caculate, number);
 }
 void change_to_postnotation_and_caculate(char input[100],pstack change,numberpstack number)
 {

	 int i, j = 0, index = 0, value,flag=0,flag1=0;//index���ڵõ���ǰ�����Ȩֵ��flag���ڼ�¼С�����λ����flag1���ڼ�¼���ź�λ����value���ڵõ�ջ�������Ȩֵ
	 for (i = 0; input[i] != '\0'; i++)
	 {

		  if (  input[i] >='0'  && input[i] <= '9'  ||  input[i]=='.'  || input[i]=='#') //�������ֻ�.��#
		  {
			  printf("%c", input[i]);
			  if (input[i] == '.')//����.
			  {
				  
				  flag = 0;
				  flag++;
				  if (input[i - flag1] == '#')//��֮ǰ��#��
					  flag1++;
			  }

			  if (input[i] == '#')//����#
			  {
				  flag1 = 0;
				  flag1++;
			  }
			  
			  if (input[i - flag] == '.')//�������ǰ��.
				 {
					  double t;
					  t = popnumber(number);
					  if(input[i-flag1] !='#')
					  pushnumber(number, t + ((double)(input[i] - '0') / pow(10, flag)));//���ǰ���޸��ţ���С�����Ĳ��� ��λ�����㲢��ջ
					  else
						  pushnumber(number, t - ((double)(input[i] - '0') / pow(10, flag)));//���ǰ���и��ţ���С�����Ĳ��� ��λ�����㲢��ջ
					  flag++,flag1++;
				  }
			  
						
			  else if (input[i-1]>='0' && input[i-1]<='9' && input[i] !='.' && input[i] !='#')//����Ƕ�λ��
			  {
		         double t;	            	
				 t=popnumber(number);
				 if (input[i - flag1] != '#')
				 pushnumber(number,(double)(t * 10 + input[i] - '0'));//���ǰ���޸��ţ��������������ջ
				 else
				 pushnumber(number, (double)(t * 10 - (input[i] - '0')));//���ǰ���и��ţ����������ȡ������ջ
				 flag1++;
		      }	            
			  else if (input[i] != '.' && input[i] != '#')//�����һ����λ��
			  {
				  if(input[i - flag1] != '#')
				  pushnumber(number, (double)(input[i] - '0'));
				  else
					  pushnumber(number, -(double)(input[i] - '0'));
				  flag1++;
			  }
		  }	    	
		 
		else if (serch_sign(input[i]) != -1)//�ж��Ƿ����������
		{
			  printf(" ");
			 index = serch_sign(input[i]);
			 value = getstackvalue(change);
			 if (input[i] == '(')//����������ţ���ջ
			 {
				 push(change, input[i]);
			 }
			 else if (input[i] == ')')
			 {
				 while (getval(change) != '(' && empty(change) == false)//����������ţ����ջֱ��������
				 {
					 caculatenumber(number,getval(change));
					 printf("%c", pop(change));
					 j++;
				 }
				 if(getval(change)=='(')//�������ų�ջ
					 pop(change);
				 else
					 printf("%c", pop(change));
					 j++;
			 }
			 else if (mysign[index].number > value || getval(change) == '(')
				 push(change, input[i]);//�����ǰ�����Ȩֵ����ջ��Ȩֵ

			 else
			 {
				 while (mysign[index].number <= value && empty(change) == false && getval(change) !='(')//�����ǰ���������ջ�������Ȩֵ�����ջ���������㣬ֱ��С�ڵ���
				 {
					 caculatenumber(number, getval(change));
					 printf("%c", pop(change));
					 j++;
					 value = getstackvalue(change);
				 }
				 push(change, input[i]);
			 }

		}
	 }
	 while (empty(change) == false)//��ջ��Ϊ�գ�����ѭ������
	 {
		 printf("%c", getval(change));
		 caculatenumber(number,pop(change) );
		 j++;
	 }
 }

int main()
{
	pstack change = (pstack)malloc(sizeof(stack));
	numberpstack number = (numberstack *)malloc(sizeof(numberstack));
	init(change);//��ʼ������ջ
	initnumber(number);//��ʼ������ջ
	char input[100];
	while (true)
	{
		scanf("%s", input);
		check(input);//��������Ƿ���ȷ
		change_to_postnotation_and_caculate(input, change, number);//����ת������ģ��
		printf("\n");
		printf("%f\n", popnumber(number));//���ջ��ֵ
	}
	getchar();
	getchar();
}