#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>

#define T1 4
#define T2 8 
#define DONE 10

int count;
void *functionCount1();
void *functionCount2();

void main()
{
    pthread_t thread1, thread2;
    int ret1, ret2;
    
    ret1 = pthread_create(&thread1, NULL, &functionCount1, NULL);
    ret2 = pthread_create(&thread2, NULL, &functionCount2, NULL);
    if ( 0 != ret1 || 0 != ret2 )
        perror("False reason: ");
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );
}

void *functionCount1()
{
        while (count <= T1 || count >= T2)
        {
            count += 1;
            printf("count value functionCount1: %d\n", count);
            sleep(2);
            if (count == DONE) 
                pthread_exit(NULL);
        }
}

void *functionCount2()
{
    while (count > T1 && count < T2)
    {
        count += 1;
        printf("count value functionCount2: %d\n", count);
        sleep(2);
        if (count == DONE)
            pthread_exit(NULL);
    }
}
