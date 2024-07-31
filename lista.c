#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *file;

void swap(int *i, int *j) {
    int aux = *i;
    *i = *j;
    *j = aux;
}

void randVecGenerator(int *v, int size) {
    for (int i = 0; i < size; i++)
        v[i] = i;

    for (int i = 0; i < size; i++)
        swap(&v[i], &v[rand() % size]);
}

// Insertion Sort
void insertionSort(int *v, int size) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Heap Sort
void heapify(int *v, int size, int parent) {
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < size && v[left] > v[largest])
        largest = left;
    if (right < size && v[right] > v[largest])
        largest = right;

    if (largest != parent) {
        swap(&v[parent], &v[largest]);
        heapify(v, size, largest);
    }
}

void heapSort(int *v, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(v, size, i);

    for (int i = size - 1; i >= 0; i--) {
        swap(&v[0], &v[i]);
        heapify(v, i, 0);
    }
}

double timeInsertionSort(int *vec, unsigned int size) {
    clock_t begin, end;

    begin = clock();
    insertionSort(vec, size);
    end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

double timeHeapSort(int *vec, unsigned int size) {
    clock_t begin, end;

    begin = clock();
    heapSort(vec, size);
    end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
    // Rewriting the report file if it already exists
    file = fopen("report.txt", "w");

    srand(time(NULL));

    unsigned int vecSize[] = {1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    unsigned int size = sizeof(vecSize) / sizeof(int);

    int *vecISort = NULL;
    int *vecHSort = NULL;
    for (int i = 0; i < size; i++) {
        vecISort = (int *)malloc(vecSize[i] * sizeof(int));
        vecHSort = (int *)malloc(vecSize[i] * sizeof(int));
        printf("Generating a random vector of %i values...", vecSize[i]);
        randVecGenerator(vecISort, vecSize[i]);
        printf(" Done.\n\n");

        for (int j = 0; j < vecSize[i]; j++)
            vecHSort[j] = vecISort[j];

        file = fopen("report.txt", "a");
        fprintf(file, "Time on %i values:\n", vecSize[i]);
        fclose(file);

        // Insertion Sort
        printf("Testing Insertion Sort...");
        file = fopen("report.txt", "a");
        fprintf(file, "Insertion Sort = %.6f seconds\n", timeInsertionSort(vecISort, vecSize[i]));
        fclose(file);
        printf(" Done.\n");

        // Heap Sort
        printf("Testing Heap Sort...");
        file = fopen("report.txt", "a");
        fprintf(file, "Heap Sort = %.6f seconds\n\n", timeHeapSort(vecHSort, vecSize[i]));
        fclose(file);
        printf(" Done.\n\n");

        free(vecISort);
        free(vecHSort);
    }

    return 0;
}
