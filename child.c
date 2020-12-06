#include<stdio.h> 
#include<time.h>
#include <unistd.h>
#include<stdlib.h>
int main()
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
    return 0;
}
