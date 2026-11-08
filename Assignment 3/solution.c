// gcc -g -Wall -o binary_search binary_search.c -lpthread
// ./binary_search
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[] = {1, 5, 8, 12, 17, 23,
             28, 34, 66, 86, 100, 112,
             124, 160, 200, 300, 312}; // Sample sorted array
int size = sizeof(arr) / sizeof(arr[0]);
int key;

struct search_args {
    int low;
    int high;
};

void *binary_search_thread(void *arg) {
    struct search_args *args = (struct search_args *)arg;
    int mid;

    while (args->low <= args->high) {
        mid = args->low + (args->high - args->low) / 2;

        if (arr[mid] == key) {
            int *found_index = malloc(sizeof(int));
            *found_index = mid;
            return found_index;
        } else if (arr[mid] < key) {
            args->low = mid + 1;
        } else {
            args->high = mid - 1;
        }
    }

    return NULL; // Element not found
}

int main() {
    printf("Enter the element to search: ");
    scanf("%d", &key);

    // Number of threads
    int num_threads = 4;

    pthread_t threads[num_threads];
    struct search_args args[num_threads];

    // Divide the search space equally among threads
    int chunk = size / num_threads;
    for (int i = 0; i < num_threads; i++) {
        args[i].low = i * chunk;
        if (i == num_threads - 1) {
            args[i].high = size - 1;
        } else {
            args[i].high = (i + 1) * chunk - 1;
        }
        if (pthread_create(&threads[i], NULL, binary_search_thread, &args[i]) != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

     // Wait for all threads to finish and check for found index and print it,
    // and if the element not found print element not found
    int found = 0;
    int found_index = -1;
    for (int i = 0; i < num_threads; i++) {
        void *result;
        if (pthread_join(threads[i], &result) != 0) {
            perror("Failed to join thread");
            return EXIT_FAILURE;
        }
        if (result != NULL && !found) {
            found = 1;
            found_index = *(int *)result;
            free(result);
        }
    }

    if (found) {
        printf("Element %d found at index %d.\n", key, found_index);
    } else {
        printf("Element %d not found in the array.\n", key);
    }

    return 0;
}
