#ifndef KSMALLESTELEMENT_HPP
#define KSMALLESTELEMENT_HPP

template <typename T>
void insSort(T* arr, int size){
    //standard insertion sort
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

template <typename T>
int partition(T arr[], int l, int r, T x);

template <typename T>
T findMedian(T arr[], int n){
    insSort<T>(arr, n);
    return arr[n/2];
}

template <typename T>
T kthSmallest(T arr[], int l, int r, int k){
    if (k > 0 && k <= r - l + 1){
        int n = r-l+1;
        int i;
        T median[(n+4)/5];
        for (i = 0; i < n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n){
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        T medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);

        int pos = partition(arr, l, r, medOfMed);

        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)
            return kthSmallest(arr, l, pos-1, k);

        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
    return -1;
}

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
int partition(T arr[], int l, int r, T x){
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++){
        if (arr[j] <= x){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

#endif // KSMALLESTELEMENT_HPP
