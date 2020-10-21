/*
– Write a program that starts 3 threads and prints:
 • Thread 1:”<“, every 1/10 s
 • Thread 2 : “|”, every 1/5 s
 • Thread 3: “>”, every 1/3 s
 */
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/*void *thread_function(void *arg) {
	int i; 
	for (i = 0; i < 4; i++) {
		printf("Thread says hi!\n");
		sleep(1);
	}
	return NULL;
}
*/


void *thread_function1(void *arg) {
	int i; 
	for (i = 0; i < 4; i++) {
		printf("<");
		sleep(1/10);
	}
	return NULL;
}
void *thread_function2(void *arg) {
	int i; 
	for (i = 0; i < 4; i++) {
		printf("|");
		sleep(1/5);
	}
	return NULL;
}

void *thread_function3(void *arg) {
	int i; 
	for (i = 0; i < 4; i++) {
		printf(">");
		sleep(1/3);
	}
	return NULL;
}

int main(void) {
	pthread_t mythread;

	if (pthread_create(&mythread, NULL, thread_function1, NULL)) {
		printf("error creating thread.");
		abort();
	}
	if (pthread_create(&mythread, NULL, thread_function2, NULL)) {
		printf("error creating thread.");
		abort();
	}
	if (pthread_create(&mythread, NULL, thread_function3, NULL)) {
		printf("error creating thread.");
		abort();
	}

	if (pthread_join(mythread, NULL)) {
		printf("error joining thread.");
		abort();
	}
	
	exit(0);
}
