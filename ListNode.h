#ifndef LISTNODE_H
#define LISTNODE_H

using namespace std;

#include <cstdlib>
#include <iostream>

template<typename T>
class ListNode{
        public:
            ListNode(T data);
            virtual ~ListNode();
            T m_data;
            ListNode<T>* m_next; // recursive data sturcture, points to instances of itself
            ListNode<T>* m_prev;
};

template <typename T>
ListNode<T>::ListNode(T data){
    m_data = data;
    m_prev = NULL;
    m_next = NULL;
}

template<typename T>
ListNode<T>::~ListNode(){
    m_next = NULL;
    m_prev = NULL;
}

#endif