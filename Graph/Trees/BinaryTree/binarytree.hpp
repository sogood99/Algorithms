#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

namespace BinaryTree{
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
    node* m_Parent = nullptr;

public:
    T getData(void);
    node<T>* getLeftChild(void);
    node<T>* getRightChild(void);
    node<T>* getParent(void);

    void inorderTraversal(void (*vFunctionCall)(node* arg));
    void preorderTraversal(void (*vFunctionCall)(node* arg));
    void postorderTraversal(void (*vFunctionCall)(node* arg));

protected:
    void createLeftNode(T data = T());
    void createRightNode(T data = T());

    void setValue(T data);
    void setLeftChild(node* leftChild);
    void setRightChild(node* rightChild);
    void setParent(node* parent);
};

template<typename T>
node<T>::~node(){
    if (m_LeftChild != nullptr){
        delete m_LeftChild;
    }
    if (m_RightChild != nullptr){
        delete m_RightChild;
    }
}

template<typename T>
void node<T>::createLeftNode(T data){
    if (m_LeftChild == nullptr){
        setLeftChild(new BinaryTree::node<T>(data));
    }
}

template<typename T>
void node<T>::createRightNode(T data){
    if (m_RightChild == nullptr){
        setRightChild(new BinaryTree::node<T>(data));
    }
}

template<typename T>
void node<T>::setValue(T data){
    m_Data = data;
}

template<typename T>
void node<T>::setLeftChild(node<T> *leftChild){
    m_LeftChild = leftChild;
    leftChild->setParent(this);
}

template<typename T>
void node<T>::setRightChild(node<T> *rightChild){
    m_RightChild = rightChild;
    rightChild->setParent(this);
}

template<typename T>
void node<T>::setParent(node* parent){
    m_Parent = parent;
}

template<typename T>
node<T>* BinaryTree::node<T>::getLeftChild(void){
    return m_LeftChild;
}

template<typename T>
node<T>* node<T>::getRightChild(void){
    return m_RightChild;
}

template<typename T>
T node<T>::getData(void){
    return m_Data;
}

template<typename T>
node<T>* node<T>::getParent(void){
    return m_Parent;
}

template<typename T>
void node<T>::inorderTraversal(void (*vFunctionCall)(node*)){
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    vFunctionCall(this);
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
}

template<typename T>
void node<T>::preorderTraversal(void (*vFunctionCall)(node*)){
    vFunctionCall(this);
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
}

template<typename T>
void node<T>::postorderTraversal(void (*vFunctionCall)(node*)){
    if (m_LeftChild != nullptr){
        m_LeftChild->inorderTraversal(vFunctionCall);
    }
    if (m_RightChild != nullptr){
        m_RightChild->inorderTraversal(vFunctionCall);
    }
    vFunctionCall(this);
}
}

#endif // BINARYTREE_HPP
