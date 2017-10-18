#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg
{
	long mtype;
	char mess[255];
};

int main(int argc, char const *argv[])
{
	key_t key = ftok("./text", 42L);
	int msgid = msgget(key, IPC_CREAT);
	struct msg tmp;
	tmp.mtype = 46L;
	switch(fork())
	{
		case 0:
			/*Child*/
			msgrcv(msgid, &tmp, sizeof(tmp), 46L, 0);
			printf("%s\n", tmp.mess);
			break;
			
		default:
			/*Parent*/			
			strcpy(tmp.mess, "Hello World!");
			msgsnd(msgid, (void*)&tmp, sizeof(tmp), 0);
			wait(0);
			break;
	}
	return 0;
}