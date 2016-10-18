#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <iostream>

#include "list.h"

class Queue : public List
{
	public:
		
		Queue *tail;
		
		static int count;
		
		Queue(): List(), tail(this)
		{
			count++;
		};
		
		Queue(int _data): List(_data), tail(this)
		{
			count++;
		};
		
		~Queue();
		
		Queue *add(int value);
		
		Queue *pop(); 
		
	protected:
		
		Queue(int _data, Queue *_next, Queue *_tail): List(_data, _next), tail(_tail)
		{
			count++;
		};
};

#endif
