#include "stack.h"

int Stack::count = 0;

Stack::~Stack()
{
	count--;
}

Stack *Stack::add(int value)
{
	Stack *last = new Stack(value,this);
	return last;
}

Stack *Stack::pop()
{
	Stack *n;
	cout << "��������� �������� �����: " << data << " -> �������" << endl;
	n = (Stack *)this->next;
	try
	{
		if(!(this->next)){
			throw "������ ������� �� ������ ��������, ������� ��� � main, ����������";
		}
		delete this; // �������������, ����.
		
	}
	catch(char *str)
	{
		cout << str << endl;
		return this;
	}

	return n;
}
