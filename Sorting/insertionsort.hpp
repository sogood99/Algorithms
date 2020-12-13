#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP


template <typename T>
void insertionSort(T* arr, int size){
    if (size <= 1){
        return;
    }
    int i, j, key;
    for (i = 1; i < size; i++){
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

#endif // INSERTIONSORT_HPP
