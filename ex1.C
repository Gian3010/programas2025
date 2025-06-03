#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10001;
    }
}

double measureTime(void (*sortFunction)(int[], int), int arr[], int n) {
    clock_t start, end;
    start = clock();
    sortFunction(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    int sizes[] = {10000, 100000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int repetitions = 5;

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));

        double insertionTime = 0, selectionTime = 0, bubbleTime = 0, shellTime = 0;

        for (int j = 0; j < repetitions; j++) {
            fillArray(arr, n);
            insertionTime += measureTime(insertionSort, arr, n);

            fillArray(arr, n);
            selectionTime += measureTime(selectionSort, arr, n);

            fillArray(arr, n);
            bubbleTime += measureTime(bubbleSort, arr, n);

            fillArray(arr, n);
            shellTime += measureTime(shellSort, arr, n);
        }

        insertionTime /= repetitions;
        selectionTime /= repetitions;
        bubbleTime /= repetitions;
        shellTime /= repetitions;

        printf("N = %d\n", n);
        printf("InsertionSort: %.6f seconds\n", insertionTime);
        printf("SelectionSort: %.6f seconds\n", selectionTime);
        printf("BubbleSort: %.6f seconds\n", bubbleTime);
        printf("ShellSort: %.6f seconds\n", shellTime);
        printf("\n");

        free(arr);
    }

    return 0;
}