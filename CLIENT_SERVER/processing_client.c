#include "header.h"
int pxfd1,resfd1;
struct data *pdata[10];
int iret1,iret2;
pthread_t thread4,thread5;
void *process_result(void *rddata)
{
        struct data *pdata=(struct data *)rddata; 
	switch(pdata->operator_name)
	{
		case '+':
			pdata->result=pdata->first + pdata->second;
			break;
		case '-':
			pdata->result=pdata->first - pdata->second;
			break;
		case '*':
			pdata->result=pdata->first * pdata->second;
			break;
		case '/':
			pdata->result=pdata->first / pdata->second;
			break;
		case '%':
			pdata->result=pdata->first % pdata->second;
			break;
	}
        printf("Result in Processing -data recieved=%d and %d and operator=%c and result=%d\n",pdata->first,pdata->second,pdata->operator_name,pdata->result);
        write(resfd1,pdata,sizeof(struct data));
        perror("pxing result write");
	//(void)close(resfd1);
}
void *catch_req()
{ 
	int res,res1,i;
        i=0;
	while(1)
	//for(int i=0;i<2;i++)
	{
		if(res=read(pxfd1,pdata[i],sizeof(struct data))>0)
                {
			iret2=pthread_create( &thread5, NULL, &process_result, (void*)pdata[i]);
        		perror("pxing thread");
                        i++;
		}
	}
}
int main()
{
        for(int i=0;i<10;i++)
        {
        	pdata[i]=malloc(sizeof(struct data));
		memset(pdata[i],'\0',sizeof(struct data));
        }
        pxfd1=open(PXFIFO,O_RDONLY);
	iret1=pthread_create( &thread4, NULL, &catch_req, NULL);
        perror("px catching thread");
        resfd1=open(RESULTFIFO,O_WRONLY);
        perror("pxing result open");
        //sprintf(res,"%d",result);
	pthread_join( thread4, NULL);
}

