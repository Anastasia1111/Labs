#include <cstdlib>
#include <iostream>
#include <clocale>
#include "queue.h"
#include "stack.h"
#include <ctime>

#define TYPE char

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));
		
	Queue<TYPE> q;
	Stack<TYPE> s;
	
	for(int i=1; i<10; ++i){
		TYPE tmp = rand()%100+100;
		q.push(tmp);
		s.push(tmp);
	}
		
	while(!q.empty()){
		cout<<q.front()<<" ";
		q.pop();
	}
	cout<<endl;
	while(!s.empty()){
		cout<<s.front()<<" ";
		s.pop();
	}
	cout<<endl;
	system("pause");
	return 0;
}
