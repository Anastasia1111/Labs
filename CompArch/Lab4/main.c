#include "myBigChars.h"

int main()
{
	bc_box(1,1,9,9);
	int a[2] = _5;
	bc_printbigchar(a, 2, 2, YELLOW, WHITE);
	int value;
	bc_getbigcharpos(a, 0, 4, &value);
	int fd = open("ara.txt", O_WRONLY);
	bc_bigcharwrite(fd, a, 1);
	int count = 0;
	close(fd);
	fd = open("ara.txt", O_RDONLY);
	bc_bigcharread(fd, a, 1, &count);
	bc_printbigchar(a, 12, 22, YELLOW, WHITE);
	close(fd);
	return 0;
}
