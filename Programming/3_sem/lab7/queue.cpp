#include "queue.h"

int Queue::count = 0;

Queue::~Queue()
{
	count--;
}

Queue *Queue::add(int value)
{
	/*Queue *last = this;
	while (last->next){
		last = (Queue*)last->next;
	}
	last->next = new Queue(value);
	tail = last;*/
	tail->next = new Queue(value);
	try
	{
		if(!(tail->next))
		{
			throw "New element was not created";
		}
		tail = (Queue *)tail->next;
		return this;
	}
	catch(char *str)
	{
		cout << str << endl;
	}
}

Queue *Queue::pop()
{
	int x = data;
	cout << "First queue data: " << x << " -> deleted." << endl;
	Queue *n = (Queue *)next;
	
	try
	{
		if (count)
		{
			throw 1;
		}
		delete this;
	}
	catch(...)
	{
		cout << "Queue contain one element. Delete it in main, pleeeeeeeeeease!" << endl;
	}
	
	return n;
}
