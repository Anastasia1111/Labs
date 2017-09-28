#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	
	switch(fork())
	{
		case -1:
			cout << "Error." << endl;
			break;
		case 0:
			execl("/bin/ls", "ls", "-l", NULL);
			break;
		default:
			wait();
			break;
	}
	
	return 0;
}

