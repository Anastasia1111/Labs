
int tcgetattr (int fd, struct termios *tsaved);
int tcsetattr (int fd, int actions, const struct termios *tnew);

int rk_readkey (enum keys *key)
{
	struct termios term;
	char buf[8];
	int num_read;
	
	if (tcgetattr(STDIN_FILENO, &term) != 0)
		return -1;
	if (rk_mytermregime(0, 0, 1, 0, 1) != 0)
		return -1;
	num_read = read(STDIN_FILENO, buf, 7);
	if (num_read < 0)
		return -1;
	buf[num_read] = 0;
	if (strcmp(buf, "l") == 0)
		*key = l_key;
	if (strcmp(buf, "s") == 0)
		*key = s_key;
	if (strcmp(buf, "r") == 0)
		*key = r_key;
	if (strcmp(buf, "t") == 0)
		*key = t_key;
	if (strcmp(buf, "i") == 0)
		*key = i_key;
	if (strcmp(buf, "q") == 0)
		*key = q_key;
	if (strcmp(buf, "\n") == 0)
		*key = enter_key;
	if (strcmp(buf, "\033[15~") == 0)
		*key = f5_key;
	if (strcmp(buf, "\033[17~") == 0)
		*key = f6_key;
	if (strcmp(buf, "\033[A") == 0)
		*key = up_key;
	if (strcmp(buf, "\033[B") == 0)
		*key = down_key;
	if (strcmp(buf, "\033[C") == 0)
		*key = right_key;
	if (strcmp(buf, "\033[D") == 0)
		*key = left_key;
	*key = no_key;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		return -1;
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

