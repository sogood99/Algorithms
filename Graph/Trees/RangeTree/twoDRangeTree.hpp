#ifndef TWODRANGETREE_HPP
#define TWODRANGETREE_HPP

template <typename T>
class Pair{
public:
    Pair(T t1 = T(), T t2 = T(), int tmp = 0): m_first(t1), m_second(t2), temp(tmp){}
    ~Pair(){}
public:
    T getX();
    T getY();
    int temp;
public:
    void setX(T x);
    void setY(T y);
    bool operator> (const Pair<T> &other) const{
        return other < *this;
    }
    bool operator<= (const Pair<T> &other) const{
        return (m_first < other.m_first)||(m_first == other.m_first && m_second <= other.m_second);
    }
    bool operator== (const Pair<T> &other) const{
        return m_first == other.m_first && m_second == other.m_second;
    }
    bool operator< (const Pair<T> &other) const{
        return (m_first < other.m_first)||(m_first == other.m_first && m_second < other.m_second);
    }
    bool operator>= (const Pair<T> &other) const{
        return other <= *this;
    }
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
    int i, j;
    T key;
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
    return Pair<int>(2147483647,2147483647);
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
public:
    bool isLeaf(){return m_leftNode == nullptr && m_rightNode == nullptr;}
};

template <typename T>
class yRangeTree{
public:
    yRangeTree(Pair<T> e): m_root(new yNode<T>(e)){}
    yRangeTree(Pair<T> arr[], int size);
public:
    yNode<T>* buildRangeTree(Pair<T> arr[], int size);
    void rangeQuery(Pair<T> p1, Pair<T> p2, void (*vFunctionCall)(yNode<T>* arg));
public:
    yNode<T>* m_root = nullptr;
protected:
    yNode<T>* findSplittingNode(Pair<T> p1, Pair<T> p2);
    void reportSubtree(yNode<T>* n, void (*vFunctionCall)(yNode<T>*));
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
yNode<T>* yRangeTree<T>::findSplittingNode(Pair<T> p1, Pair<T> p2){
    if (m_root == nullptr)
        return nullptr;
    yNode<T>* v = m_root;
    while (!v->isLeaf() && (p2 <= v->m_value || p1 > v->m_value)){
        if (p2 <= v->m_value){
            v = v->m_leftNode;
        }else{
            v = v->m_rightNode;
        }
    }
    return v;
}

template <typename T>
void yRangeTree<T>::reportSubtree(yNode<T>* n, void (*vFunctionCall)(yNode<T>*)){
    if (n->isLeaf()){
        vFunctionCall(n);
        return;
    }
    reportSubtree(n->m_leftNode, vFunctionCall);
    reportSubtree(n->m_rightNode, vFunctionCall);
}

template <typename T>
bool yLessThan(Pair<T> p1, Pair<T> p2){
    return p1.getY() < p2.getY() || (p1.getY() == p2.getY() && p1.getX() < p2.getX());
}

template <typename T>
bool yLessThanEq(Pair<T> p1, Pair<T> p2){
    return p1.getY() < p2.getY() || (p1.getY() == p2.getY() && p1.getX() <= p2.getX());
}

template <typename T>
void yRangeTree<T>::rangeQuery(Pair<T> p1, Pair<T> p2, void (*vFunctionCall)(yNode<T>* arg)){
    yNode<T>* v = findSplittingNode(p1, p2);
    if (v->isLeaf()){
//        if (v->m_value >= p1 && v->m_value <= p2){
        if (yLessThanEq(p1,v->m_value) && yLessThanEq(v->m_value, p2)){
            vFunctionCall(v);
        }
    }else{
        yNode<T>* v_l = v->m_leftNode;
        while (!v_l->isLeaf()){
            if (yLessThan(p1,v_l->m_value)){
                reportSubtree(v_l->m_rightNode, vFunctionCall);
                v_l = v_l->m_leftNode;
            }else{
                v_l = v_l->m_rightNode;
            }
        }
//        if (v_l->m_value >= p1 && v_l->m_value <= p2){
        if (yLessThanEq(p1, v_l->m_value) && yLessThanEq(v_l->m_value,p2)){
            vFunctionCall(v_l);
        }
        yNode<T>* v_r = v->m_rightNode;
        while (!v_r->isLeaf()){
//            if (p2 > v_r->m_value){
            if (yLessThan(v_r->m_value, p2)){
                reportSubtree(v_r->m_leftNode, vFunctionCall);
                v_r = v_r->m_rightNode;
            }else{
                v_r = v_r->m_leftNode;
            }
        }
        if (yLessThanEq(p1, v_r->m_value) && yLessThanEq(v_r->m_value,p2)){
            vFunctionCall(v_r);
        }
    }
}

// above is yRangeTree()

template <typename T>
class xNode{
public:
    xNode(Pair<T> p = Pair<T>(), yRangeTree<T>* ytree = nullptr, xNode<T>* leftNode = nullptr,
          xNode<T>* rightNode = nullptr): m_value(p), m_leftNode(leftNode), m_rightNode(rightNode),
        m_yTree(ytree){}
public:
    Pair<T> m_value = Pair<T>();
    xNode<T>* m_leftNode = nullptr;
    xNode<T>* m_rightNode = nullptr;
    yRangeTree<T>* m_yTree = nullptr;
public:
    bool isLeaf(){return m_leftNode == nullptr && m_rightNode == nullptr;}
};

template <typename T>
class xRangeTree{
public:
    xRangeTree(Pair<T> arr[], int size);
public:
    xNode<T>* buildRangeTree(Pair<T> arr[], int size);// assume array is sorted on y
    xNode<T>* m_root = nullptr;
public:
    void rangeQuery(Pair<T> p1, Pair<T> p2, void (*vFunctionCall)(yNode<T>* arg));
public:
    xNode<T>* findSplittingNode(Pair<T> p1, Pair<T> p2);
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
        return new xNode<T>(arr[0], ytree);
    }
    Pair<T> newArr[size];
    for (int i = 0; i < size; i++){
        newArr[i] = arr[i];
    }
    Pair<T> med = kthSmallest(newArr, 0, size - 1, (size+1)/2);
    int i = 0, j = 0, m = (size - 1)/2;
    int k;
    for (k = 0; k < size; k++){
        if (arr[k] <= med){
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

template <typename T>
xNode<T>* xRangeTree<T>::findSplittingNode(Pair<T> p1, Pair<T> p2){
    if (m_root == nullptr)
        return nullptr;
    xNode<T>* v = m_root;
    while (!v->isLeaf() && (p2 <= v->m_value || p1 > v->m_value)){
        if (p2 <= v->m_value){
            v = v->m_leftNode;
        }else{
            v = v->m_rightNode;
        }
    }
    return v;
}

template <typename T>
void xRangeTree<T>::rangeQuery(Pair<T> p1, Pair<T> p2, void (*vFunctionCall)(yNode<T>* arg)){
    xNode<T>* v = findSplittingNode(p1, p2);
    if (v->isLeaf()){
        if (v->m_value >= p1 && v->m_value <= p2){
            v->m_yTree->rangeQuery(p1, p2, vFunctionCall);
        }
    }else{
        xNode<T>* v_l = v->m_leftNode;
        while (!v_l->isLeaf()){
            if (p1 <= v_l->m_value){
                v_l->m_rightNode->m_yTree->rangeQuery(p1, p2, vFunctionCall);
                v_l = v_l->m_leftNode;
            }else{
                v_l = v_l->m_rightNode;
            }
        }
        if (v_l->m_value >= p1 && v_l->m_value <= p2){
            v_l->m_yTree->rangeQuery(p1, p2, vFunctionCall);
        }
        xNode<T>* v_r = v->m_rightNode;
        while (!v_r->isLeaf()){
            if (p2 > v_r->m_value){
                v_r->m_leftNode->m_yTree->rangeQuery(p1, p2, vFunctionCall);
                v_r = v_r->m_rightNode;
            }else{
                v_r = v_r->m_leftNode;
            }
        }
        if (v_r->m_value >= p1 && v_r->m_value <= p2){
            v_r->m_yTree->rangeQuery(p1, p2, vFunctionCall);
        }
    }
}

#endif // TWODRANGETREE_HPP
