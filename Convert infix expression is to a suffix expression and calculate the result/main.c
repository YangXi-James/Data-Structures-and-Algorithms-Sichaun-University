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
struct compare mysign[6] = { {'(',999} ,{')',-1} ,{'*',5},{'/',5},{'+',1},{'-',1} };//定义不同运算符的权值

 int getstackvalue(pstack change)//用于返回栈顶运算符的权值
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

 int serch_sign(char input)//用于得到当前符号是否是运算符，如果是则返回此运算符权值
 {
	 int i;
	 for (i = 0; i < 6; i++)
	 {
		 if (input == mysign[i].sign)
			 return i;
	 }
	 return -1;
 }

 void check(char input[100])//用于检查输入的错误
 {
	 int i, number = 0, key0 = 0, key = 0,key1=0, key2 = 0, key3 = 0, key4 = 0,key5=0;
	 pstack checkit = (pstack)malloc(sizeof(stack));
	 for (i = 0; input[i] != '\0'; i++)
	 {
		 if ( (input[i] < '0'  || input[i] > '9') && input[i] != '.' && input[i] != '#'  &&  serch_sign(input[i]) == -1 && key==0)//判断是否输入非法字符
		 {
			 printf("输入不合法！\n");
			 number = 1;
			 key = 1;
		 }

		 if (input[i] == '.' && key0==0)//如果该字符为“.”，且该语句未被执行过

		 {
			 if (input[i - 1]<'0' || input[i - 1]>'9')
			 {
				 printf("小数点前无数字！\n");
				 number = 1;
				 key0 = 1;
			 }
		 }

		 if (serch_sign(input[i]) != -1)//如果是运算符
		 {
			 if (input[i - 1] == '.'&& key1==0)//如果该运算符之前是“.”
			 {
				 printf("小数点后无数字！\n");
				 number = 1;
				 key1 = 1;
			 }
			 if (input[i - 1] == '#' && key2==0  )//如果该运算符之前是“#”
			 {
				 printf("负号不合法！\n");
				 number = 1;
				 key2 = 1;
			 }
			 if (input[i-1] !=')' && input[i] !='(' &&(i==0 || serch_sign(input[i-1]) != -1) && key3==0)//如果两个运算符连用且不是括号
			 {
				 printf("运算符使用不合法！\n");
				 number = 1;
				 key3 = 1;
			 }
			 if (input[i] == '(')//如果是左括号，入栈
			 {
				 push(checkit, input[i]);
			 }
			 if (input[i] == ')')
			 {
				 if (empty(checkit)==true || pop(checkit) != '(' && key4==0)//如果栈中没有匹配的左括号，且未被执行过
				 {
					 printf("前括号不匹配！\n");
					 number = 1;
					 key4 = 1;
				 }
			 }
		 }
	 }
	 if (empty(checkit) == false && key5==0)//如果栈中还有“(”
	 {
		 printf("后括号不匹配！\n");
		 key5 = 1;
		 number = 1;
	 }
	 if (number == 1)//如果上述语句有一个被执行，则输入出错，退出程序
	 {
		 getchar();
		 getchar();
		 exit(0);
	 }
 }

 void caculatenumber(numberpstack caculate, char output)//用于栈顶两个数字进行当前运算符的计算，并将计算结果入栈
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

	 int i, j = 0, index = 0, value,flag=0,flag1=0;//index用于得到当前运算符权值，flag用于记录小数点后位数，flag1用于记录负号后位数，value用于得到栈顶运算符权值
	 for (i = 0; input[i] != '\0'; i++)
	 {

		  if (  input[i] >='0'  && input[i] <= '9'  ||  input[i]=='.'  || input[i]=='#') //若是数字或.和#
		  {
			  printf("%c", input[i]);
			  if (input[i] == '.')//若是.
			  {
				  
				  flag = 0;
				  flag++;
				  if (input[i - flag1] == '#')//若之前有#号
					  flag1++;
			  }

			  if (input[i] == '#')//若是#
			  {
				  flag1 = 0;
				  flag1++;
			  }
			  
			  if (input[i - flag] == '.')//如果数字前有.
				 {
					  double t;
					  t = popnumber(number);
					  if(input[i-flag1] !='#')
					  pushnumber(number, t + ((double)(input[i] - '0') / pow(10, flag)));//如果前面无负号，对小数点后的部分 按位数运算并入栈
					  else
						  pushnumber(number, t - ((double)(input[i] - '0') / pow(10, flag)));//如果前面有负号，对小数点后的部分 按位数运算并入栈
					  flag++,flag1++;
				  }
			  
						
			  else if (input[i-1]>='0' && input[i-1]<='9' && input[i] !='.' && input[i] !='#')//如果是多位数
			  {
		         double t;	            	
				 t=popnumber(number);
				 if (input[i - flag1] != '#')
				 pushnumber(number,(double)(t * 10 + input[i] - '0'));//如果前面无负号，则算出数字再入栈
				 else
				 pushnumber(number, (double)(t * 10 - (input[i] - '0')));//如果前面有负号，则算出数字取负再入栈
				 flag1++;
		      }	            
			  else if (input[i] != '.' && input[i] != '#')//如果是一个个位数
			  {
				  if(input[i - flag1] != '#')
				  pushnumber(number, (double)(input[i] - '0'));
				  else
					  pushnumber(number, -(double)(input[i] - '0'));
				  flag1++;
			  }
		  }	    	
		 
		else if (serch_sign(input[i]) != -1)//判读是否是运算符号
		{
			  printf(" ");
			 index = serch_sign(input[i]);
			 value = getstackvalue(change);
			 if (input[i] == '(')//如果是左括号，入栈
			 {
				 push(change, input[i]);
			 }
			 else if (input[i] == ')')
			 {
				 while (getval(change) != '(' && empty(change) == false)//如果是右括号，则出栈直到左括号
				 {
					 caculatenumber(number,getval(change));
					 printf("%c", pop(change));
					 j++;
				 }
				 if(getval(change)=='(')//将左括号出栈
					 pop(change);
				 else
					 printf("%c", pop(change));
					 j++;
			 }
			 else if (mysign[index].number > value || getval(change) == '(')
				 push(change, input[i]);//如果当前运算符权值大于栈顶权值

			 else
			 {
				 while (mysign[index].number <= value && empty(change) == false && getval(change) !='(')//如果当前运算符大于栈顶运算符权值，则出栈并进行运算，直到小于等于
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
	 while (empty(change) == false)//若栈不为空，进行循环计算
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
	init(change);//初始化符号栈
	initnumber(number);//初始化数字栈
	char input[100];
	while (true)
	{
		scanf("%s", input);
		check(input);//检查输入是否正确
		change_to_postnotation_and_caculate(input, change, number);//进入转换计算模块
		printf("\n");
		printf("%f\n", popnumber(number));//输出栈顶值
	}
	getchar();
	getchar();
}