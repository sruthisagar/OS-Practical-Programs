#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];

void eat(int p)
{
    printf("Philosopher %d eats\n", p);
    sleep(2);
}

void *philosophers(void *n)
{
    int p = *(int *)n;
    printf("Philosopher %d wants to eat\n", p);
    printf("Philosopher %d tries to take left chopstick\n", p);
    sem_wait(&chopstick[p]);
    printf("Philosopher %d picks left chopstick\n", p);
    printf("Philosopher %d tries to take right chopstick\n", p);
    sem_wait(&chopstick[(p + 1) % 5]);
    printf("Philosopher %d picks right chopstick\n", p);
    eat(p);
    printf("Philosopher %d finished eating\n", p);
    sem_post(&chopstick[(p + 1) % 5]);
    printf("Philosopher %d left right chopstick\n", p);
    sem_post(&chopstick[p]);
    printf("Philosopher %d left left chopstick\n", p);
}

void main()
{
    int i, n[5];
    pthread_t t[5];

    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1); //initialize each chopstick shared with thread(0) with value 1
    for (i = 0; i < 5; i++)
    {
        n[i] = i;
        pthread_create(&t[i], NULL, philosophers, (void *)&n[i]); //excecution of thread starts from fun philosophers passing parameter n[i]
    }
    for (i = 0; i < 5; i++)
        pthread_join(t[i], NULL);
}
