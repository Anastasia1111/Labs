#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <iostream>

#include "list.h"

template <typename type>
class Stack : public List <type>
{
	public:
		
		Stack<type>(): List<type>(){};
		
		Stack<type>(type _data): List<type>(_data){};
		
		~Stack<type>(){};
		
		Stack<type>* add(type value)
		{
			Stack *input = NULL;
			input = new Stack(value,this);
			try
			{
				if(!(input))
				{
					throw 1;
				}
				return input;
			}
			catch(...)
			{
				cout << "New element was not created" << endl;
			}
		};
		
		Stack<type>* pop()
		{
			Stack *n;
			type x = this->data;
			cout << "Last stack data: " << x << " -> deleted" << endl;
			n = (Stack *)this->next;
			
			return n;
		};
		
	protected:
			
		Stack<type>(type _data, Stack *_next): List<type>(_data, _next){};
};

#endif
