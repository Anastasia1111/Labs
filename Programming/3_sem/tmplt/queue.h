#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <iostream>

#include "list.h"

template <typename type>
class Queue : public List <type>
{
	public:
		
		Queue<type> *tail;
		
		Queue<type>(): List<type>(), tail(this){};
		
		Queue<type>(type _data): List<type>(_data), tail(this){};
		
		~Queue<type>(){};
		
		Queue<type> *add(type value)
		{
			tail->next = new Queue(value);
			try
			{
				if(!(tail->next))
				{
					throw 1;
				}
				tail = (Queue *)tail->next;
				return this;
			}
			catch(...)
			{
				cout << "New element was not created" << endl;
			}
		};
		
		Queue<type> *pop()
		{
			type x = this->data;
			cout << "First queue data: " << x << " -> deleted." << endl;
			Queue *n = (Queue *)this->next;
			
			return n;
		}; 
		
	protected:
		
		Queue<type>(type _data, Queue *_next, Queue *_tail): List<type>(_data, _next), tail(_tail){};
};

#endif
