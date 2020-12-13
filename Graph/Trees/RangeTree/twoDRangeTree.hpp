#ifndef TWODRANGETREE_HPP
#define TWODRANGETREE_HPP

template <typename T>
class Pair{
public:
    Pair(T t1 = T(), T t2 = T()): m_first(t1), m_second(t2){}
    ~Pair(){}
public:
    T getX();
    T getY();
public:
    void setX(T x);
    void setY(T y);
protected:
    T m_first = T();
    T m_second = T();
};
template <typename T>
T Pair<T>::getX(){
    return m_first;
}
template <typename T>
T Pair<T>::getY(){
    return m_second;
}
template <typename T>
void Pair<T>::setX(T x){
    m_first = x;
}
template <typename T>
void Pair<T>::setY(T y){
    m_second = y;
}

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
int kthSmallest(T arr[], int l, int r, int k){
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
// median finding and pair definition


template <typename T>
class yNode{
public:
    yNode(Pair<T> p = Pair<T>(), yNode<T>* leftNode = nullptr, yNode<T>* rightNode = nullptr):
        m_value(p), m_leftNode(leftNode), m_rightNode(rightNode){}
public:
    Pair<T> m_value = Pair<T>();
    yNode<T>* m_leftNode = nullptr;
    yNode<T>* m_rightNode = nullptr;
};

template <typename T>
class yRangeTree{
public:
    yRangeTree(Pair<T> e): m_root(new yNode<T>(e)){}
    yRangeTree(Pair<T> arr[], int size);
public:
    yNode<T>* buildRangeTree(Pair<T> arr[], int size);
public:
    yNode<T>* m_root = nullptr;
};

template <typename T>
yRangeTree<T>::yRangeTree(Pair<T> arr[], int size){
    m_root = buildRangeTree(arr, size);
}

template <typename T>
yNode<T>* yRangeTree<T>::buildRangeTree(Pair<T> arr[], int size){
    if (size <= 0){
        return nullptr;
    }
    if (size == 1){
        return new yNode<T>(arr[0]);
    }
    int m = (size-1)/2;
    yNode<T>* leftNode = buildRangeTree(arr, m+1);
    yNode<T>* rightNode = buildRangeTree(arr+m+1, size - m - 1);
    return new yNode<T>(arr[m], leftNode, rightNode);
}

template <typename T>
class xNode{
public:
    xNode(T x = T(), yRangeTree<T>* ytree = nullptr, xNode<T>* leftNode = nullptr,
          xNode<T>* rightNode = nullptr): m_xvalue(x), m_leftNode(leftNode), m_rightNode(rightNode),
        m_yTree(ytree){}
public:
    T m_xvalue = T();
    xNode<T>* m_leftNode = nullptr;
    xNode<T>* m_rightNode = nullptr;
    yRangeTree<T>* m_yTree = nullptr;
};

template <typename T>
class xRangeTree{
public:
    xRangeTree(Pair<T> arr[], int size);
public:
    xNode<T>* buildRangeTree(Pair<T> arr[], int size);// assume array is sorted on y
    xNode<T>* m_root = nullptr;
};

template <typename T>
xRangeTree<T>::xRangeTree(Pair<T> arr[], int size){
    m_root = buildRangeTree(arr, size);
}

template <typename T>
xNode<T>* xRangeTree<T>::buildRangeTree(Pair<T> arr[], int size){
    if (size <= 0){
        return nullptr;
    }
    if (size == 1){
        yRangeTree<T>* ytree = new yRangeTree<T>(arr[0]);
        return new xNode<T>(arr[0].getX(), ytree);
    }
    T arrP[size]; Pair<T> newArr[size];
    for (int i = 0; i < size; i++){
        arrP[i] = arr[i].getX();
    }
    T med = kthSmallest(arrP, 0, size - 1, (size+1) >> 1);
    int i = 0, j = 0, m = (size - 1)/2;
    for (int k = 0; k < size; k++){
        if (arr[k].getX() <= med){
            newArr[i] = arr[k];
            i++;
        }else{
            newArr[m+1+j] = arr[k];
            j++;
        }
    }
    xNode<T>* leftNode = buildRangeTree(newArr, m+1);
    xNode<T>* rightNode = buildRangeTree(newArr+m+1, size-m-1);
    yRangeTree<T>* ytree = new yRangeTree<T>(arr, size);
    return new xNode<T>(med, ytree, leftNode, rightNode);
}

#endif // TWODRANGETREE_HPP
