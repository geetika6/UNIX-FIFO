#include "header.h"
int rc1, rc2;

pthread_t thread1, thread2,thread3;
struct data *rdata[10];
struct data *resdata[10];
int reqfd2,pxfd,resfd,client_fifo_fd1;
char client_fifo1[256];

void *send_req(void *data)
{ 
	int res,res1;
	struct data *pxdata;
	pxdata=(struct data*)data;
//	printf("Server send req first =%d,second=%d and operator=%c\n",pxdata->first,pxdata->second,pxdata->operator_name);
	res1=write(pxfd,pxdata,sizeof(struct data));
}

void *read_req()
{ 
	int res,res1;
	printf("Server read data\n");
	pxfd=open(PXFIFO,O_WRONLY);
	perror("server px fifo open\n");
	int i=0;
	while(1)
	{
		if(res=read(reqfd2,rdata[i],sizeof(struct data))>0)
		{	
			pthread_create( &thread2, NULL, &send_req, (void *)rdata[i]);
			perror("server read_req thread\n");
			i++;
		}
	}
}
void *read_res()
{ 
	int res,res1;
	resfd=open(RESULTFIFO,O_RDONLY);
	perror("resfd open");
	if (resfd ==-1)
	{
		perror("resfd reqfd2 and pxfd open");
		exit(EXIT_FAILURE);
	}
	else
	{
		int i=0;
		while(1)
		{
			if(res=read(resfd,resdata[i],sizeof(struct data))>0)
			{
			//	printf("Server Result data no= %d,first =%d,second=%d and operator=%c and result=%d and pid=%d\n",i,resdata[i]->first,resdata[i]->second,resdata[i]->operator_name,resdata[i]->result,resdata[i]->pid);
				//open client fifo with the process id in its name
				sprintf(client_fifo1,OP_CLIENT_FIFO,(int)resdata[i]->pid);
			//	printf("client fifo name=%s\n",client_fifo1);
				client_fifo_fd1=open(client_fifo1,O_WRONLY);
				perror("server client result fifo open\n");
				res1=write(client_fifo_fd1,resdata[i],sizeof(struct data));
				i++;
				//(void)close(reqfd2);
			}
			//printf("value of bytes read in result=%d\n",res);

		}
	}
}
int main()
{

	int stat,res,res1=0;
	for(int i=0;i<10;i++)
	{
		rdata[i]=malloc(sizeof(struct data));
		resdata[i]=malloc(sizeof(struct data ));
		memset(rdata[i],'\0',sizeof(struct data));
		memset(resdata[i],'\0',sizeof(struct data));
	}
	if (access(REQFIFO,F_OK)==-1)
	{
		stat=mkfifo(REQFIFO,0777);
		if(stat!=0)
		{
			perror("rq_fifo");
			exit(EXIT_FAILURE);
		}
	}
	if (access(PXFIFO,F_OK)==-1)
	{
		stat=mkfifo(PXFIFO,0777);
		if(stat!=0)
		{
			perror("px_fifo");
			exit(EXIT_FAILURE);
		}
	}
	if (access(RESULTFIFO,F_OK)==-1)
	{
		stat=mkfifo(RESULTFIFO,0777);
		if(stat!=0)
		{
			perror("res_fifo");
			exit(EXIT_FAILURE);
		}
	}
	//reqfd2=open(REQFIFO,O_RDONLY);
	reqfd2=open(REQFIFO,O_RDWR);
	if (reqfd2 ==-1) 
	{
		perror("reqfd2 open");
		exit(EXIT_FAILURE);
	}
	else
//Launch thread for catching resuests from req clients and send to processing client//running infinite 
	{
		pthread_create( &thread1, NULL, &read_req, NULL);
		perror("server read_req thread\n");
	}

//Launch thread for catching results from processing client and send back to respective client through dedicated fifo for client//running infinite 
	pthread_create( &thread3, NULL, &read_res, NULL);
	perror("Server result thread");
	//	pthread_join( thread3, NULL);
//Waiting for the server process to end its execution by adding a wait of pthread join
	pthread_join( thread1, NULL);
	exit(EXIT_SUCCESS);
}
