#include "header.h"
int main()
{

        int pipefd;
        int pipefd1[2];
        char buffer[BUFFER_SIZE+1];
	int nbytes,stat,res,bytes_sent,result=0;
        struct data
        {
          int first,second;
	  char operator;
        }data_to_send;
	struct data *rdata;
        rdata=&data_to_send;
	pid_t pid;
        if (access(MYFIFO,F_OK)==-1)
	{
	        stat=mkfifo(MYFIFO,0777);
        	perror("fifo");
                if(stat!=0)
		{
			fprintf(stderr,"fifo not created\n");
                        exit(EXIT_FAILURE);

		}

	}
        pipefd=open(MYFIFO,O_WRONLY);
        printf("Process id =%d,fd =%d\n",getpid(),pipefd);
        if (pipefd!=-1)
        {
        	while(bytes_sent< TEN_MEG)
                {   
  			res=write(pipefd,buffer,BUFFER_SIZE);
			if(res==-1)
			{
				fprintf(stderr,"write on fifo not done\n");
                	        exit(EXIT_FAILURE);
			}
                	bytes_sent+=res;
                        printf("data written =%d\n",bytes_sent);
		}

        	(void)close(pipefd);
	}
        else
        {
                exit(EXIT_FAILURE);
	
	}
        printf("Process id =%d,bytes sent=%d\n",getpid(),bytes_sent);
        exit(EXIT_SUCCESS);
}
