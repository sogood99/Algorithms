#ifndef STACK_HPP
#define STACK_HPP

#define MAX_STACK_SIZE 10000

template <typename T>
class stack{
public:
    stack(){}
protected:
    T m_Stack[MAX_STACK_SIZE];
    int m_Size = 0;
public:
    T top();
    T pop();
    bool push(T item);
    bool empty();
};

template<typename T>
T stack<T>::top(){
    // Returns top if there exists, otherwise returns default constructor
    return m_Size > 0? m_Stack[m_Size-1] : T();
}

template<typename T>
T stack<T>::pop(){
    // Returns popped element if there exists, otherwise returns default constructor
    return m_Size > 0? m_Stack[--m_Size] : T();
}

template<typename T>
bool stack<T>::push(T item){
    // Returns true if size < maxsize
    if (m_Size >= MAX_STACK_SIZE){
        return false;
    }
    m_Stack[m_Size++] = item;
    return true;
}

template<typename T>
bool stack<T>::empty(){
    // Returns true if size < maxsize
    return m_Size == 0;
}

#endif // STACK_HPP
