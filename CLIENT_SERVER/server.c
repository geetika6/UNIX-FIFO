#include "header.h"
int main()
{

        int pipefd;
        int pipefd1[2];
        //char buffer[BUFFER_SIZE+1];
	int nbytes,stat,res,bytes_read,result=0;
	struct data *rdata;
        bytes_read=0;
        rdata=malloc(sizeof(struct data));
	memset(rdata,'\0',sizeof(struct data));
        if (access(REQFIFO,F_OK)==-1)
	{
	        stat=mkfifo(REQFIFO,0777);
        	perror("rq_fifo");
                if(stat!=0)
		{
			fprintf(stderr,"fifo not created\n");
                        exit(EXIT_FAILURE);
		}
	}
        if (access(PROCESSINGFIFO,F_OK)==-1)
	{
	        stat=mkfifo(PXFIFO,0777);
        	perror("px_fifo");
                if(stat!=0)
		{
			fprintf(stderr,"fifo not created\n");
                        exit(EXIT_FAILURE);
		}
	}
        reqfd=open(REQFIFO,O_RDONLY|O_NONBLOCK);
        pxfd=open(PXFIFO,O_RDWR);
        if ((reqfd && pxfd)!=-1)
        {
                while(1)
                {

	  		res=read(reqfd,rdata,sizeof(struct data));
  			res1=write(pxfd,rdata,BUFFER_SIZE);

        		(void)close(pipefd);
		}
	}
        else
        {
                exit(EXIT_FAILURE);
	
	}
         
        exit(EXIT_SUCCESS);
}
