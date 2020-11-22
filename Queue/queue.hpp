#ifndef QUEUE_HPP
#define QUEUE_HPP
#define MAX_QUEUESIZE 10000

template <typename T>
class queue{
public:
    queue(){}
    queue(queue& other){
        *this = other;
    }
public:
    bool enque(T item);
    T dequeue();
    bool empty();
protected:
    T m_Queue[MAX_QUEUESIZE + 1];
    int m_Head = 0;
    int m_Tail = 0;
};

template <typename T>
bool queue<T>::enque(T item){
    if ((m_Tail + 1)%(MAX_QUEUESIZE+1) == m_Head){
        return false;
    }
    m_Queue[m_Tail] = item;
    m_Tail++;
    m_Tail %= (MAX_QUEUESIZE+1);
    return true;
}

template <typename T>
T queue<T>::dequeue(){
    int last = m_Head;
    if (m_Head == m_Tail){
        return T();
    }
    m_Head ++;
    m_Head %= (MAX_QUEUESIZE+1);
    return m_Queue[last];
}

template <typename T>
bool queue<T>::empty(){
    return m_Head == m_Tail;
}

#endif // QUEUE_HPP
