#ifndef SC_LIBS
#define SC_LIBS

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#endif //SC_LIBS

#ifndef MY_READ_KEY
#define MY_READ_KEY

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
	no_key,
	key_0,
	key_1 = 15,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6 = 20,
	key_7,
	key_8,
	key_9,
	key_a,
	key_b = 25,
	key_c,
	key_d,
	key_e,
	key_f = 29
};

int rk_readkey(enum keys *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif //MY_READ_KEY
