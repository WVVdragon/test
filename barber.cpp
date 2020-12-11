#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<errno.h>
sem_t mutex,customers,barbers;//三个信号量，对应互斥信号量，顾客信号量，理发师
int waiting=0;  //等待的顾客数量
int chair[3];//三把椅子
int moneys=0;//赚取的钱数
int n=0;//记录第几次理发
void * barber();//理发师线程函数
void * customer ( void *arg );//顾客线程函数
int main ()
{
    //创建10个顾客线程和1个理发师线程
    pthread_t Customer_id[10],Barber_id;
    int i;
    sem_init ( &mutex,0,1 );  //互斥信号量初始化1
    sem_init ( &customers,0,0 );//顾客信号量初始化0
    sem_init ( &barbers,0,1 );//理发师信号量初始化1
   //下面循环让顾客或者理发师去抢占线程，满足条件就可执行，不行就阻塞，直到信号量满足条件
    for ( i=0; i<3; i++ )
        pthread_create ( &Barber_id,NULL, ( void* ) barber,NULL );
    for ( i=0; i<10; i++ )
        pthread_create ( &Customer_id[i],NULL, ( void* ) customer, ( void* ) ( i+1 ) );
   //回收线程资源
    for ( i=0; i<10; i++ )
        pthread_join ( Customer_id[i],NULL );
    for ( i=0; i<3; i++ )
        pthread_join ( Barber_id,NULL );
    return -1;
}

void * customer ( void *arg )
{
    int i;
    sem_wait ( &mutex ); //等待互斥锁释放
    if ( waiting<3)
    {
        waiting++;  //等待的顾客加1
        for ( i=0; i<3; i++ )
        {
            if ( chair[i]==0 )
            {
                chair[i]= ( int ) arg;
                break;
            }
         }
 
        printf ( "-----------------------------------------------------\n" );
        printf ( "%d号顾客进来了，坐在第%d把椅子上 \n", ( int ) arg, (i+1));
        printf ( "这个理发店总共有%d顾客在店里 \n",waiting );
        printf ( "这些顾客分别坐在椅子上的位置:" );
        for ( i=0; i<3; i++ )
            printf ( "%d ",chair[i]);
        printf ( "\n" );
        sleep(1);
        sem_post ( &mutex ); //释放互斥锁
        sem_post ( &customers );
        sem_wait ( &barbers ); //理发师等待
    }
    else
    {
        printf ( "%d号顾客想要进来理发，但理发店已经没有椅子，这位顾客离开了! \n", ( int ) arg );
        sem_post ( &mutex );
    }
        return 0;
}


void * barber()
{
    int i;
    int next;//记录当前的理发顾客号
    //等待顾客，如果没有顾客，理发师阻塞
    sem_wait ( &customers );
    sem_wait ( &mutex );  //等待互斥锁释放
    waiting--;   //等待的顾客减1
    for ( i=0; i<3; i++ )
    {
        if ( chair[i]!=0 )
        {
            
            next= chair[i];            
            chair[i]=0;
            break;
        }
     }
    printf ( "这个理发师正在给%d号顾客理发\n",next);
    int times;//每次理发的时间
    times=rand()%10+5;
    moneys=moneys+times;//每次赚取的钱数，累加，因为一秒钟对应一块钱
    printf("理发完成!用时%ds.这是第%d次理发，目前总共赚取%d元钱.\n",times,++n,moneys);
    sleep (times);
    sem_post ( &mutex );
    sem_post ( &barbers);
    return 0;
}
