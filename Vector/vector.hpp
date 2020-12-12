#ifndef VECTOR_HPP
#define VECTOR_HPP

// Array with table doubling (O(1) amortized push pos)

template <typename T>
class vector{
public:
    vector(){}
    void push(T element);
    T pop();
    int size();
    int capacity();
    bool empty();
    T& operator[](int index);
protected:
    T* m_vector = new int[1];
    int m_capacity = 1;
    int m_size = 0;
};

template <typename T>
void vector<T>::push(T element){
    if (m_size >= m_capacity){
        m_capacity = m_capacity << 1;
        T* newVector = new int[m_capacity];
        for (int i = 0; i < m_size; i++){
            newVector[i] = m_vector[i];
        }
        delete [] m_vector;
        m_vector = newVector;
    }
    m_vector[m_size++] = element;
}

template <typename T>
T vector<T>::pop(){
    if (m_size <= m_capacity/4 && m_size > 0){
        m_capacity = m_capacity >> 1;
        T* newVector = new int[m_capacity];
        for (int i = 0; i < m_size; i++){
            newVector[i] = m_vector[i];
        }
        delete [] m_vector;
        m_vector = newVector;
    }
    if (m_size > 0){
        return m_vector[m_size--];
    }
    return T();
}

template <typename T>
int vector<T>::size(){
    return m_size;
}

template <typename T>
int vector<T>::capacity(){
    return m_capacity;
}

template <typename T>
bool vector<T>::empty(){
    return m_size == 0;
}

template <typename T>
T& vector<T>::operator[](int index){
    if (index < 0 || index >= m_size){
        throw "Out of bounds!";
    }
    return m_vector[index];
}

#endif // VECTOR_HPP
