#include<unistd.h>
#include<stdio.h> 
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h> 
void child(void)
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
int main(void)
{
    pid_t pid;
    pid = fork();
    child();
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
