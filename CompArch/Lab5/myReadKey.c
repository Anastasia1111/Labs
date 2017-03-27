#include <termios.h>
#include <stdio.h>
#include <unistd.h>
int tcgetattr (int fd, struct termios *tsaved);
int tcsetattr (int fd, int actions, const struct termios *tnew);

//enum keys {};

int rk_readkey (/*enum keys *key*/)
{
	return 0;
}

int rk_mytermsave()
{
	struct termios saved_term;
	FILE *f = NULL;
	if(tcgetattr(STDIN_FILENO, &saved_term) != 0)
		return 1;
	if((f = fopen("term_set", "wb")) == NULL)
		return 1;
	fwrite(&saved_term, sizeof(saved_term), 1, f);
	fclose(f);
	return 0;
}

int rk_mytermrestore ()
{
	struct termios saved_term;
	FILE *f = NULL;
	if((f = fopen("term_set", "rb")) == NULL)
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

int main(int argc, char **argv)
{
	return 0;
}

