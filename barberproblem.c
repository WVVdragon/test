#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <math.h>

#define chairNum 6
sem_t cus;
sem_t bar;
pthread_mutex_t mutex;
int waitNum = 0;
int num = 0;

void* barFunction() {
    while(1) 
	{
        if(waitNum == 0) 
		{
            printf("No customers, sleeping now...\n");
        }
        sem_wait(&cus);
        pthread_mutex_lock(&mutex);
        waitNum--;
        pthread_mutex_unlock(&mutex);
        printf("Start: No.%d.\n", ++num);
        sleep(1);
        sem_post(&bar);
	    sleep(1);
        if(!waitNum) 
		{
            break;
        }
    }
    printf("Go off work.\n");
    return 0;
}

void* cusFunction() {
    pthread_mutex_lock(&mutex);
    if(waitNum < chairNum) {
        waitNum++;
        printf("New cunstomer No.%d, %d Waiting.\n", (unsigned int)pthread_self(), waitNum);
        pthread_mutex_unlock(&mutex);
        sem_post(&cus);
        sem_wait(&bar);
        printf("Customer No.%d has Finished.\n", (unsigned int)pthread_self());
    }
    else {
        printf("Customer No.%d has Leaved.\n",(unsigned int)pthread_self());
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main() {
    int i;
    pthread_t barID, cusID;
    sem_init(&cus, 0, 0);
    sem_init(&bar, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&barID, NULL, barFunction, NULL);
    srand((unsigned)time(NULL));
    for(i = 0; i < 20; i++) 
	{
        sleep(rand()%3 + 1);
        pthread_create(&cusID, NULL, cusFunction, NULL);
    }
    pthread_join(barID, NULL);
    printf("Finished customers: %d, Leaved customers: %d.\n", num, 10 - num);
    return 0;
}

