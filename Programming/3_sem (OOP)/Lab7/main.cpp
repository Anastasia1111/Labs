#include <cstdlib>
#include <iostream>
#include <clocale>
#include "queue.h"
#include "stack.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	Queue * qhead= new Queue(rand()%50);
	Stack * shead= new Stack(rand()%50);
	int i = 0;
	
	for(i = 0; i < 1; i++){
		qhead = qhead->add(rand()%50);
		shead = shead->add(rand()%50);
	}
	
	cout << qhead->count << endl;
	cout << shead->count << endl;
	
	qhead->show();
	cout << endl;
	shead->show();
	cout << endl;
	
	qhead = qhead->pop();
	shead = shead->pop();
	
	cout << qhead->count << endl;
	cout << shead->count << endl;
	
	qhead->show();
	cout << endl;
	shead->show();
	cout << endl;
	
	
    system("PAUSE");
    return EXIT_SUCCESS;
}
