void *thread_start(void *args)
{
    if (pthread_detach( pthread_self()))
        perror("Fail reason:");
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
        if (count % 10000 == 0)
        {
            printf("Number of threads are created: %ld\n", count);
        }
    }
    return 0;
}
