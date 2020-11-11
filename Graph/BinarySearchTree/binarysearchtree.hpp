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
    node<T>* m_LeftChild = nullptr;
    node<T>* m_RightChild = nullptr;
    node<T>* m_Parent = nullptr;

public:
    void insert(T data);
    bool find(T data, void (*vFunctionCall)(node* arg));
    node<T>* remove(T data);

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
node<T>* BinarySearchTree::node<T>::remove(T data){
    if (data == m_Data){
        node<T>* temp;
        if (m_LeftChild == nullptr){
            if (m_Parent->m_LeftChild == this){
                m_Parent->m_LeftChild = m_RightChild;
            }else{
                m_Parent->m_RightChild = m_RightChild;
            }
            if (m_RightChild != nullptr){
                m_RightChild->m_Parent = m_Parent;
            }
            temp = m_RightChild;

            m_LeftChild = nullptr;
            m_RightChild = nullptr;
            delete this;
            return temp;
        }else if (m_RightChild == nullptr){
            if (m_Parent->m_LeftChild == this){
                m_Parent->m_LeftChild = m_LeftChild;
            }else{
                m_Parent->m_RightChild = m_LeftChild;
            }
            if (m_LeftChild != nullptr){
                m_LeftChild->m_Parent = m_Parent;
            }
            temp = m_LeftChild;
            m_LeftChild = nullptr;
            delete this;
            return temp;
        }else if (m_RightChild->m_LeftChild == nullptr){
            if (m_Parent->m_LeftChild == this){
                m_Parent->m_LeftChild = m_RightChild;
            }else{
                m_Parent->m_RightChild = m_RightChild;
            }
            m_RightChild->m_Parent = m_Parent;
            m_RightChild->m_LeftChild = m_LeftChild;
            m_LeftChild->m_Parent = m_RightChild;
            temp = m_RightChild;

            m_LeftChild = nullptr;
            m_RightChild = nullptr;
            delete this;
            return temp;
        }else{
            node<T>* n = m_RightChild;
            while (n->m_LeftChild != nullptr){
                n = n->m_LeftChild;
            }
            n->m_Parent->m_LeftChild = n->m_RightChild;
            if (n->m_RightChild != nullptr){
                n->m_RightChild->m_Parent = n->m_Parent;
            }
            m_LeftChild->m_Parent = n;
            m_RightChild->m_Parent = n;
            n->m_LeftChild = m_LeftChild;
            n->m_RightChild = m_RightChild;
            n->m_Parent = m_Parent;
            if (m_Parent != nullptr){
                if (m_Parent->m_LeftChild == this){
                    m_Parent->m_LeftChild = n;
                }else{
                    m_Parent->m_RightChild = n;
                }
            }
            m_LeftChild = nullptr;
            m_RightChild = nullptr;
            delete this;
            return n;
        }
    }else if (data < m_Data && m_LeftChild != nullptr){
        return m_LeftChild->remove(data);
    }else if (m_RightChild != nullptr){
        return m_RightChild->remove(data);
    }
}

template<typename T>
void node<T>::createLeftNode(T data){
    if (m_LeftChild == nullptr){
        setLeftChild(new BinarySearchTree::node<T>(data));
    }
}

template<typename T>
void node<T>::createRightNode(T data){
    if (m_RightChild == nullptr){
        setRightChild(new BinarySearchTree::node<T>(data));
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
void node<T>::setParent(node<T> *parent){
    m_Parent = parent;
}


template<typename T>
T node<T>::getData(void){
    return m_Data;
}

template<typename T>
node<T>* node<T>::getLeftChild(void){
    return m_LeftChild;
}

template<typename T>
node<T>* node<T>::getRightChild(void){
    return m_RightChild;
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

#endif // BINARYSEARCTREE_HPP
