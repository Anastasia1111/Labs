#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <iostream>

#include "list.h"

class Stack : public List
{
	public:
		
		static int count;
		
		Stack(): List()
		{count++;
		};
		
		Stack(int _data): List(_data)
		{count++;
		};
		
		~Stack();
		
		Stack *add(int value);
		
		Stack *pop();
		
	protected:
			
		Stack(int _data, Stack *_next): List(_data, _next)
		{
			count++;
		};
};

#endif
