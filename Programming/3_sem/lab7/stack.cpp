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
	cout << "��������� �������� �����: " << data << " -> �������" << endl;
	Stack *n = (Stack *)this->next;
	delete this; // �������������, ����.
	return n;
}
