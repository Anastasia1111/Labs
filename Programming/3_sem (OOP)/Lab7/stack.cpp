#include "stack.h"

int Stack::count = 0;

Stack::~Stack()
{
	count--;
}

Stack *Stack::add(int value)
{
	Stack *input = NULL;
	input = new Stack(value,this);
	try
	{
		if(!(input))
		{
			throw "New element was not created";
		}
		return input;
	}
	catch(char *str)
	{
		cout << str << endl;
	}
	
}

Stack *Stack::pop()
{
	Stack *n;
	cout << "Last stack data: " << data << " -> deleted" << endl;
	n = (Stack *)this->next;
	try
	{
		if(count){
			throw 1;
		}
		delete this; // отвратительно, знаю.
		
	}
	catch(...)
	{
		cout << "Stack contain one element. Delete it in main, pleeeeeeeeeease!" << endl;
		return this;
	}

	return n;
}
