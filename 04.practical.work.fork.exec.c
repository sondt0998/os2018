#include <stdio.h>
#include <unistd.h>
int main()
{
   int pid =fork();
   printf("Main before fork()\n");
   if (pid == 0)
   {
       int pid1 = fork();
       if (pid1 == 0)
       { 
           printf("I am a child after fork(), launching ps -ef\n");
           char *args1[] = {"/bin/ps", "-ef", NULL};
           execvp("/bin/ps", args1);
       }   
       else
       {
           printf("I am a child after fork(), launching free -h\n");
           char *args2[] = {"free", "-h", NULL};
           execvp("free", args2);
       }
   }
   return 0;
}
