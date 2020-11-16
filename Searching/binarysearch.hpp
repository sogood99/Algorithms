#ifndef BINARYSEARCH_HPP
#define BINARYSEARCH_HPP

// Asuume array is sorted, return index (>=0) if found, -1 if not found

template <typename T>
int BinarySearch_A(T* array, int size, T goal){
    int l = 0, r = size-1;
    while(l <= r){
        int m = (l+r)>>1;
        if (array[m] == goal){
            return m;
        }else if (array[m] > goal){
            r = m-1;
        }else{
            l = m+1;
        }
    }
    return -1;
}

template <typename T>
int BinarySearch_B(T* array, int size, T goal){
    int k = 0;
    for (int b = size/2; b>=1; b = b>>1){
        while(k+b < size && array[k+b] <= goal){
            k += b;
        }
    }
    if (array[k] == goal){
        return k;
    }
    return -1;
}

#endif // BINARYSEARCH_HPP
