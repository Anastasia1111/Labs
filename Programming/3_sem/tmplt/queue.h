#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <iostream>

template<typename T>
class Queue{
	protected:
		struct el{
			T data;
			el * next;
		} * head,* tail;
	public:
		Queue():head(0),tail(0){};
		
		bool empty(){
			return !head;
		};
		
		void push(T data){
			el * temp = new el;
			temp->data = data;
			temp->next = 0;
			if(empty()){
				head = tail=temp;
			}
			else{
				tail->next = temp;
				tail = temp;
			}
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
