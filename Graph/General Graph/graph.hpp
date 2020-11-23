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
