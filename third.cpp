#include "stdio.h"  
#include "pthread.h"  
#include "stdlib.h"  
#include <sys/syscall.h>
pthread_t thread1;  
  
void *thread_dec(void *arg){  
   printf("child%d",syscall(SYS_gettid));
}  
void main(void *arg){  
       
     int i = pthread_create(&thread1,NULL,thread_dec,NULL);   //创建子线程  
     if(i != 0){  
         printf("线程创建失败！\n");  
     }  
     printf("parent%d",syscall(SYS_gettid))   //调用自增1函数  
     return ;  
}  
