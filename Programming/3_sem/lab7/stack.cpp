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
	cout << "Последнее значение стэка: " << data << " -> удалено" << endl;
	n = (Stack *)this->next;
	try
	{
		if(!(this->next)){
			throw "Список состоит из одного элемента, удалите его в main, пожалуйста";
		}
		delete this; // отвратительно, знаю.
		
	}
	catch(char *str)
	{
		cout << str << endl;
		return this;
	}

	return n;
}
