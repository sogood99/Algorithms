#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

namespace LinkedList {

template <typename T>
class node{
public:
    node(T data = T(), node* next = nullptr): m_Data(data), m_Next(next){}
    ~node(){
        if (m_Next != nullptr){
            delete m_Next;
        }
    }
public:
    void setValue(T value);
    T getValue();
    void setNext(node<T>* next);
    node<T>* getNext();
    void insert(node<T>* n);
    void insert(T data);
    node<T>* remove(node<T>* n);
    node<T>* remove(T data);
protected:
    T m_Data = T();
    node* m_Next = nullptr;
};

template <typename T>
void node<T>::setValue(T value){
    m_Data = value;
}

template <typename T>
T node<T>::getValue(){
    return m_Data;
}

template <typename T>
void node<T>::setNext(node<T>* next){
    m_Next = next;
}

template <typename T>
node<T>* node<T>::getNext(){
    return m_Next;
}

template <typename T>
void node<T>::insert(node<T>* n){
    if (m_Next == nullptr){
        m_Next = n;
    }else{
        m_Next->insert(n);
    }
}

template <typename T>
void node<T>::insert(T data){
    node<T>* n = new node<T>(data);
    insert(n);
}

template <typename T>
node<T>* node<T>::remove(node<T>* n){
    if (n == this){
        node<T>* temp = m_Next;
        m_Next = nullptr;
        delete this;
        return temp;
    }else if (m_Next != nullptr){
        if (m_Next == n){
            node<T>* temp = m_Next;
            m_Next = m_Next->getNext();
            temp->remove(n);
            return this;
        }
        m_Next->remove(n);
    }
    return this;
}

template <typename T>
node<T>* node<T>::remove(T data){
    if (m_Data == data){
        node<T>* temp = m_Next;
        m_Next = nullptr;
        delete this;
        return temp;
    }else if (m_Next != nullptr){
        if (m_Next->getValue() == data){
            node<T>* temp = m_Next;
            m_Next = m_Next->getNext();
            temp->remove(data);
            return this;
        }
        m_Next->remove(data);
    }
    return this;
}

}

#endif // LINKEDLIST_HPP

#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph{

template <typename T>
class edge;

template <typename T>
class node{
public:
    node(T data);
public:
    T data;
    int m_Deg = 0;
    LinkedList::node<edge<T>*> edges = nullptr;
public:
    void addEdge(edge<T>* edge);
    void addEdge(node<T>* from, node<T>* to);
};

template <typename T>
class edge{
public:
    edge(node<T>* from, node<T>* to, int weight = 1): m_From(from), m_To(to), m_Weight(weight){};
public:
    int m_Weight = 1;
    node<T>* m_From = nullptr;
    node<T>* m_To = nullptr;
};

}

#endif // GRAPH_HPP
