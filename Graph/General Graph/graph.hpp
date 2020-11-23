#ifndef GRAPH_HPP
#define GRAPH_HPP

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

//Directed Graph

namespace graph{

template <typename T>
class edge;

template <typename T>
class node{
public:
    node(T data = T()): m_Data(data){}
public:
    void addEdge(edge<T> edge);
    void addEdge(node<T>* to);
    void removeEdge(edge<T> edge);
    void removeEdge(node<T>* to, int weight = 1);
    int deg();
protected:
    T m_Data = T();
    int m_Deg = 0;
    LinkedList<edge<T>> m_EdgeList;
};

template <typename T>
void node<T>::addEdge(edge<T> edge){
    if (edge.m_From == this){
        m_EdgeList.insert(edge);
        m_Deg++;
    }
}

template <typename T>
void node<T>::addEdge(node<T>* to){
    edge<T>* e = new edge<T>(this, to);
    m_EdgeList.insert(e);
    m_Deg++;
}

template <typename T>
void node<T>::removeEdge(edge<T> edge){
    if (m_EdgeList.find(edge)){
        m_EdgeList.remove(edge);
        m_Deg--;
    }
}

template <typename T>
void node<T>::removeEdge(node<T>* to, int weight){
    edge<T> ex(this, to, weight);
    auto lln = m_EdgeList.find(ex);
    if (lln != nullptr){
        m_EdgeList.remove(ex);
        m_Deg--;
    }
}

template <typename T>
int node<T>::deg(){
    return m_Deg;
}

template <typename T>
class edge{
public:
    edge(node<T>* from, node<T>* to, int weight = 1): m_From(from), m_To(to), m_Weight(weight){};
public:
    int m_Weight = 1;
    node<T>* m_From = nullptr;
    node<T>* m_To = nullptr;
    bool operator==(const edge<T>& other);
};

template <typename T>
bool edge<T>::operator==(const edge<T>& other){
    if (m_Weight == other.m_Weight && m_From == other.m_From && m_From == other.m_From){
        return true;
    }
    return false;
}

}

#endif // GRAPH_HPP
