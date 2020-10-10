#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

int  count = 0;

#define DONE  10
#define T1  3
#define T2  6


pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

void *functionCount1()
{
   for(;;)
   {
      pthread_mutex_lock( &condition_mutex );
      while( count >= T1 && count <= T2 )
      {
         pthread_cond_wait( &condition_cond, &condition_mutex );
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      ++count;
      sleep(1);
      printf("Counter value functionCount1: %d\n",count);
      pthread_mutex_unlock( &count_mutex );
      if(count >= DONE)
         pthread_exit(NULL);
    }
}

void *functionCount2()
{
    for(;;)
    {
       pthread_mutex_lock( &condition_mutex );
       if( count < T1 || count > T2 )
       {
          pthread_cond_signal( &condition_cond );
       }
       pthread_mutex_unlock( &condition_mutex );

       pthread_mutex_lock( &count_mutex );
       ++count;
       sleep(1);
       printf("Counter value functionCount2: %d\n",count);
       pthread_mutex_unlock( &count_mutex );
       if(count >= DONE)
          pthread_exit(NULL);
    }
}



main()
{
   pthread_t thread1, thread2;
   int ret1, ret2;

   ret1 = pthread_create( &thread1, NULL, &functionCount1, NULL);
   ret2 = pthread_create( &thread2, NULL, &functionCount2, NULL);
   if ( 0 != ret1 || 0 != ret2 )
        perror("False reason:");
   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   exit(0);
}




