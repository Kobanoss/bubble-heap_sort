# Задание: Реализация алгоритмов сортировки пузырьком и пирамидальной сортировки.


## Алгоритм пузырьковой сортировки:

``` C
void BubbleSort(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        bool flag = True;
        for (int j = 0; j < size - (i + 1); j++) {
            if (arr[j] > arr[j + 1]) {
                flag = False;
                swap(&arr[j], &arr[j + 1]);
            }
        }
        if (flag == True) break;
    }
}
```

![Alt-текст](https://github.com/Kobanoss/FLaTA/blob/master/bubble-heap_sort/term.png)
![Alt-текст](https://github.com/Kobanoss/FLaTA/blob/master/bubble-heap_sort/bubble.png)
![Alt-текст](https://github.com/Kobanoss/FLaTA/blob/master/bubble-heap_sort/heap.png)
