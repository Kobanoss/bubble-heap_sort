#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "bool.h"
#include "swap.h"
#include "bubblesort.h"
#include "heapsort.h"
#include "sorttype.h"
#include "gnuplot.h"


void shuffle(int *array, int n, SortType type) {
    if (n <= 1) return;
    int i;
    if (type == Heap) i = 1;
    else i = 0;
    for (; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        if (j == 0 && type == Heap) continue;
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}


int main() {
    int crit_size, laps, tmp;
    SortType type;
    printf("Select type of sort:\n1.Bubble\n2.Heap\n");
    scanf("%d", &tmp);
    if (tmp == 1) type = Bubble;
    else if (tmp == 2) type = Heap;
    else {
        printf("Wrong sort type select");
        exit(130);
    }

    printf("Print critical array size:\n");
    scanf("%d", &crit_size);
    printf("Print number of laps:\n");
    scanf("%d", &laps);

    char *output;
    if (type == Bubble) output = "bubble_time.txt";
    else output = "heap_time.txt";
    FILE *total_time = fopen(output, "w");
    if (total_time == NULL) {
        exit(EEXIST);
    }


    clock_t start, stop;
    long n = 0;
    char number[10];
    int max;
    char *name = (char *) malloc(20 * sizeof(char));
    while (n != crit_size + 1) {

        int limit = 1000000;
        tmp = n;
        for (int i = 0; i < 9; i++) {
            if (n >= limit) n += limit;
            else if (limit >= 10) limit = limit / 10;
            if (tmp != n) break;
        }
        if (tmp == n) n += 1;
        if (n > crit_size) break;

        if (n < 1000) {
            sprintf(name, "./values/%lu.txt", n);
        } else if (n < 1000000) {
            sprintf(name, "./values/%luK.txt", n / 1000);
        }

        double mean = 0;
        for (int q = 0; q < laps; q++) {
            if (type == Heap) n += 1;
            double *values = (double *) calloc(laps, sizeof(double));
            int *arr = (int *) calloc(n, sizeof(int));

            FILE *block = fopen(name, "r");
            if (block == NULL) {
                exit(ENOENT);
            }

            tmp = 0;
            if (type == Heap) {
                arr[0] = n;
                tmp = 1;
            }
            for (int i = tmp; i < n; i++) {
                fscanf(block, "%[^,],", number);
                arr[i] = atoi(number);
            }

            fclose(block);
            system("sync");
            if (type == Heap) {
                start = clock();
                HeapSort(arr);
                stop = clock();
            } else {
                start = clock();
                BubbleSort(arr, n);
                stop = clock();
            }
            shuffle(arr, n, type);
            values[q] = (1000.0 / CLOCKS_PER_SEC) * (stop - start);

            mean += values[q];

            free(values);
            free(arr);

            if (type == Heap) n -= 1;
        }
        if (mean != 0.000) mean = mean / laps;
        else mean = 0;


        printf("\nThe average time for sorting of %ld elements was: %.3f ms\n", n,
               mean);
        total_time = fopen(output, "a");
        if (total_time == NULL) {
            exit(ENOENT);
        }

        fprintf(total_time, "%ld %f\n", n, mean);
        fclose(total_time);
        max = mean;
    }
    gnuplot(crit_size, max, type);
    return 0;
}