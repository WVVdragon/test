#include "stdio.h"  
#include "pthread.h"  
#include "stdlib.h"  
pthread_t thread1;  
  
void *thread_dec(void *arg){  
   printf("child%d\n",pthread_self());
}  
void main(void *arg){  
       
     int i = pthread_create(&thread1,NULL,thread_dec,NULL);   //�������߳�  
     if(i != 0){  
         printf("�̴߳���ʧ�ܣ�\n");  
     }  
     printf("parent%d\n",pthread_self());   //��������1����  
     return ;  
}  
