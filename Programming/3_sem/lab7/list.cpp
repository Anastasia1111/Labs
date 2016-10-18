#include "list.h"

int List::count = 0;

List::~List(){
	count--;
}

void List::print()
{
	cout << data << endl;
	if(next != NULL){
	}
}

List *List::add(int value)
{
	List *last = new List(value, this);
	return last;
}

void List::show()
{
	cout << data << " ";
	if (next){
		return next->show();
	}
}

void List::search(int key)
{
	if(data == key){
		cout << "element was found!" << endl;
		return;
	} else {
		if(next != NULL){
			return next->search(key);
		}
	}
	return;
}

void List::dellist()
{
	if(next != NULL){
		return next->dellist();
	}
	delete this;
}

