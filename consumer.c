#include "header.h"
int main()
{

        int pipefd;
        int pipefd1[2];
        char buffer[BUFFER_SIZE+1];
	int nbytes,stat,res,bytes_read,result=0;
        struct data
        {
          int first,second;
	  char operator;
        }data_to_send;
	struct data *rdata;
        rdata=&data_to_send;
	pid_t pid;
        bytes_read=0;
	memset(buffer,'\0',sizeof(buffer));
        pipefd=open(MYFIFO,O_RDONLY);
        printf("Process id =%d,fd =%d\n",getpid(),pipefd);
        if (pipefd!=-1)
        {
        	do

                {   
  			res=read(pipefd,buffer,BUFFER_SIZE);
                	bytes_read +=res;
                        printf("data read =%d\n",bytes_read);
		}
		while(res>0);

        	(void)close(pipefd);
	}
        else
        {
                exit(EXIT_FAILURE);
	
	}
        printf("Process id =%d,bytes read =%d\n",getpid(),bytes_read);
         
        exit(EXIT_SUCCESS);
}
