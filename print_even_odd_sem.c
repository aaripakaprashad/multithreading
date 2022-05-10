//http://www.vishalchovatiya.com/semaphore-between-processes-example-in-c/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;

void * odd_thread(void *arg) { //even
	for(int i=1; i<15;i+=2) {
		printf("odd T1:%d\n",i);
		sem_post(&sem2);
		sem_wait(&sem1);  
	}
}


void * even_thread(void *arg) { //odd
	for(int i=2; i<15;i+=2) {
		sem_wait(&sem2);
		printf("Even T2:%d\n",i);
		sem_post(&sem1);
	}
}


int main() {
	if (sem_init(&sem1, 0, 0) == -1) //second argument '0' means, using semaphore between threads related.
               printf("sem_init Error\n");//second argument is 1 means, semaphore is used between process
	if (sem_init(&sem2, 0, 0) == -1) 
               printf("sem_init Error\n");

	pthread_t tid1, tid2; 
	pthread_create(&tid1, NULL, even_thread, NULL);
	pthread_create(&tid2, NULL, odd_thread, NULL);
        
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
	
	sem_destroy(&sem1);
	sem_destroy(&sem2);
    
    return 0;
}
