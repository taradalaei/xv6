#include "../kernel/types.h"
#include "../kernel/param.h"
#include "../kernel/memlayout.h"
#include "../kernel/riscv.h"
#include "../kernel/spinlock.h"
#include "../kernel/proc.h"
#include "../user/user.h"
#define STACK_SIZE 100

// Simple mutex using atomic operations
volatile int print_lock = 0;

void acquire_print_lock() {
    while (__sync_lock_test_and_set(&print_lock, 1)) {
        // Busy wait (spin)
    }
}

void release_print_lock() {
    __sync_lock_release(&print_lock);
}

struct thread_data {
    int thread_id;
    uint64 start_number;
};

void *my_thread(void *arg) {
    
    for (int i = 0; i < 10; ++i) {
        ((struct thread_data *) arg)->start_number++;
        
        // Acquire lock before printing
        acquire_print_lock();
        printf("thread %d: %lu\n", ((struct thread_data *) arg)->thread_id, ((struct thread_data *) arg)->start_number);
        release_print_lock();
        // Release lock after printing
        
        // Try to yield by calling a system call that trigger scheduling
        sleep(1);  // Sleep for 1 tick - this should trigger thread scheduling
    }
    return (void *) ((struct thread_data *) arg)->start_number;
}


int main(int argc, char *argv[]) {
    int sp1[STACK_SIZE], sp2[STACK_SIZE], sp3[STACK_SIZE];
    
    // Create thread data structures (static to ensure they persist)
    static struct thread_data data1 = {1, 100};
    static struct thread_data data2 = {2, 200};
    static struct thread_data data3 = {3, 300};
    
    int ta = thread(my_thread, sp1 + STACK_SIZE, (void *) &data1);
    acquire_print_lock();
    printf("NEW THREAD CREATED 1\n");
    release_print_lock();
    
    int tb = thread(my_thread, sp2 + STACK_SIZE, (void *) &data2);
    acquire_print_lock();
    printf("NEW THREAD CREATED 2\n");
    release_print_lock();
    
    int tc = thread(my_thread, sp3 + STACK_SIZE, (void *) &data3);
    acquire_print_lock();
    printf("NEW THREAD CREATED 3\n");
    release_print_lock();
    
    jointhread(ta);
    jointhread(tb);
    jointhread(tc);
    
    acquire_print_lock();
    printf("DONE\n");
    release_print_lock();
}