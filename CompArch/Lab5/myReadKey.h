#ifndef MY_READ_KEY
#define MY_READ_KEY

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

enum keys {
	l_key = 0,
	s_key,
	r_key, 
	t_key,
	i_key,
	quit_key = 5,
	f5_key,
	f6_key,
	enter_key,
	up_key,
	down_key = 10,
	left_key,
	right_key,
	no_key = 13
};

int rk_readkey(enum keys *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif //MY_READ_KEY
