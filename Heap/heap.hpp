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

#include <iostream>

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
    for (int i = 1; i < m_size; i++){
        std::cout << m_heap[i];
    }
    std::cout<<std::endl;
}

// Implimentation of minheap

#endif // HEAP_HPP
