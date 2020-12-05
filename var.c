#include "stdio.h"  
#include "pthread.h"  
#include "stdlib.h"  
  
int shared_var = 0;  
pthread_t thread1;  
  
void m_add(){  
   while(1){  
      printf("%d\n",++shared_var);   //输出shared_var自增1后的值  
   }  
}  
void *thread_dec(void *arg){  
   while(1){  
      printf("%d\n",--shared_var);      //子线程，输出shared_var自减1后的值  
   }  
}  
void main(void *arg){  
       
     int i = pthread_create(&thread1,NULL,thread_dec,NULL);   //创建子线程  
     if(i != 0){  
         printf("线程创建失败！\n");  
     }  
     m_add();    //调用自增1函数  
     return ;  
}  
