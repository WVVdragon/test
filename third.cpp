#include "stdio.h"  
#include "pthread.h"  
#include "stdlib.h"  
#include <sys/types.h>
#include <sys/syscall.h>
pthread_t thread1;  
  
void *thread_dec(void *arg){  
   printf("child%d",syscall(SYS_gettid));
}  
void main(void *arg){  
       
     int i = pthread_create(&thread1,NULL,thread_dec,NULL);   //�������߳�  
     if(i != 0){  
         printf("�̴߳���ʧ�ܣ�\n");  
     }  
     printf("parent%d",syscall(SYS_gettid))   //��������1����  
     return ;  
}  
