/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>

int n=0;
#defind MAX 10 

void * even(void *arg1)
{
    while(1) {
    if(n%2==0){
        printf("even:%d\n",n);
        n++;
    }
    if(n > MAX)
       pthread_exit((void *)NULL);
    }
        
}

void * odd(void *arg2){
    while(1) {
    if(n%2 ==1){
        printf("odd:%d\n",n);
        n++;
    }
    if(n > MAX)
       pthread_exit((void*)NULL);
    }   
}

int main()
{
    printf("Hello World");
    
    pthread_t tid1,tid2;
    pthread_create(&tid1, NULL, even, NULL);
    pthread_create(&tid2, NULL, odd, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

  return 0;
}
