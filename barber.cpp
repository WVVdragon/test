#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<errno.h>
sem_t mutex,customers,barbers;//�����ź�������Ӧ�����ź������˿��ź�������ʦ
int waiting=0;  //�ȴ��Ĺ˿�����
int chair[3];//��������
int moneys=0;//׬ȡ��Ǯ��
int n=0;//��¼�ڼ�����
void * barber();//��ʦ�̺߳���
void * customer ( void *arg );//�˿��̺߳���
int main ()
{
    //����10���˿��̺߳�1����ʦ�߳�
    pthread_t Customer_id[10],Barber_id;
    int i;
    sem_init ( &mutex,0,1 );  //�����ź�����ʼ��1
    sem_init ( &customers,0,0 );//�˿��ź�����ʼ��0
    sem_init ( &barbers,0,1 );//��ʦ�ź�����ʼ��1
   //����ѭ���ù˿ͻ�����ʦȥ��ռ�̣߳����������Ϳ�ִ�У����о�������ֱ���ź�����������
    for ( i=0; i<3; i++ )
        pthread_create ( &Barber_id,NULL, ( void* ) barber,NULL );
    for ( i=0; i<10; i++ )
        pthread_create ( &Customer_id[i],NULL, ( void* ) customer, ( void* ) ( i+1 ) );
   //�����߳���Դ
    for ( i=0; i<10; i++ )
        pthread_join ( Customer_id[i],NULL );
    for ( i=0; i<3; i++ )
        pthread_join ( Barber_id,NULL );
    return -1;
}

void * customer ( void *arg )
{
    int i;
    sem_wait ( &mutex ); //�ȴ��������ͷ�
    if ( waiting<3)
    {
        waiting++;  //�ȴ��Ĺ˿ͼ�1
        for ( i=0; i<3; i++ )
        {
            if ( chair[i]==0 )
            {
                chair[i]= ( int ) arg;
                break;
            }
         }
 
        printf ( "-----------------------------------------------------\n" );
        printf ( "%d�Ź˿ͽ����ˣ����ڵ�%d�������� \n", ( int ) arg, (i+1));
        printf ( "��������ܹ���%d�˿��ڵ��� \n",waiting );
        printf ( "��Щ�˿ͷֱ����������ϵ�λ��:" );
        for ( i=0; i<3; i++ )
            printf ( "%d ",chair[i]);
        printf ( "\n" );
        sleep(1);
        sem_post ( &mutex ); //�ͷŻ�����
        sem_post ( &customers );
        sem_wait ( &barbers ); //��ʦ�ȴ�
    }
    else
    {
        printf ( "%d�Ź˿���Ҫ���������������Ѿ�û�����ӣ���λ�˿��뿪��! \n", ( int ) arg );
        sem_post ( &mutex );
    }
        return 0;
}


void * barber()
{
    int i;
    int next;//��¼��ǰ�����˿ͺ�
    //�ȴ��˿ͣ����û�й˿ͣ���ʦ����
    sem_wait ( &customers );
    sem_wait ( &mutex );  //�ȴ��������ͷ�
    waiting--;   //�ȴ��Ĺ˿ͼ�1
    for ( i=0; i<3; i++ )
    {
        if ( chair[i]!=0 )
        {
            
            next= chair[i];            
            chair[i]=0;
            break;
        }
     }
    printf ( "�����ʦ���ڸ�%d�Ź˿���\n",next);
    int times;//ÿ������ʱ��
    times=rand()%10+5;
    moneys=moneys+times;//ÿ��׬ȡ��Ǯ�����ۼӣ���Ϊһ���Ӷ�Ӧһ��Ǯ
    printf("�����!��ʱ%ds.���ǵ�%d������Ŀǰ�ܹ�׬ȡ%dԪǮ.\n",times,++n,moneys);
    sleep (times);
    sem_post ( &mutex );
    sem_post ( &barbers);
    return 0;
}
