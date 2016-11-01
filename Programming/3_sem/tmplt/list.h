#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

template <typename type>
class List {
	public:
		type data;
		
		List<type>() : data(0), next(NULL){};
		
		List<type>(type _data): data(_data), next(NULL){};
		
		~List<type>(){};
		
		void show()
		{
			cout << data << " ";
			if (next){
				return next->show();
			}
		};
		
		List<type>* add(type value)
		{
			List *last = new List(value, this);
			return last;
		};
			
	protected:
		List<type> *next;
		
		void dellist()
		{
			if(next != NULL){
				return next->dellist();
			}
			delete this;
		};
		
		List<type>(type _data, List *_next): data(_data), next(_next){};
};

#endif
