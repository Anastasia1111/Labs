#include "ok.h"
template<typename T>
Queue<T>::Queue():head(0),tail(0){}
template<typename T>
bool Queue<T>::empty(){return !head;}
template<typename T>
void Queue<T>::push(T data){
	el * temp = new el;
	temp->data=data;
	temp->next=0;
	if(empty()){
		head=tail=temp;
	}
	else{
		tail->next=temp;
		tail=temp;
	}
}
template<typename T>
void Queue<T>::pop(){
	if(!empty()){
		el * temp=head;
		head=head->next;
		delete temp;
	}
}		
template<typename T>
T Queue<T>::front(){
		return head->data;
}
