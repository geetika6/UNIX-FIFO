#include "header.h"
int main(int argc, char *argv[])
{

	pid_t pid;
	int rfd,wfd;
	int nbytes,result;
	char operator,res[4];
	struct data
	{
		int first,second;
		char operator;
	}data_to_send;
	struct data *rdata;
	rdata=&data_to_send;
	
	switch(rdata->operator)
	{
		case '+':
			result=rdata->first + rdata->second;
			break;

		case '-':
			result=rdata->first - rdata->second;
			break;

		case '*':
			result=rdata->first * rdata->second;
			break;

		case '/':
			result=rdata->first / rdata->second;
			break;
	}

	printf("In processing client result=%d\n",result);
        //sprintf(res,"%d",result);
        write(wfd,&result,sizeof(result));
}

