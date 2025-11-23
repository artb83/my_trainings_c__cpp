#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[MAX];
int fill = 0;
int use = 0;
sem_t empty;
sem_t full;
sem_t mutex; // Binary semaphore used as a mutex

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    return tmp;
}

void* producer(void* arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty); // Line P1
        sem_wait(&mutex); // Line P0 (NEW LINE)
        put(i); // Line P2
        sem_post(&mutex); // Line P4 (NEW LINE)
        sem_post(&full); // Line P3
    }
    return NULL;
}

void* consumer(void* arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&full); // Line C1
        sem_wait(&mutex); // Line C0 (NEW LINE)
        int tmp = get(); // Line C2
        sem_post(&mutex); // Line C4 (NEW LINE)
        sem_post(&empty); // Line C3
        printf("%d\n", tmp);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // Initialize semaphores
    sem_init(&empty, 0, MAX); // MAX slots are empty
    sem_init(&full, 0, 0); // 0 slots are full
    sem_init(&mutex, 0, 1); // Binary semaphore for mutex

    // Create threads
    pthread_t p, c;
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}


void* producer(void* arg) {
    sem_wait(&empty); // Wait for an empty slot
    sem_wait(&mutex); // Acquire mutex
    for (int i = 0; i < loops; i++) {
        put(i); // Produce an item
        printf("Produced: %d\n", i);
    }
    sem_post(&mutex); // Release mutex
    sem_post(&full); // Signal that a new item is available
    return NULL;
}

void* consumer(void* arg) {
    sem_wait(&full); // Wait for a full slot
    sem_wait(&mutex); // Acquire mutex
    for (int i = 0; i < loops; i++) {
        int tmp = get(); // Consume an item
        printf("Consumed: %d\n", tmp);
    }
    sem_post(&mutex); // Release mutex
    sem_post(&empty); // Signal that a slot is now empty
    return NULL;
}