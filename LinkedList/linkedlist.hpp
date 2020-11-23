#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

namespace LinkList {

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
    node<T>* find(T data);
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
    node<T>* nd = this;
    while(nd->getNext() != nullptr)
        nd = nd->getNext();
    nd->setNext(n);
}

template <typename T>
void node<T>::insert(T data){
    node<T>* n = new node<T>(data);
    node<T>* nd = this;
    while(nd->getNext() != nullptr)
        nd = nd->getNext();
    nd->setNext(n);
}

template <typename T>
node<T>* node<T>::remove(node<T>* n){
    if (this == n){
        node<T>* temp = m_Next;
        m_Next = nullptr;
        delete this;
        return temp;
    }
    node<T>* nd = this;
    while (nd->getNext() != nullptr){
        if (nd->getNext() == n){
            node<T>* temp = nd->getNext();
            nd->setNext(nd->getNext()->getNext());
            temp->setNext(nullptr);
            delete temp;
            return this;
        }
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
    }
    node<T>* nd = this;
    while (nd->getNext() != nullptr){
        if (nd->getNext()->getValue() == data){
            node<T>* temp = nd->getNext();
            nd->setNext(nd->getNext()->getNext());
            temp->setNext(nullptr);
            delete temp;
            return this;
        }
    }
    return this;
}

template <typename T>
node<T>* node<T>::find(T data){
    node<T>* nd = this;
    while (nd != nullptr){
        if (nd->getValue() == data){
            return nd;
        }
        nd = nd->getNext();
    }
    return nullptr;
}

}

template <typename T>
class LinkedList{
public:
    LinkedList(LinkList::node<T>* n = nullptr): m_Root(n){}
    ~LinkedList(){
        if (m_Root != nullptr){
            delete m_Root;
        }
    }
    void insert(T data);
    void remove(T data);
    LinkList::node<T>* find(T data);
protected:
    LinkList::node<T>* m_Root = nullptr;
};


template <typename T>
void LinkedList<T>::insert(T data){
    if (m_Root == nullptr){
        m_Root = new LinkList::node<T>(data);
    }else{
        m_Root->insert(data);
    }
}

template <typename T>
void LinkedList<T>::remove(T data){
    if (m_Root == nullptr){
        return;
    }else{
        m_Root = m_Root->remove(data);
    }
}

template <typename T>
LinkList::node<T>* LinkedList<T>::find(T data){
    return m_Root->find(data);
}

#endif // LINKEDLIST_HPP
