#pragma once

#include <iostream>
#define MAX 1000
using namespace std;

//��ջ�ľ�̬ʵ�֣���֧������ʱ����洢�ռ䣬Ĭ�ϴ洢�ռ�Ϊ100

class Stack
{
public:
	int data[MAX];
	~Stack() {}
	Stack() { top = -1; }

	bool push(int value)
	{
		if (top > (MAX - 1))
		{
			cout << "Stack Overflow"<<endl;
			return false;
		}

		data[++top] = value;
		return true;
	}


	int pop()
	{
		if (isEmpty())
		{
			cout << "Stack is empty"<<endl;
			return -1;
		}
		else
		{
			return data[top--];
		}
	}

	bool isEmpty()
	{
		return top < 0;
	}

private:
	int top;
};
