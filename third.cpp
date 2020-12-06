#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* thread_func(void *arg)
{
    while(1)
    {
        time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	printf("Child thread is talking at%d:%d:%d | thread id=%lu\n",8+p->tm_hour,p->tm_min,p->tm_sec,pthread_self());
    }
    return arg;
}
 
int main(void)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    printf("Main thread is talking at%d:%d:%d | ",8+p->tm_hour,p->tm_min,p->tm_sec);
    printf("process id=%d\n", pid);
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid,NULL);
    return 0;
}
