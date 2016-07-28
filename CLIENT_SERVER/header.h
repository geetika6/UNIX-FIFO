#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#define REQFIFO "reqfifo"
#define PXFIFO "pxfifo"
#define RESULTFIFO "resultfifo"
#define OP_CLIENT_FIFO "cli_%d_fifo"
char operator_type[5]= {'+','-','*','/','%'}; 
struct data
{
        pid_t pid;
  	int first;
	int second;
	int result;
	char operator_name;
};
