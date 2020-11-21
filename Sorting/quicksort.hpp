#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

template <typename T>
int Partition(T arr[], int p, int r){
    T pivot = arr[r];
    int i = p-1;
    T temp;
    for (int j = p; j < r; j++){
        if (arr[j] <= arr[r]){
            temp = arr[i+1];
            arr[i+1] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    temp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = temp;
    return i+1;
}

template <typename T>
void quicksort(T arr[], int p, int r){
    // r = size-1 = index of last element
    if (p < r){
        int q = Partition(arr, p, r);
        quicksort(arr, p, q-1);
        quicksort(arr, q+1, r);
    }
}

#endif // QUICKSORT_HPP
