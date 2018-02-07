#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 10

typedef struct
{
   char type;  
   int amount; 
   char unit;   
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

sem_t semaphore;

void produce(item *i) 
{
   while ((first + 1) % BUFFER_SIZE == last)   
   {
      // do nothing -- no free buffer item
   }
   sem_wait(&semaphore);
   memcpy(&buffer[first], i, sizeof(item));
   first = (first + 1) % BUFFER_SIZE;
   sem_post(&semaphore);
}

item *consume() 
{ 
   item *i = malloc(sizeof(item));
   while (first == last) 
   {
      // do nothing -- nothing to consume
   }
   sem_wait(&semaphore);
   memcpy(i, &buffer[last], sizeof(item));
   last = (last + 1) % BUFFER_SIZE;
   sem_post(&semaphore);
   return i;
}

void println(item i) 
{
   printf("Type: %d - Amount(s): %d - Unit:\n",i.type,i.amount,i.unit);
}

void *threadProducer(void *param) 
{
   item chicken, cola, burger;
   chicken.type = '1';
   chicken.amount = 100;
   chicken.unit = '1';
   cola.type = '0';
   cola.amount = 10;
   cola.unit = '0';
   burger.type = '1';
   burger.amount = 50;
   burger.unit = '1';
   produce(&chicken);
   produce(&cola);
   produce(&burger);
}

void *threadConsumer(void *param) 
{
   display(*consume());
   display(*consume());
}

int main()
{
   sem_init(&semaphore, 0, 1);
   pthread_t tid1,tid2;
   pthread_create(&tid1, NULL, threadProducer, NULL);
   pthread_join(tid1, NULL);
   pthread_create(&tid2, NULL, threadConsumer, NULL);
   pthread_join(tid2, NULL);
   sem_destroy(&semaphore);
   return 0;
}


