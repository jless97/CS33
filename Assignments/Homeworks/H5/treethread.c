//treethread.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp);

int main(int argc, char* argv[])
{
    int i, j, numberOfThreads;
    
    numberOfThreads = atoi(argv[1]);
    pthread_t *tid = malloc(sizeof(pthread_t) * numberOfThreads);
    
    for (i = 0; i < numberOfThreads; i++)
    {
        pthread_create(&tid[i], NULL, thread, NULL);
        pthread_create(&tid[i], NULL, thread, NULL);
    }
    for (j = 0; j < numberOfThreads; j++)
    {
        pthread_join(tid[j], NULL);
        pthread_join(tid[j], NULL);
    }
    
    free(tid);
    printf("Hello, world\n");
    exit(0);
}

void *thread(void *vargp)
{
    printf("Hello, world\n");
    return NULL;
}

