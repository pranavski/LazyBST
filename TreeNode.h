#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>

template <typename T>
class TreeNode {
    public:
        TreeNode(T data);
        virtual ~TreeNode();
        T getData();
        void setData(T data);
        void setRoot(T data);
        T m_data;
        TreeNode<T>* m_right;
        TreeNode<T>* m_left;
};

template <typename T>
TreeNode<T>::TreeNode(T data){
    m_data = data;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
    //delete m_left
    //delete m_right
}

template <typename T>
T TreeNode<T>::getData(){
    return m_data;
}

template <typename T>
void TreeNode<T>::setData(T data){
    m_data = data;
}

#endif
