#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <iostream>

template<typename T>
class Stack{
	protected:
		struct el{
			T data;
			el * next;
		} * head;
	public:
		Stack():head(0){};
		
		bool empty(){
			return !head;
		};
		
		void push(T data){
			el * temp = new el;
			temp->data = data;
			temp->next = head;
			head = temp;
		};
		
		void pop(){
			if(!empty()){
				el * temp = head;
				head = head->next;
				delete temp;
			}
		};
		
		T front(){
			return head->data;
		};
};
#endif
