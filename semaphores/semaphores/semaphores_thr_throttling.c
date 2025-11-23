#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct __Zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} Zem_t;

// Initialize the semaphore
void Zem_init(Zem_t* s, int value) {
    s->value = value;
    pthread_cond_init(&s->cond, NULL);
    pthread_mutex_init(&s->lock, NULL);
}

// Semaphore wait operation
void Zem_wait(Zem_t* s) {
    pthread_mutex_lock(&s->lock);
    while (s->value <= 0)
        pthread_cond_wait(&s->cond, &s->lock);
    s->value--;
    pthread_mutex_unlock(&s->lock);
}

// Semaphore post operation
void Zem_post(Zem_t* s) {
    pthread_mutex_lock(&s->lock);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}

void* memory_intensive_operation(void* arg) {
    Zem_t* sem = (Zem_t*)arg;
    Zem_wait(sem);
    printf("Thread entered memory-intensive region\n");
    // Simulate memory-intensive work
    Zem_post(sem);
    printf("Thread exited memory-intensive region\n");
    return NULL;
}

int main() {
    const int MAX_THREADS = 5; // Maximum number of concurrent threads in the region
    Zem_t sem;
    Zem_init(&sem, 3); // Allowing 3 threads to enter the region simultaneously

    pthread_t threads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, memory_intensive_operation, &sem);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}