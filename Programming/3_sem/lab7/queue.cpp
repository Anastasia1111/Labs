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
	Queue *last = new Queue(value, this, this->tail);
	return last;
}

Queue *Queue::pop()
{
	int x = tail->data;
	cout << "Первое значение в очереди: " << x << " -> удалено." << endl;
	Queue *last = this;
	try
	{
		if (tail == this)
		{
			throw "Список состоит из одного элемента, удалите его в main, пожалуйста";
		}
		delete tail;
	}
	catch(char *str)
	{
		cout << str << endl;
	}
	while (last->next){
		last = (Queue *)last->next;
	}
	tail = last;
	
	return this;
}
