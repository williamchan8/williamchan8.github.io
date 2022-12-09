#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int n;
int t;
int* P;

void* eliminateMultiples(void* param) {
	int factor = *((int *) param);
	for (int i = 2 * factor; i < n; i += factor) {
		P[i] = 0;
	}
	free(param);
}

int main() {
	// Initialize n, t, P, and thread attributes
	printf("Value of n: ");
	scanf("%d", &n);

	P = malloc(n * sizeof(*P));
	for (int i = 0; i < n; i++) {
		P[i] = 1;
	}

	printf("Number of threads: ");
	scanf("%d", &t);
	
	pthread_t tid[t];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// Loop through n, join thread in tid[] if one was previously created
	for (int i = 0; i < (n / 2); i++) {
		// memory allocated in this loop will be freed in thread
		int* factor = (int*)malloc(sizeof(int));
		*factor = i + 2;
		if (i >= t) {
			pthread_join(tid[i % t], NULL);
		}
		pthread_create(&(tid[i % t]), &attr, eliminateMultiples, (void*)(factor));
	}

	// Join remaining threads, print primes, and clean up
	for (int i = 0; i < t && i < n; i++) {
		pthread_join(tid[i], NULL);
	}

	for (int i = 2; i < n; i++) {
		if (P[i]) {
			printf("%d\n", i);
		}
	}

	free(P);

	return 0;
}