#include "stdio.h"  
#include "pthread.h"  
#include "stdlib.h"  
  
int shared_var = 0;  
pthread_t thread1;  
  
void m_add(){  
   while(1){  
      printf("%d\n",++shared_var);   //���shared_var����1���ֵ  
   }  
}  
void *thread_dec(void *arg){  
   while(1){  
      printf("%d\n",--shared_var);      //���̣߳����shared_var�Լ�1���ֵ  
   }  
}  
void main(void *arg){  
       
     int i = pthread_create(&thread1,NULL,thread_dec,NULL);   //�������߳�  
     if(i != 0){  
         printf("�̴߳���ʧ�ܣ�\n");  
     }  
     m_add();    //��������1����  
     return ;  
}  
