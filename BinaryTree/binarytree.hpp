#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

namespace BinaryTree {
template <typename T>
class node{
public:
    node(T data = T(), node* leftChild = nullptr, node* rightChild = nullptr): m_Data(data),
        m_LeftChild(leftChild), m_RightChild(rightChild){}
    ~node();
protected:
    T m_Data;
    node* m_LeftChild = nullptr;
    node* m_RightChild = nullptr;
public:
    void createLeftNode(T data = T());
    void createRightNode(T data = T());
    void setValue(T data);
    void setLeftChild(node* leftChild);
    void setRightChild(node* rightChild);

    node<T>* getLeftChild(void);
    node<T>* getRightChild(void);

    void inorderTraversal(void (*vFunctionCall)(T arg));
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
void BinaryTree::node<T>::createLeftNode(T data){
    if (m_LeftChild == nullptr){
        m_LeftChild = new BinaryTree::node<T>(data);
    }
}

template<typename T>
void BinaryTree::node<T>::createRightNode(T data){
    if (m_RightChild == nullptr){
        m_RightChild = new BinaryTree::node<T>(data);
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

template<typename T>
void BinaryTree::node<T>::inorderTraversal(void (*vFunctionCall)(T)){
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    vFunctionCall(m_Data);
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
}

#endif // BINARYTREE_HPP
