# Задание: Реализация алгоритмов сортировки пузырьком и пирамидальной сортировки.

Программа вызывается из консоли, на выбор дается один из алгоритмов сортировки, кол-во сортируемых элементов и кол-во проходов по таком кол-ву элементов (для повышения точности).
## Пример работы программы: 

![Alt-текст](https://github.com/Kobanoss/bubble-heap_sort/blob/main/term.png)

    Далее строится график с использованием gnuplot



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
## Блок-схема алгоритма :
![Alt-текст](https://github.com/Kobanoss/bubble-heap_sort/blob/main/algo_bubble.png)

Теоретическое значение временной сложности алгоритма: O(n^2)

На графике мы сравниваем полученные значения с теоретическими.
## График сравнения:
![Alt-текст](https://github.com/Kobanoss/bubble-heap_sort/blob/main/bubble.png)



## Алгоритм пирамидальной сортировки (сортировки кучей):

``` C
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
```
## Блок-схема алгоритма :
![Alt-текст](https://github.com/Kobanoss/bubble-heap_sort/blob/main/algo_heap.png)

Теоретическое значение временной сложности алгоритма всегда: O(n(log(n))

На графике мы сравниваем полученные значения с теоретическими.
## График сравнения:
![Alt-текст](https://github.com/Kobanoss/bubble-heap_sort/blob/main/heap.png)

# Итог: 
    Алгоритм пузырьковой сортировки является самым медленным алгоритмом сортировки, 
    не только из представленных, но и из всех доступных алгоритмов в целом.
            
    Даже не смотря на оптимизацию данной сортировки, что позволило сделать ее временную сложность меньше O(n^2), 
    она все еще имеет показатели по временным затратам большие, нежели у остальных сортировок, 
    что делает этот алгоритм сортировки пригодным только для учебных целей.

