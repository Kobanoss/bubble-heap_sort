#include <stdio.h>

void heapify(int *arr, int root_id) {
    int is_completed = 0;
    int heap_bottom = arr[0];

    while (!(is_completed)) {

        int left = 2 * root_id, right = left + 1, swap_index = root_id;

        if (left <= heap_bottom && arr[left] > arr[swap_index])
            swap_index = left;
        if (right <= heap_bottom && arr[right] > arr[swap_index])
            swap_index = right;
        if (swap_index == root_id)
            is_completed = 1;
        else {
            swap(&arr[root_id], &arr[swap_index]);
            root_id = swap_index;
        }
    }
}

void HeapSort(int *arr) {
    int size = arr[0];
    for (int i = size / 2; i >= 1; i--)
        heapify(arr, i);

    while (arr[0] > 1) {
        swap(&arr[1], &arr[arr[0]]);
        arr[0]--;
        heapify(arr, 1);
    }
}