#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char inp[18] = "Enter your name:\n";
	write(1, inp, 17);
	char output[1024];
	read(0, output, 1024);
	char ans[8] = "Hello, ";
	write(1, ans, 7);
	write(1, output, strlen(output) - 1);
	write(1,"!!!", 3);
	return 0;
}