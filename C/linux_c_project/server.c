#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
struct msgbuf
{
    long mtype;
    char mtext[BUFSIZ];
};       

int main()
{
	key_t key = ftok("./", 0x6666);
	if (key < 0)
	{
		perror("ftok error!");
		return -1;
	}
	int msg_id = msgget(key, IPC_CREAT|IPC_EXCL|0666);
	if (msg_id < 0)
	{
		perror("msgget error!");
		return -1;
	}
	char buff[BUFSIZ] = { 0 };
	sprintf(buff, "Server process pid is %d", getpid());
	struct msgbuf buf;
	buf.mtype = 1;
	strncpy(buf.mtext, buff, strlen(buff));
	if (msgsnd(msg_id, (void*)&buf, sizeof(buf.mtext), 0) < 0)
	{
		perror("msgsnd error!");
		return -1;
	}
	int size = sizeof(buf.mtext);
	if (msgrcv(msg_id, (void*)&buf, size, 2, 0) < 0)
	{
		perror("msgrcv error!");
		return -1;
	}
	strncpy(buff, buf.mtext, size);
	buff[size] = 0;
	printf("Server process recv:%s\n", buff);
	if (msgctl(msg_id, IPC_RMID, NULL) != 0)
	{
		perror("msgctl error!");
		return -1;
	}
	return 0;
}
