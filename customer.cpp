#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<errno.h>

sem_t mutex,customers,barber;
int waiting = 0;//the number of waiting customers
int chairs[6];

void *customer(void *args)
{	
	int i;
	sem_post(&mutex);
	if(waiting<6)
	{
	
		for(i = 0;i < 6;i++)
		{
			if(!chair[i])chair[i] = (int)args;
		}
		waiting++;
	
	printf("Customer NO.%d are waiting,sitting at chair NO.%d",(int)args,i+1);
	sem_post(&mutex);
	sem_post(&customers);
	sem_wait(&barbers);
	}
	else
	{
		printf("No waiting seat for customer NO.%d.\n",(int)args);
		sem_wait(&mutex);
	}
}

void *barber(void *args)
{
	int i;
	sem_wait(&customers);
	sem_wait(&mutex);
	waiting--;
	int c;
	for(int i = 0;i < 6;i++)
	{
		if(chairs[i])
		{
			c = chairs[i];
			chairs[i] = 0;
			break;
		}
	}	
	printf("Customer NO.%d is getting the haircut.\n",c);
	sleep(1);
	sem_post(&barber);
	sem_post(&mutex);
} 

int main()
{
	pthread_t Customer_id[10],Barber_id;
    int i;
    sem_init ( &mutex,0,1 );  
    sem_init ( &customers,0,0 );
    sem_init ( &barbers,0,1 );
    for ( i=0; i<6; i++ )
        pthread_create ( &Barber_id,NULL, ( void* ) barber,NULL );
    for ( i=0; i<20; i++ )
        pthread_create ( &Customer_id[i],NULL, ( void* ) customer, ( void* ) ( i+1 ) );
   //回收线程资源
    for ( i=0; i<20; i++ )
        pthread_join ( Customer_id[i],NULL );
    for ( i=0; i<6; i++ )
        pthread_join ( Barber_id,NULL );
}
 
