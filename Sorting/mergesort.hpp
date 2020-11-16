#ifndef MERGESORT_HPP
#define MERGESORT_HPP

template <typename T>
void merge(T* array, int left, int middle, int right){
    if (right == middle || left >= right){
        return;
    }
    T leftTempArray[middle-left+1];
    T rightTempArray[right-middle];

    for (int i = 0; i <= middle - left; i++){
        leftTempArray[i] = array[left + i];
    }
    for (int i = 0; i < right - middle; i++){
        rightTempArray[i] = array[middle + i + 1];
    }

    int i = 0, j = 0;

    while (i < middle-left+1 && j < right-middle){
        if (leftTempArray[i] <= rightTempArray[j]){
            array[left + i + j] = leftTempArray[i];
            i++;
        }else{
            array[left + i + j] = rightTempArray[j];
            j++;
        }
    }

    while (i < middle-left+1){
        array[left+i+j] = leftTempArray[i];
        i++;
    }

    while (j < right-middle){
        array[left+i+j] = rightTempArray[j];
        j++;
    }
}

template <typename T>
void mergeSort(T* array, int left, int right){
    //Assume r = size-1
    if (right - left <= 0){
        return;
    }
    int middle = (left+right)>>1;
    mergeSort(array, left, middle);
    mergeSort(array, middle+1, right);
    merge(array, left, middle, right);
}

#endif // MERGESORT_HPP
