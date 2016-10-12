#ifndef LIST_H
#define LIST_H

class List {
	public:
		int data;
		static int count;
		
		List() : data(0), count(0), next(NULL) 
		{
		};
		
		List(int _data): data(_data), count(count++) 
		{
		};
		
		~List();
		
		void print();
		
		void search();
		
		void del();
			
	private:
		List *next;
		
}

#endif
