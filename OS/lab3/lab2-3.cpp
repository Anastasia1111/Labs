#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
	cout << getpid() << " (main)" << endl;
	pid_t pid;
	switch(pid = fork())
	{
		case -1:
			cout << "Error." << endl;
			break;
		case 0:
			switch(pid = fork())
			{
				case -1:
					cout << "Error." << endl;
					break;
				case 0:
					break;
				default:
					switch(pid = fork())
					{
						case -1:
							cout << "Error." << endl;
							break;
						default:
							wait(0);
							break;
					}
					break;
			}
			wait(0);
			break;
		default:
			switch(pid = fork())
			{
				case -1:
					cout << "Error." << endl;
					break;
				case 0:
					pid = fork();
					wait(0);
					break;
				default:
					wait(0);
					break;
			}
			wait(0);
			break;
			
	}
	wait(0);
	cout << getpid() << ", child of " << getppid() << endl;
	return 0;
}

