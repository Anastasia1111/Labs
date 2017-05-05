#include "SimpleComputer.h"

int main(int argc, char **argv)
{
	struct itimerval nval, oval;
	signal (SIGALRM, IncInstCount);
	signal (SIGUSR1, StopIt);
	nval.it_interval.tv_sec = 1;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;
	int i, j;
	InstCount = 0;
	int value = 0, flag;
	int com, oper;
	char mem[6];
	int n;
	initialize();
	
	//MECHANISM
	int prev = InstCount;
	int prevx, prevy, InstCountx, InstCounty;
	int flagstep = 1;
	int exit = 0;
	
	enum keys button;
	while(!exit)
	{
		print_value(prev);
		mt_gotoXY(5, 70);
		n = sprintf(mem, "%04d", InstCount);
		write(STDOUT_FILENO, mem, n);
		mt_gotoXY(2, 70);
		n = sprintf(mem, "%04X", Accum);
		write(STDOUT_FILENO, mem, n);
		
		big_window();
		print_flag();
		operation();
		rk_mytermregime(1, 0, 1, 0, 1);
		mt_gotoXY(23, 7);
		rk_readkey(&button);
		
		prev = InstCount;
		
		sc_regGet(REG_STEP_IGNORE, &flagstep);
		
		if(!flagstep)
		{
			switch(button)
			{
				case r_key:
					raise(SIGUSR1);
				break;
				case i_key:
					refresh();
				break;
				default:
				break;
			}
			continue;
		}
		
		switch(button)
		{
			case l_key:
				sc_memoryLoad("RAMsave.txt");
				for(i = 0; i < 10; ++i)
					for(j = 0; j < 10; ++j)
						write_ram(i, j);
			break;
			case s_key:
				sc_memorySave("RAMsave.txt");
			break;
			case r_key:
				setitimer(ITIMER_REAL, &nval, &oval);
				sc_regSet(REG_STEP_IGNORE, 0);
			break;
			case t_key:
				InstCount++;
				if(InstCount > 99)
					InstCount--;
			break;
			case i_key:
				refresh();
			break;
			case f5_key:
				set_Accum();
			break;
			case f6_key:
				set_InstCount();
			break;
			case enter_key:
				enter_ram();
			break;
			case up_key:
				if((InstCount - 10) >= 0)
					InstCount -= 10;
			break;
			case down_key:
				if((InstCount + 10) <= 99)
					InstCount += 10;
			break;
			case left_key:
				if((InstCount - 1) >= 0)
					InstCount--;
			break;
			case right_key:
				if((InstCount + 1) <= 99)
					InstCount++;
			break;
			case quit_key:
				exit = 1;
			break;
			default:
			break;
		}
	}
	
	return 0;
}
