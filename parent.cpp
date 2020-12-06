#include <unistd.h>
#include <stdio.h>
#include<time.h>
#include <stdlib.h>
int main(void)
{
    pid_t pid;

    int n = 0; 

    pid = fork();

    if(pid < 0)
    {
        
        printf("fork fail.\n");
        return -1;
    }
    else if(pid == 0)
    {
       	int i;
		for(i = 1;i < 1666;i++)
		{
			time_t timep;
			struct tm *p;
			time (&timep);
			p=gmtime(&timep);
			printf("The child is talking at%d:%d:%d\n",8+p->tm_hour,p->tm_min,p->tm_sec);
			sleep(1);
		}
    }
    else
    {
       	int i;
		for(i = 1;i < 1666;i++)
		{
			time_t timep;
			struct tm *p;
			time (&timep);
			p=gmtime(&timep);
			printf("The parent is talking at%d:%d:%d\n",8+p->tm_hour,p->tm_min,p->tm_sec);
			sleep(1);
		}
    }
}
