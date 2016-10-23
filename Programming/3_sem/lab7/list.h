#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

class List {
	public:
		int data;

		static int count;
		
		List() : data(0), next(NULL)
		{
			count++;
		};
		
		List(int _data): data(_data), next(NULL)
		{
			count++;
		};
		
		virtual ~List();
		
		void show();
		
		virtual List *add(int value);
		
		void search(int key);
			
	protected:
		List *next;
		
		void dellist();
		
		List(int _data, List *_next): data(_data), next(_next)
		{
			count++;
		};
};

#endif
