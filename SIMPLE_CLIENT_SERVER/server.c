#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>


#define INGOING "clientToServer.fifo"

#define BUFFER 200

int main(int argc, char *argv[]) 
{
	char in[BUFFER];
	mkfifo(INGOING, 0666);
	printf("Welcome to server.\n");
	printf("channel for sending messages to server is %s\n", INGOING);

//to keep the server running forever, make the open call as RDWR instead of RDONLY. this will block it from closing the pipe
//or instead make the while loop as while(1)
//	int in_fd=open(INGOING, O_RDONLY);
	int in_fd=open(INGOING, O_RDWR);

	if (in_fd==-1) 
	{
		perror("open error");
		exit(-1);
	}
	int nbytes;
//	while(1)
 //       {
//        if ((nbytes = read(in_fd, in, sizeof(in))) > 0)
	while((nbytes = read(in_fd, in, sizeof(in))) > 0) 
		printf("You sent [%.*s] to the server\n", nbytes, in);
	//}
	return 2;

}

