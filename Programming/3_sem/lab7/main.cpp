#include <cstdlib>
#include <iostream>
#include "queue.h"
#include "stack.h"

using namespace std;

int main(int argc, char *argv[])
{
	Queue * qhead= new Queue(rand()%50);
	Stack * shead= new Stack(rand()%50);
	int i = 0;
	
	for(i = 0; i < 10; i++){
		qhead = qhead->add(rand()%50);
		shead = shead->add(rand()%50);
	}
	
	qhead->show();
	cout << endl;
	shead->show();
	cout << endl;
	
	
	
    system("PAUSE");
    return EXIT_SUCCESS;
}
