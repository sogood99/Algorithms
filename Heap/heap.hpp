#ifndef HEAP_HPP
#define HEAP_HPP

#define MAX_HEAPSIZE 10000

// Implimentation of maxheap

template <typename T>
class MaxHeap{
public:
    MaxHeap(){}
    T top(); //also max
    void insert(T value);
    void removeTop();
    bool empty();
protected:
    T* m_heap = new T[MAX_HEAPSIZE];
    int m_size = 1;
};

template <typename T>
T MaxHeap<T>::top(){
    if (m_size > 1){
        return m_heap[1];
    }
    return T();
}

// NOT FINISHED

template <typename T>
void MaxHeap<T>::insert(T value){
    int currentIndex = m_size;
    if (m_size >= MAX_HEAPSIZE){
        return;
    }else{
        m_heap[m_size++] = value;
    }
    T tempVal;
    for (;currentIndex >= 2; currentIndex /= 2){
        if (m_heap[currentIndex/2] > m_heap[currentIndex]){
            tempVal = m_heap[currentIndex/2];
            m_heap[currentIndex/2] = m_heap[currentIndex];
            m_heap[currentIndex] = tempVal;
        }else{
            break;
        }
    }
}

template <typename T>
void MaxHeap<T>::removeTop(){
    if (m_size <= 1){
        return;
    }
    m_heap[1] = m_heap[--m_size];
    int currentIndex = 1;
    while(currentIndex*2 < m_size){
        T tempval;
        if (m_heap[currentIndex] < m_heap[currentIndex*2] || m_heap[currentIndex] < m_heap[currentIndex*2+1]){
            if (m_heap[currentIndex*2] > m_heap[currentIndex*2+1]){
                tempval = m_heap[currentIndex*2];
                m_heap[currentIndex*2] = m_heap[currentIndex];
                m_heap[currentIndex] = tempval;
            }else{
                tempval = m_heap[currentIndex*2+1];
                m_heap[currentIndex*2+1] = m_heap[currentIndex];
                m_heap[currentIndex] = tempval;
            }
        }else{
            return;
        }
        currentIndex*=2;
    }
}

template <typename T>
bool MaxHeap<T>::empty(){
    return m_size == 1;
}

// Implimentation of minheap

#endif // HEAP_HPP
