#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void pTime()
{
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	printf("Child thread is talking at%d:%d:%d",8+p->tm_hour,p->tm_min,p->tm_sec);
} 
void* thread_func(void *arg)
{
	pTime();
	printf(" thread id=%lu\n",pthread_self());
    return arg;
}
 
int main(void)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    pTime();
    printf("process id=%d\n", pid);
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid,NULL);
    return 0;
}
