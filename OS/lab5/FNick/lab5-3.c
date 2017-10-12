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
	char buf[255];
};

int main()
{
	key_t key = ftok("./text", 42L);
	int msgid = msgget(key, IPC_CREAT);
	struct msg tmp;
	switch(fork())
	{
		case 0:
			msgrcv(msgid, &tmp, sizeof(tmp), 46L, 0);
			printf("%s\n", tmp.buf);
			break;
		default:
			tmp.mtype = 46L;
			strcpy(tmp.buf, "Hello World!");
			msgsnd(msgid, (void*)&tmp, sizeof(tmp), 0);
			wait(0);
			break;
	}
	return 0;
}
