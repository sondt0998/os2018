#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define BUFFER_SIZE 10

typedef struct
{
   char type;   // 0=fried chicken, 1=French fries
   int amount;  // pieces or weight
   char unit;   // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) 
{
   while ((first + 1) % BUFFER_SIZE == last)   
   {
      // do nothing -- no free buffer item
   }
   memcpy(&buffer[first], i, sizeof(item));
   first = (first + 1) % BUFFER_SIZE;
}

item *consume() 
{ 
   item *i = malloc(sizeof(item));
   while (first == last) 
   {
      // do nothing -- nothing to consume
   }
   memcpy(i, &buffer[last], sizeof(item));
   last = (last + 1) % BUFFER_SIZE;
   return i;
}

int main()
{
   item i1 = {0, 10, 1};
   item i2 = {1, 50, 0};
   printf("After producing item 1(): ");
   produce(&i1);
   printf("first = %d, last = %d\n", first, last);
   printf("After producing item 2(): ");
   produce(&i2);
   printf("first = %d, last = %d\n", first, last);
   printf("After consuming item(): ");
   consume();
   printf("first = %d, last = %d\n", first, last);
   return 0;
}

