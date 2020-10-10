void *thread_start(void *args)
{
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread1;
    int ret;
    long count = 0;
    
    while (1){
        if (ret = pthread_create(&thread1, NULL, thread_start, NULL))
        {
            perror("Fail reason:");
            break;
        }
        usleep(10);
        count++;
        if (0 == count % 10000)
            printf("Number of threads are created: %ld\n", count);
    }
    return 0;
}
