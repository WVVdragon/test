#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pid;

    int n = 0;  //测试父进程和子进程是否共享一个n

    pid = fork();

    if(pid < 0)
    {
        /* 创建子进程失败 */
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
