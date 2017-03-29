#include "myReadKey.h"

int tcgetattr (int fd, struct termios *tsaved);
int tcsetattr (int fd, int actions, const struct termios *tnew);

int rk_readkey (enum keys *key)
{
	struct termios term;
	char buf[8];
	int num_read;
	
	if (tcgetattr(STDIN_FILENO, &term) != 0)
		return -1;
	num_read = read(STDIN_FILENO, buf, 8);
	if (num_read < 0)
		return -1;
	buf[num_read] = 0;
	*key = no_key;
	if (strncmp(buf, "l", 1) == 0)
		*key = l_key;
	if (strncmp(buf, "s", 1) == 0)
		*key = s_key;
	if (strncmp(buf, "r", 1) == 0)
		*key = r_key;
	if (strncmp(buf, "t", 1) == 0)
		*key = t_key;
	if (strncmp(buf, "i", 1) == 0)
		*key = i_key;
	if (strncmp(buf, "q", 1) == 0)
		*key = quit_key;
	if (strncmp(buf, "\n", 1) == 0)
		*key = enter_key;
	if (strncmp(buf, "\033[[E", 4) == 0)
		*key = f5_key;
	if (strncmp(buf, "\033[17~", 5) == 0)
		*key = f6_key;
	if (strncmp(buf, "\033[A", 3) == 0)
		*key = up_key;
	if (strncmp(buf, "\033[B", 3) == 0)
		*key = down_key;
	if (strncmp(buf, "\033[C", 3) == 0)
		*key = right_key;
	if (strncmp(buf, "\033[D", 3) == 0)
		*key = left_key;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		return -1;
	
	return (int)buf[0];
}

int rk_mytermsave()
{
	struct termios saved_term;
	FILE *f = NULL;
	if(tcgetattr(STDIN_FILENO, &saved_term) != 0)
		return 1;
	if((f = fopen("term_set.dat", "wb")) == NULL)
		return 1;
	fwrite(&saved_term, sizeof(saved_term), 1, f);
	fclose(f);
	return 0;
}

int rk_mytermrestore ()
{
	struct termios saved_term;
	FILE *f = NULL;
	if((f = fopen("term_set.dat", "rb")) == NULL)
		return 1;
	if(fread(&saved_term, sizeof(saved_term), 1, f) <= 0)
		return 1;
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_term) != 0)
		return 1;
	return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios term;
	if(tcgetattr(STDIN_FILENO, &term) != 0)
		return 1;
	if(regime == 0)
		term.c_lflag |= ICANON;
	else if(regime == 1)
	{
		term.c_lflag &= (~ICANON);
		term.c_cc[VTIME] = vtime;
		term.c_cc[VMIN] = vmin;
		
		if(echo == 0)
			term.c_lflag &= (~ECHO);
		else if(echo == 1)
			term.c_lflag |= ECHO;
			else return 1;
		
		if(sigint == 0)
			term.c_lflag &= (~ISIG);
		else if(sigint == 1)
			term.c_lflag |= ISIG;
			else return 1;
	}
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		return 1;
	
	return 0;
}
