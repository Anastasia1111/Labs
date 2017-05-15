#include "Btranslator.h"

int GoTo(char *param)
{
	while(param[i] == ' ')
		i++;
	while(param[i] != ' ')
	{
		switch(param[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				stringnum *= 10;
				stringnum += (param[i] - '0');
				++i;
			break;
			default:
				error_log(8);
				return -1;
			break;
		}
	}
	
	while(param[i] == ' ')
		i++;
	if(param[i] == 0 || param[i] == '\n')
		return 0;
	else 
	{
		//error_log;
		return -1;
	}
}
