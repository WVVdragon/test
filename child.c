#include<stdio.h> 
#include<time.h>
#include<windows.h>
#include<stdlib.h>
int main()
{
	while(true)
	{
		time_t timep;
	    struct tm *p;
	    time (&timep);
	    p=gmtime(&timep);
	    printf("The child is talking at%d:%d:%d\n",8+p->tm_hour,p->tm_min,p->tm_sec); 
	    sleep(1000);
	}
    
}