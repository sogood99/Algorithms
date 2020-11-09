#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

namespace BinaryTree {
template <typename T>
class node{
public:
    node(T data): m_Data(data){}
    node(T data, node* leftChild, node* rightChild): m_Data(data),
        m_LeftChild(leftChild), m_RightChild(rightChild){}
    ~node();
protected:
    T m_Data;
    node* m_LeftChild = nullptr;
    node* m_RightChild = nullptr;
public:
    void createNode(T data);
    void setValue(T data);
    void setLeftChild(node* leftChild);
    void setRightChild(node* rightChild);
    node<T>* getLeftChild(void);
    node<T>* getRightChild(void);
};
}

template<typename T>
BinaryTree::node<T>::~node(){
    if (m_LeftChild != nullptr){
        delete m_LeftChild;
    }
    if (m_RightChild != nullptr){
        delete m_RightChild;
    }
}

template<typename T>
void BinaryTree::node<T>::createNode(T data){
    if (data <= m_Data){
        if (m_LeftChild != nullptr){
            m_LeftChild = new BinaryTree::node<T>(data);
        }else{
            m_LeftChild->createNode(data);
        }
    }else{
        if (m_RightChild != nullptr){
            m_RightChild = new BinaryTree::node<T>(data);
        }else{
            m_RightChild->createNode(data);
        }
    }
}

template<typename T>
void BinaryTree::node<T>::setValue(T data){
    m_Data = data;
}

template<typename T>
void BinaryTree::node<T>::setLeftChild(BinaryTree::node<T> *leftChild){
    m_LeftChild = leftChild;
}

template<typename T>
void BinaryTree::node<T>::setRightChild(BinaryTree::node<T> *rightChild){
    m_RightChild = rightChild;
}

template<typename T>
BinaryTree::node<T>* BinaryTree::node<T>::getLeftChild(void){
    return m_LeftChild;
}

template<typename T>
BinaryTree::node<T>* BinaryTree::node<T>::getRightChild(void){
    return m_RightChild;
}

#endif // BINARYTREE_HPP
