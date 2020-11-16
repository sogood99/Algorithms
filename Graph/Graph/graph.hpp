#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

template <typename T>
class edge;

template <typename T>
class node{
public:
    node(T data);
public:
    T data;
    int m_Deg = 0;
    edge<T>* edges[];
public:
    void addEdge(edge<T>* edge);
};

template <typename T>
class edge{
public:
    edge(node<T>* from, node<T>* to): m_From(from), m_To(to) {};
public:
    node<T>* m_From = nullptr;
    node<T>* m_To = nullptr;
};

}

#endif // GRAPH_HPP
