#include<iostream>
#include<cmath>
#include<stack>
#include<vector>
#include<cstdio>
using namespace std;
#define maxSize 100

struct data_fix					//自定义类型以储存运算符或数字
{
	int	id = 0;					//运算符标记为1，数字标记为2
	double num = 0;
	char op = 0;
};


bool cmpPrior(char top1, char cur)		//运算符优先级比较函数
{
	if ((top1 == '+' || top1 == '-') && (cur == '+' || cur == '-'))
		return true;
	if ((top1 == '*' || top1 == '/')&&(cur=='*'||cur=='/'||cur=='+'||cur=='-'))
		return true;
	return false;
}


data_fix* trans(char* exp,data_fix* a)			//将中缀表达式处理变为后缀表达式
{
	double data_num = 0;
	char data_op;
	stack<char>oper;
	int j = 0;
	oper.push('=');


	for (int i = 0; exp[i]!='\0'; i++)
	{ 
		
		if (isdigit(exp[i]))					//包含对小数的处理
		{
			a[j].id = 2;
			while (isdigit(exp[i]))
			{
				a[j].num = a[j].num * 10 + exp[i] - '0';
				i++;
			} 
			if (exp[i] == '.')				
			{
				i++;
				int z = 1;
				while (isdigit(exp[i]))
				{
					a[j].num = a[j].num + (exp[i] - '0') / pow(10, z++);
					i++;
				} 
			}
			i--;
			j++;
		}
		else if (exp[i] == ' ')					//忽略空格
		{
			continue;
		}
		else if (exp[i] == '(')
			oper.push('(');
		else if (exp[i] == ')')
		{
			while (oper.top() != '(')
			{
				a[j].id = 1;
				a[j].op = oper.top();
				oper.pop();
				j++;
			}
			oper.pop();
		}
		else if (cmpPrior(oper.top(), exp[i]))
		{
			while (cmpPrior(oper.top(), exp[i]))
			{
				a[j].id = 1;
				a[j].op = oper.top();
				oper.pop();
				j++;
			}
			oper.push(exp[i]);
		}
		else oper.push(exp[i]);
	}
	while (!oper.empty())
	{
		a[j].id = 1;
		a[j].op = oper.top();
		oper.pop();
		j++;
	}
	return a;
}

double caluate_once(double num1, double num2,char op)		//单次四则运算
{
	double result = 0;
	switch (op)
	{
	case'+':result = num1 + num2; break;
	case'-':result = num1 - num2; break;
	case'*':result = num1 * num2; break;
	case'/': 
	{
		if (num2 == 0)
			cout << "error" << endl;
		else result = num1 / num2;
		break;
	}
	default:break;
	}
	return result;
}
double cacluate(data_fix* postfix_exp)			//对后缀表达式进行求值
{
	double num1 = 0, num2 = 0, result = 0;
	stack <double>num;
	num.push(0);
	for (int i = 0; postfix_exp[i].id != 0; i++)
	{
		if (postfix_exp[i].id == 2)
		{
			num.push(postfix_exp[i].num);
		}
		else if(postfix_exp[i].op!='=')
		{
			num2 = num.top();
			num.pop();
			num1 = num.top();
			num.pop();
			result=caluate_once(num1, num2, postfix_exp[i].op);
			num.push(result);
		}
	}
	return result;
}

int main()
{
	char exp[maxSize] = {'\0'};
	data_fix a[maxSize];
	while (cin >> exp)
	{
		data_fix* m = trans(exp, a);
		cout << "result:"<< cacluate(m) << endl;
		for (int i = 0; a[i].id != 0; i++)			//清空数组
		{
			a[i].id = 0;
			a[i].num = 0;
			a[i].op = 0;
		}
	}
	return 0;
}
