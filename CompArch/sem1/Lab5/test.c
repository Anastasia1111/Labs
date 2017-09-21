#include "myReadKey.h"

int main()
{
	enum keys button;
	
	rk_mytermregime(1, 0, 1, 0, 1);
	rk_readkey(&button);
	printf("%d ", button);
	return 0;
}
