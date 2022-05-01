/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>

#define MAX 10

int n=0;
pthread_mutex_t lock;
pthread_cond_t cv;

void * even(void *arg1)
{
    while(1) {
        pthread_mutex_lock(&lock);
        if(!(n%2)){
            printf("even:%d\n",n);
            n++;
        }
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
        if(n >MAX)
            pthread_exit((void *)NULL);
    }
        
}

void * odd(void *arg2){
    while(1) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cv,&lock);
        if(n%2){
            printf("odd:%d\n",n);
            n++;
        }
        pthread_mutex_unlock(&lock);
        if(n >MAX)
            pthread_exit((void*)NULL);
    }   
}

int main()
{
    printf("Hello World\n");

    pthread_t tid1,tid2;
    pthread_create(&tid1, NULL, even, NULL);
    pthread_create(&tid2, NULL, odd, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
