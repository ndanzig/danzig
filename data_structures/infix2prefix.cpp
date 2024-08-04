// 110215_infix2prefix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Node
{
	public:
		double $operand;
		char $operator;
		Node * next;
		Node ()
		{
			$operand = $operator = NULL;
			next= (Node *)NULL;
		}
};

class Stack
{
	public:
		Node * head;
		Stack()
		{
			head = NULL;
		}
		~Stack()
		{
			Node * t;
			while (t=head)
			{
				head=head->next;
				delete t;
			}
			return;
		}
		void push_operand (double data)
		{
			Node * temphead = head;
			head = new Node ();
			head->$operand = data;
			if (temphead)
			{
				head->next = temphead;
			}
			return;
		}
		void push_operator (char data)
		{
			Node * temphead = head;
			head = new Node ();
			head->$operator = data;
			if (temphead)
			{
				head->next = temphead;
			}
			return;
		}
		Node * pop ()
		{
			Node * temphead = head;
			if (!head)
				return (Node *)NULL;
			head = head->next;
			return temphead;
		}
};

Stack * infix2prefix (char * expression);
Stack * parse (char * expression);
short oper_priority (char x);
double evaluate (Stack prefix);

int _tmain(int argc, _TCHAR* argv[])
{
	char in[100];
	gets(in);
	Stack * out;
	out = infix2prefix(in);
	double value = evaluate (* out);
	Node * temp;
	while (out->head)
	{
		temp = out->pop();
		if (temp->$operator)
			cout<<(temp->$operator);
		else
			cout<<(temp->$operand);
	}
	cout<<endl<<value<<endl;
	delete out;
	system("PAUSE");
	return 0;
}


Stack * infix2prefix (char * infix_string)
{
	Stack * infix = (parse (infix_string));
	Stack * prefix = new Stack;
	Stack temp;
	Node * current;
	while (infix->head)
	{
		current = infix->pop();
		if (!(current->$operator))
		{
			prefix->push_operand(current->$operand);
		}
		else
		{
			bool repeat;
			switch (current->$operator)
			{
			case (')'):
				temp.push_operator(')');
				break;
			case ('+'):
			case ('-'):
			case ('*'):
			case ('/'):
				do
				{
					repeat = 0;
					if ((!(temp.head))||
						(((temp.head)->$operator) == ')')||
						(oper_priority (current->$operator)>=(oper_priority ((temp.head)->$operator))))
						temp.push_operator(current->$operator);
					else
					{
						prefix->push_operator((temp.pop())->$operator);
						repeat = 1;
					}
				} while (repeat);
				break;
			case ('('):
				while (temp.head && (((temp.head)->$operator) != ')'))
				{
					prefix->push_operator((temp.pop())->$operator);
				}
				temp.pop();
				break;
			}
		}
	}
	while (temp.head)
		prefix->push_operator((temp.pop())->$operator);
	while (prefix->head)
	{
		if ((prefix->head)->$operator)
			temp.push_operator((prefix->pop())->$operator);
		else
			temp.push_operand((prefix->pop())->$operand);
	}
	while (temp.head)
	{
		if ((temp.head)->$operator)
			prefix->push_operator((temp.pop())->$operator);
		else
			prefix->push_operand((temp.pop())->$operand);
		prefix->push_operator(' ');
	}
	delete infix;
	return prefix;
}

short oper_priority (char x)
{
	if (x=='*'||x=='/')
		return 2;
	else if (x=='+'||x=='-')
		return 1;
	else
		return NULL;
}

Stack * parse (char * expression)
{
	Stack * out_stack = new Stack;
	int i, j;
	double temp;
	int length = strlen(expression);
	for (i=0; i<length; i++)
	{
		if ((expression[i]>='0')&&(expression[i]<='9'))
		{
			temp = (expression[i]-'0');
			j = (i+1);
			int base = 10;
			while ((expression[j]>='0')&&(expression[j]<='9'))
			{
				temp = ((base * temp)+(expression[j]-'0'));
				j++;
				i++;
				base *= 10;
			}
			out_stack->push_operand (temp);
		}
		else 
			out_stack->push_operator (expression[i]);
	}
	return out_stack;
}

double evaluate (Stack prefix)
{
	Stack eval_stack, reverse;
	int i, j;
	double temp, temp1, temp2;
	Node * current;
	while (prefix.head)
	{
		if ((prefix.head)->$operator)
			reverse.push_operator((prefix.pop())->$operator);
		else
			reverse.push_operand((prefix.pop())->$operand);
	}
	while (reverse.head)
	{
		current = reverse.pop();
		if (!(current->$operator))
		{
			eval_stack.push_operand (current->$operand);
		}
		else if ((current->$operator)!=' ')
		{
			temp1 = ((eval_stack.pop())->$operand);
			temp2 = ((eval_stack.pop())->$operand);
			switch (current->$operator) 
			{
			case ('+'):
				temp = temp1 + temp2;
				break;
			case ('-'):
				temp = temp1 - temp2;
				break;
			case ('*'):
				temp = temp1 * temp2;
				break;
			case ('/'):
				temp = temp1 / temp2;
				break;
			}
			eval_stack.push_operand (temp);
		}
	}
	return ((eval_stack.pop())->$operand);
}