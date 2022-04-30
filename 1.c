#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//even odd - multithreading - semaphore

void *task1(void *arg1) {
  
   printf("task1\n");
   printf("task1 - arg1:%s\n",(char *)arg1);
   char * t1 = (char *)malloc(64);
   strcpy(t1, "task1-one");
   return (void *)t1;
}

void *task2(void *arg2) {
   
   printf("task2\n");
   printf("task2 - arg2:%s\n",(char *)arg2);
   char * t2 = (char *)malloc(64);
   strcpy(t2, "task2-two");
   return (void *)t2; 
}


int main()
{
     pthread_t tid1,tid2;
     pthread_attr_t attr1, attr2;

     char arg1[12] = "one";
     char arg2[12] = "two";

     pthread_attr_init(&attr1); //stacksize, guardsize,detach state, concurrency, priority, sched_policy, 

     pthread_attr_setguardsize(&attr1, 5000); 

     pthread_create(&tid1, &attr1, task1, (void *)&arg1); 
     pthread_create(&tid2, &attr2, task2, (void *)&arg2);

     size_t g1;
     pthread_attr_getguardsize(&attr1, &g1); 
  
     printf("g1:%ld\n",g1);
     
     char *t1_status = NULL;
     char *t2_status = NULL;
     pthread_join(tid1, (void **)&t1_status);
     printf("main: join tid1 - %s\n",t1_status); //output: task1-one
  
     pthread_join(tid2, (void **)&t2_status);
     printf("main: join tid2 - %s\n",t2_status); //output: task2-two
     }

