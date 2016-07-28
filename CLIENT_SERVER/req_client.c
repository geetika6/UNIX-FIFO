#include "header.h"
int main(int argc, char **argv)
{

	int reqfd,resfd,client_fifo_fd,num_data;
	char client_fifo[256];
	int stat,res=0;
	int result[10];
	struct data *rdata[10];
	struct data *resdata[10];
	pid_t pid;
	num_data=(int)(argv[1][0]-'0');
	printf("num_data =%d\n",(int)(argv[1][0]-'0'));

	for(int i=0;i<num_data;i++)
	{
		rdata[i]=malloc(sizeof(struct data));
		resdata[i]=malloc(sizeof(struct data));
		rdata[i]->first=rdata[i]->first+i;
		rdata[i]->second=rdata[i]->first+rdata[i]->second+i;
		rdata[i]->operator_name=operator_type[i];
		rdata[i]->pid=getpid();
		//if (i==5)
		//	i=0;
	}

	//MAKE client fifo with the process id in its name
	sprintf(client_fifo,OP_CLIENT_FIFO,getpid());
	//printf("client_fifo_idin req_client=%s\n",client_fifo);
	stat=mkfifo(client_fifo,0777);
	if(stat!=0)
	{
		perror("make client_fifo");
		exit(EXIT_FAILURE);
	}
	//Open the request FIFO and place the various data packets with the respective operations        
	reqfd=open(REQFIFO,O_WRONLY);
	if (reqfd==-1)
	{
		perror("req_fifo_open_client");
		exit(EXIT_FAILURE);
	}
	int j=0;
	while(1)
	{	
		if (write(reqfd,rdata[j],sizeof(struct data))>0) 
		{
			//printf("Process id =%d,data sent=%d and %d and operator sent=%c and pid sent=%d\n",getpid(),rdata[j]->first,rdata[j]->second,rdata[j]->operator_name,rdata[j]->pid);
			j++;
		}
		if (j==num_data) 
		{
			printf("Bye!\n");
			break;
		}


	}

	//Now recieve the result of the operations
	client_fifo_fd=open(client_fifo,O_RDONLY);
	perror("client_fifo_open_result");
	if(client_fifo_fd!=-1)
	{	
		int j=0;
		while(1)
		{
			if(stat=read(client_fifo_fd,resdata[j],sizeof(struct data))>0)
			{
				result[j]=resdata[j]->result;
				printf("result=%d\n",result[j]);
				j++;

			}
			if (j==num_data) 
			{
				printf("Result Done!\n");
				break;
			}
		}
	}
	exit(EXIT_SUCCESS);
}
