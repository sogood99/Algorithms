#ifndef BINARYSEARCTREE_HPP
#define BINARYSEARCTREE_HPP

namespace BinarySearchTree{
template<typename T>
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
    void insert(T data);
    bool find(T data, void (*vFunctionCall)(node* arg));
    bool remove(T data);

public:
    T getData(void);
    node<T>* getLeftChild(void);
    node<T>* getRightChild(void);

    void inorderTraversal(void (*vFunctionCall)(node* arg));
    void preorderTraversal(void (*vFunctionCall)(node* arg));
    void postorderTraversal(void (*vFunctionCall)(node* arg));

protected:
    void createLeftNode(T data = T());
    void createRightNode(T data = T());

    void setValue(T data);
    void setLeftChild(node* leftChild);
    void setRightChild(node* rightChild);
};
}

template<typename T>
BinarySearchTree::node<T>::~node(){
    if (m_LeftChild != nullptr){
        delete m_LeftChild;
    }
    if (m_RightChild != nullptr){
        delete m_RightChild;
    }
}

template <typename T>
void BinarySearchTree::node<T>::insert(T data){
    if (data <= m_Data){
        if (m_LeftChild != nullptr){
            m_LeftChild->insert(data);
        }else{
            createLeftNode(data);
        }
    }else{
        if (m_RightChild != nullptr){
            m_RightChild->insert(data);
        }else{
            createRightNode(data);
        }
    }
}

template <typename T>
bool BinarySearchTree::node<T>::find(T data, void (*vFunctionCall)(node* arg)){
    if (data == m_Data){
        vFunctionCall(this);
        return true;
    }else if (data < m_Data){
        return m_LeftChild->find(data);
    }else{
        return m_RightChild->find(data);
    }
}

template <typename T>
bool BinarySearchTree::node<T>::remove(T data){
    if (data == m_Data){
        delete this;
        return true;
    }else if (m_LeftChild->getData() == data){
        delete m_LeftChild;
        m_LeftChild = nullptr;
        return true;
    }else if (data < m_Data){
        return m_LeftChild->remove(data);
    }else if (m_RightChild->getData() == data){
        delete m_RightChild;
        m_RightChild = nullptr;
        return true;
    }else{
        return m_RightChild->remove(data);
    }
}

template<typename T>
void BinarySearchTree::node<T>::createLeftNode(T data){
    if (m_LeftChild == nullptr){
        m_LeftChild = new BinarySearchTree::node<T>(data);
    }
}

template<typename T>
void BinarySearchTree::node<T>::createRightNode(T data){
    if (m_RightChild == nullptr){
        m_RightChild = new BinarySearchTree::node<T>(data);
    }
}

template<typename T>
void BinarySearchTree::node<T>::setValue(T data){
    m_Data = data;
}

template<typename T>
void BinarySearchTree::node<T>::setLeftChild(BinarySearchTree::node<T> *leftChild){
    m_LeftChild = leftChild;
}

template<typename T>
void BinarySearchTree::node<T>::setRightChild(BinarySearchTree::node<T> *rightChild){
    m_RightChild = rightChild;
}

template<typename T>
T BinarySearchTree::node<T>::getData(void){
    return m_Data;
}

template<typename T>
BinarySearchTree::node<T>* BinarySearchTree::node<T>::getLeftChild(void){
    return m_LeftChild;
}

template<typename T>
BinarySearchTree::node<T>* BinarySearchTree::node<T>::getRightChild(void){
    return m_RightChild;
}

template<typename T>
void BinarySearchTree::node<T>::inorderTraversal(void (*vFunctionCall)(node*)){
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    vFunctionCall(this);
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
}

template<typename T>
void BinarySearchTree::node<T>::preorderTraversal(void (*vFunctionCall)(node*)){
    vFunctionCall(this);
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
}

template<typename T>
void BinarySearchTree::node<T>::postorderTraversal(void (*vFunctionCall)(node*)){
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
    vFunctionCall(this);
}

#endif // BINARYSEARCTREE_HPP
