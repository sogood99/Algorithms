#ifndef ONEDRANGETREE_HPP
#define ONEDRANGETREE_HPP

template <typename T>
class node{
public:
    node(T value = T(), node* leftNode = nullptr, node* rightNode = nullptr):m_Value(value),
        m_LeftNode(leftNode), m_RightNode(rightNode){}
    ~node(){}
public:
    T m_Value = T();
    node* m_LeftNode = nullptr;
    node* m_RightNode = nullptr;
    bool isLeaf();
};

template <typename T>
bool node<T>::isLeaf(){
    return m_LeftNode == nullptr && m_RightNode == nullptr;
}

template <typename T>
class RangeTree{
public:
    RangeTree(T*, int size); //assume array is sorted
    ~RangeTree(){}
public:
    node<T>* m_Root = nullptr;
    node<T>* buildRangeTree(T* arr, int l, int r);
    void rangeQuery(T x_l, T x_r, void (*vFunctionCall)(node<T>* arg));
protected:
    node<T>* findSplittingNode(T x_l,T x_r);
    void reportSubtree(node<T>* n, void (*vFunctionCall)(node<T>*));
};

template <typename T>
RangeTree<T>::RangeTree(T* arr, int size){
    if (size > 0){
        m_Root = buildRangeTree(arr, 0, size-1);
    }
}

template <typename T>
node<T>* RangeTree<T>::buildRangeTree(T* arr, int l, int r){
    if (l > r){
        return nullptr;
    }
    if (l==r){
        return new node<T>(arr[l]);
    }
    int m = (l+r)>>1;
    T median = arr[m];
    node<T>* leftNode = buildRangeTree(arr, l, m);
    node<T>* rightNode = buildRangeTree(arr, m+1, r);
    node<T>* middleNode = new node<T>(median, leftNode, rightNode);
}

template <typename T>
node<T>* RangeTree<T>::findSplittingNode(T x_l, T x_r){
    if (m_Root == nullptr)
        return nullptr;
    node<T>* v = m_Root;
    while (!v->isLeaf() && (x_r <= v->m_Value || x_l > v->m_Value)){
        if (x_r <= v->m_Value){
            v = v->m_LeftNode;
        }else{
            v = v->m_RightNode;
        }
    }
    return v;
}

template <typename T>
void RangeTree<T>::reportSubtree(node<T>* n, void (*vFunctionCall)(node<T>*)){
    if (n->isLeaf()){
        vFunctionCall(n);
        return;
    }
    reportSubtree(n->m_LeftNode, vFunctionCall);
    reportSubtree(n->m_RightNode, vFunctionCall);
}

template <typename T>
void RangeTree<T>::rangeQuery(T x_l, T x_r, void (*vFunctionCall)(node<T>*)){
    node<T>* v = findSplittingNode(x_l, x_r);
    if (v->isLeaf()){
        if (v->m_Value >= x_l && v->m_Value <= x_r){
            vFunctionCall(v);
        }
    }else{
        node<T>* v_l = v->m_LeftNode;
        while (!v_l->isLeaf()){
            if (x_l <= v_l->m_Value){
                reportSubtree(v_l->m_RightNode, vFunctionCall);
                v_l = v_l->m_LeftNode;
            }else{
                v_l = v_l->m_RightNode;
            }
        }
        if (v_l->m_Value >= x_l && v_l->m_Value <= x_r){
            vFunctionCall(v_l);
        }
        node<T>* v_r = v->m_RightNode;
        while (!v_r->isLeaf()){
            if (x_r > v_r->m_Value){
                reportSubtree(v_r->m_LeftNode, vFunctionCall);
                v_r = v_r->m_RightNode;
            }else{
                v_r = v_r->m_LeftNode;
            }
        }
        if (v_r->m_Value >= x_r && v_r->m_Value <= x_r){
            vFunctionCall(v_r);
        }
    }
}

#endif // ONEDRANGETREE_HPP
