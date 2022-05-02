/*
 *o/p: A B C D E F G H ............Z 
 */


#include <stdio.h>
#include <pthread.h>

#define MAX 25

int n=0;
pthread_mutex_t lock;
pthread_cond_t cv;

//A  C  E  F  H .......
void * t1(void *arg1)
{
    while(1) {
        pthread_mutex_lock(&lock);
        if(!(n%2)) {
            printf("t1:%c\n",n+'A');
            n++;
        }
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
        if(n >= MAX)
            pthread_exit((void *)NULL);
 
    }
        
}

// B  D  F  H  J ......
void * t2(void *arg2){
    while(1) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cv,&lock);
        if(n%2){
            printf("t2:%c\n",n+'A');
            n++;
        }
        pthread_mutex_unlock(&lock);
        if(n >= MAX)
            pthread_exit(NULL);
    }   
}

int main()
{
    printf("Hello World\n");

    pthread_t tid1,tid2;
    pthread_create(&tid1, NULL, t1, NULL);
    pthread_create(&tid2, NULL, t2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
