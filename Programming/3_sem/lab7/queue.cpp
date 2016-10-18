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
	cout << "������ �������� � �������: " << x << " -> �������." << endl;
	Queue *last = this;
	while ((last->next) && ((last->next) != tail)){
		last = (Queue *)(last->next);
	}
	try
	{
		if (tail == this)
		{
			throw "������ ������� �� ������ ��������, ������� ��� � main, ����������";
		}
		delete tail;
	}
	catch(char *str)
	{
		cout << str << endl;
	}
	tail = last;
	tail->next = NULL;
	
	return this;
}
