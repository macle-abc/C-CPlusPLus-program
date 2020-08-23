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
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
	int msg_id = msgget(key, IPC_CREAT);
	if (msg_id < 0)
	{
		perror("msgget error!");
		return -1;
	}
	char buff[BUFSIZ] = { 0 };
	sprintf(buff, "Client process pid is %d", getpid());
	struct msgbuf buf;
	buf.mtype = 2;
	strncpy(buf.mtext, buff, strlen(buff));
	if (msgsnd(msg_id, (void*)&buf, sizeof(buf.mtext), 0) < 0)
	{
		perror("msgsnd error!");
		return -1;
	}
	int size = sizeof(buf.mtext);
	if (msgrcv(msg_id, (void*)&buf, size, 1, 0) < 0)
	{
		perror("msgrcv error!");
		return -1;
	}
	strncpy(buff, buf.mtext, size);
	buff[size] = 0;
	printf("Client process recv:%s\n", buff);
	return 0;
}
