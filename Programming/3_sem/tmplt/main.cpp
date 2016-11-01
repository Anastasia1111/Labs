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
	
	Queue<TYPE> * qhead= new Queue<TYPE>;
	Stack<TYPE> * shead= new Stack<TYPE>;
	
	int i = 0;
	for(i = 0; i < 10; i++){
		qhead = qhead->add((TYPE)(rand()%100+100));
		shead = shead->add((TYPE)(rand()%100+100));
	}
	
	qhead->show();
	cout << endl;
	shead->show();
	cout << endl;
	
	qhead = qhead->pop();
	shead = shead->pop();
	
	qhead->show();
	cout << endl;
	shead->show();
	cout << endl;
	
	
    system("PAUSE");
    return EXIT_SUCCESS;
}
