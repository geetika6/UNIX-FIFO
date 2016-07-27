#include "header.h"
int main(int argc, char **argv)
{

        int reqfd,resfd,client_fifo_fd,num_data;
        char client_fifo[256];
	int stat,res=0;
        int *result[5];
	struct data *rdata[5];
	pid_t pid;
        num_data=(int)(argv[1][0]-'0');
        printf("num_data =%d\n",(int)(argv[1][0]-'0'));

        for(int i=0;i<num_data;i++)
        {
        	rdata[i]=malloc(sizeof(struct data));
		rdata[i]->first=rdata[i]->first+i;
		rdata[i]->second=rdata[i]->first+rdata[i]->second+i;
                if (i==5)
			i=0;
                rdata[i]->operator_name=operator_type[i];
        }

//MAKE client fifo with the process id in its name
        sprintf(client_fifo,OP_CLIENT_FIFO,getpid());
	stat=mkfifo(client_fifo,0777);
        if(stat!=0)
	{
        	perror("make client_fifo");
                exit(EXIT_FAILURE);
	}
//Open the request FIFO and place the various data packets with the respective operations        
        reqfd=open(REQFIFO,O_WRONLY);
        if (reqfd!=-1)
        {
        	int i=0;
 		while(1)
        	{	

        		printf("Process id =%d,data sent=%d and %d and operator sent=%c\n",getpid(),rdata[i]->first,rdata[i]->second,rdata[i]->operator_name);
			if (write(reqfd,rdata[i],sizeof(struct data))==-1) 
			{
            			perror("write error");
        	       	        exit(EXIT_FAILURE);
       		 	}
                        i++;
                        if (i==num_data) 
			{
            			printf("Bye!\n");
           			break;
       			}


		}
	}

        else
        {
                perror("req_fifo_open_client");
                exit(EXIT_FAILURE);
	
	}
//Now recieve the result of the operations
//        client_fifo_fd=open(client_fifo,O_RDONLY);
//        perror("client_fifo_open_result");
//	if(client_fifo_fd!=-1)
//	{	
//		int j=0;
//		while(j<2)
//		{
//			stat=read(client_fifo_fd,rdata[j],sizeof(struct data));
//			printf("In client with process id=%d,result=%d\n",getpid(),rdata[j]->result);
//  			j++;	
//		}
//	}
        exit(EXIT_SUCCESS);
}
