/* lets make a linked list that gaurantees when we call a lock, we queue up, and when we call an unlock, we 

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//



typedef struct node {
    struct node *next;
    sem_t sem; 
} node_t;

typedef struct __ns_mutex_t {
    sem_t queue_lock;
    node_t *head;
    node_t *tail; 

} ns_mutex_t;

void mutex_init(ns_mutex_t *m)
{
    sem_init(&m->queue_lock, 0, 1);
    m->head = m->tail = NULL;

}

void ns_mutex_acquire(ns_mutex_t *m, node_t *me)
{
    //to acquire a lock, we first need to make a mutex and then lock the queue

    node_t *add{};

    sem_init(&add->sem, 0, 0); //locked

    sem_wait(&m->queue_lock);


    if(m->tail == nullptr){
        //nothing else queued
        m->tail->next = me;
        sem_post(&m->queue_lock);

    }
    else{

        m->tail->next = me; 
        m->tail = me;
        sem_post(&m->queue_lock);
        sem_wait(&me->sem); //wait until that thread is waken
        //when this returns we hold the lock
    }
}

void ns_mutex_release(ns_mutex_t *m) {
    sem_wait(&m->queue_lock); // 1) enter queue‐critical section

    node_t *h = m->head;
    if (h->next == NULL)
    { // 2a) no one is waiting
        m->head = m->tail = NULL;
        sem_post(&m->queue_lock); // leave, and lock is now free
    }
    else
    {                             // 2b) there is at least one waiter
        m->head = h->next;        // dequeue the next waiter
        sem_post(&m->queue_lock); // leave queue‐critical section

        sem_post(&m->head->sem); // wake exactly that thread
    }
}


void *worker(void *arg) {
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    printf("parent: end\n");
    return 0;
}
