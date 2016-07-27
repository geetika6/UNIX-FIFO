#include "header.h"
int rc1, rc2;

pthread_t thread1, thread2;
struct data *rdata;
int reqfd,pxfd,resfd,client_fifo_fd;
char client_fifo[256];
struct data *arr_data[100];


void *read_req()
{ 
	int res,res1;
	while(1)
	{
		if(res=read(reqfd,rdata,sizeof(struct data))>0)
			printf("Server read data, first =%d,second=%d and operator=%c\n",rdata->first,rdata->second,rdata->operator_name);
	}
}
//void *send_req()
//{ 
//	int res,res1;
//	while(1)
//	{
//		res1=write(pxfd,rdata,sizeof(struct data));
//		printf("Server Process data, first =%d,second=%d and operator=%c\n",rdata->first,rdata->second,rdata->operator_name);
//	}
//void *read_res()
//{ 
//	int res,res1;
//	while(1)
//	{
//		res=read(resfd,rdata,sizeof(struct data));
//		printf("Server Processed data first =%d,second=%d and operator=%c and result=%d\n",rdata->first,rdata->second,rdata->operator_name,rdata->result);
//		//open client fifo with the process id in its name
//		sprintf(client_fifo,OP_CLIENT_FIFO,rdata->pid);
//		client_fifo_fd=open(client_fifo,O_WRONLY);
//		res1=read(client_fifo_fd,rdata,sizeof(struct data));
//		//(void)close(reqfd);
//	}
//}
int main()
{

	int *result[100];
	//char buffer[BUFFER_SIZE+1];
	int stat,res,res1=0;
	rdata=malloc(sizeof(struct data));
	memset(rdata,'\0',sizeof(struct data));
	if (access(REQFIFO,F_OK)==-1)
	{
		stat=mkfifo(REQFIFO,0777);
		if(stat!=0)
		{
			perror("rq_fifo");
			exit(EXIT_FAILURE);
		}
	}
//	if (access(PXFIFO,F_OK)==-1)
//	{
//		stat=mkfifo(PXFIFO,0777);
//		if(stat!=0)
//		{
//			perror("px_fifo");
//			exit(EXIT_FAILURE);
//		}
//	}
//	if (access(RESFIFO,F_OK)==-1)
//	{
//		stat=mkfifo(RESFIFO,0777);
//		if(stat!=0)
//		{
//			perror("res_fifo");
//			exit(EXIT_FAILURE);
//		}
//	}
	//reqfd=open(REQFIFO,O_RDONLY);
	reqfd=open(REQFIFO,O_RDWR);
//	pxfd=open(PXFIFO,O_WRONLY);
	printf("Server Process id =%d,reqfd=%d\n",getpid(),reqfd);
	if (reqfd ==-1) 
	{
		perror("reqfd and pxfd open");
		exit(EXIT_FAILURE);
	}
	else
	{
		pthread_create( &thread1, NULL, &read_req, NULL);
        	perror("server read_req thread\n");
	}
     pthread_join( thread1, NULL);

 
//	resfd=open(RESFIFO,O_RDONLY);
//	//while(1)
//	if (resfd ==-1)
//	{
//		perror("reqfd and pxfd open");
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		pthread_create( &thread2, NULL, &read_res, NULL);
//	}
	exit(EXIT_SUCCESS);
}
