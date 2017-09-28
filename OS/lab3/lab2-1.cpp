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
			cout << "NOoooooooOooOo!!!..." << endl;
			break;
		default:
			cout << "I'm your father!!!" << endl;
			break;
	}
	
	return 0;
}
