/*
Pranav Surampudi
2407260
surampudi@chapman.edu
CPSC350-03
PA5
*/

#ifndef LAZYBST_H
#define LAZYBST_H

#include "TreeNode.h"
#include "DblList.h"
#include "Faculty.h"
#include "Student.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        int size();
        void insert(T data);
        bool contains(T data);
        void remove(T data);
        void printTreeInOrderStudent();
        void printTreeInOrderFaculty();
        bool printStudentInfo(int data);
        bool printFacultyInfo(int data);
        bool deleteFaculty(int data);
        bool deleteStudent(int data, LazyBST<Faculty>& facultyMembers);
        bool changeStudentAdvisor(int data, int newID, LazyBST<Faculty>& facultyMembers);
        bool removeAdvisee(int data, int newID);
        void addAdvisee(int advisorID, int studetnID);
        TreeNode<T>* findNode(int key);
        bool findNodeFaculty(int key);
        bool findNodeStudentTrue(int key);
        TreeNode<T>* findNodeStudent(int key);
        void printTreePostFix();
        int getLeftDepth();
        int getRightDepth();
        void checkDepths();
        T* storeTreeInOrder();
        void storeTree(TreeNode<T>*, T* arr, int& index);
        void rebalancedTree();
        T* toArray();
        T getRoot();
        void setRoot(T data);
        string createOutputFileStudent();
        string createOutputFileFaculty();
        void finalOutputFile(LazyBST<Faculty>& facultyMembers, LazyBST<Student*>& students);
    private:
        TreeNode<T>* m_root;
        int m_size;
        int m_leftDepth;
        int m_rightDepth;
        bool containsHelper(TreeNode<T>* currNode, T data);
        void insertHelper(TreeNode<T>*& currNode, TreeNode<T>* newNode);
        void printIOHelperStudent(TreeNode<T>* currNode);
        void printIOHelperFaculty(TreeNode<T>* currNode);
        bool printStudentInfoHelper(TreeNode<T>* currNode, int data);
        bool printFacultyInfoHelper(TreeNode<T>* currNode, int data);
        bool deleteFacultyHelper(TreeNode<T>*& currNode, int data);
        bool deleteStudentHelper(TreeNode<T>*& currNode, int data, LazyBST<Faculty>& facultyMembers);
        bool ChangeStudentAdvisorHelper(TreeNode<T>*& currNode, int data, int newID,  LazyBST<Faculty>& facultyMembers);
        bool removeAdviseeHelper(TreeNode<T>*& currNode, int data, int newID);
        void printPostHelper(TreeNode<T>* currNode);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        string createOutputFileHelperStudent(TreeNode<T>* currNode);
        string createOutputFileHelperFaculty(TreeNode<T>* currNode);
        TreeNode<T>* getSuccessor(TreeNode<T>* child);
        int leftDepthHelper(TreeNode<T>* parent);
        int rightDepthHelper(TreeNode<T>* parent);
        TreeNode<T>* rebalanceHelper(T* myArr, int start, int end);
};

template <typename T>
LazyBST<T>::LazyBST(){
    m_root = NULL;
    m_size = 0;
    m_leftDepth = 0;
    m_rightDepth = 0;
}

template <typename T>
LazyBST<T>::~LazyBST(){
    m_root = NULL;
}

template <typename T>
int LazyBST<T>::size(){
    return m_size;
}


template <typename T>
void LazyBST<T>::printTreeInOrderStudent(){
    printIOHelperStudent(m_root);
}

template <typename T>
void LazyBST<T>::printIOHelperFaculty(TreeNode<T>* currNode){
    if(currNode != NULL){
        printIOHelperFaculty(currNode->m_left);
        currNode->getData().printInfo();
        printIOHelperFaculty(currNode -> m_right);
    } else if(m_root == NULL){
        cout << "There are no faculty members in the table!" << endl;
    }
}

template <typename T>
void LazyBST<T>::printTreeInOrderFaculty(){
    printIOHelperFaculty(m_root);
}

template <typename T>
void LazyBST<T>::printIOHelperStudent(TreeNode<T>* currNode){
    if(m_size == 0){
        cout << "There are no students in table!" << endl;
    }else if(currNode != NULL){
        printIOHelperStudent(currNode->m_left);
        currNode->getData()->printInfo();
        printIOHelperStudent(currNode -> m_right);
    }
}

template <typename T>
bool LazyBST<T>::printStudentInfo(int data){
    bool result = printStudentInfoHelper(m_root, data);
    return result;
}

template <typename T>
bool LazyBST<T>::printStudentInfoHelper(TreeNode<T>* currNode, int data){
    bool found = false;
    if(currNode == NULL){
        return false; 
    }
    if(currNode->getData()->getID() > data){
        found = printStudentInfoHelper(currNode->m_left, data);
    }
    else if(currNode->getData()->getID() < data){
        found = printStudentInfoHelper(currNode->m_right, data);
    }
    else{
        currNode->getData()->printInfo();
        found = true;
    }
    return found;
}

template <typename T>
bool LazyBST<T>::printFacultyInfo(int data){
    bool result = printFacultyInfoHelper(m_root, data);
    return result;
}

template <typename T>
bool LazyBST<T>::printFacultyInfoHelper(TreeNode<T>* currNode, int data){
    bool found = false;
    if(m_size == 0){
        cout << "There are no faculty members in the table so no info can be printed" << endl;
    }
    if(currNode == NULL){
        return false;
    }
    if(currNode->getData().getID() > data){
        found = printFacultyInfoHelper(currNode->m_left, data);
    }
    else if(currNode->getData().getID() < data){
        found = printFacultyInfoHelper(currNode->m_right, data);
    }
    else{
        currNode->getData().printInfo();
        found = true;
    }
    return found;
}

template <typename T>
bool LazyBST<T>::deleteFaculty(int data){
    bool result = deleteFacultyHelper(m_root, data);
}

template <typename T>
bool LazyBST<T>::deleteFacultyHelper(TreeNode<T>*& currNode, int data){
    if(currNode == NULL){
        return false;
    }
    if(currNode->getData().getID() > data){
        return deleteFacultyHelper(currNode->m_left, data);
    }
    else if(currNode->getData().getID() < data){
        return deleteFacultyHelper(currNode->m_right, data);
    }
    else {
        if(currNode->getData().getAdvisees()->size() != 0){
            cout << "Reassign student IDs before deleting this faculty member." << endl;
            return false;
        }
        if(currNode->m_left == NULL && currNode->m_right == NULL){
            delete currNode;
            currNode = NULL;
            --m_size;
        }
        else if(currNode->m_left == NULL){
            TreeNode<T>* temp = currNode;
            currNode = currNode->m_right;
            delete temp;
            --m_size;
        }
        else if(currNode->m_right == NULL){
            TreeNode<T>* temp = currNode;
            currNode = currNode->m_left;
            delete temp;
            --m_size;
        }
        else{
            TreeNode<T>* successor = currNode->m_right;
            while (successor->m_left != NULL) {
                successor = successor->m_left;
            }
            currNode->setData(successor->getData());
            return deleteFacultyHelper(currNode->m_right, successor->getData().getID());
        }
        return true;
    }
}

template <typename T>
bool LazyBST<T>::deleteStudent(int data, LazyBST<Faculty>& facultyMembers){
    bool result = deleteStudentHelper(m_root, data, facultyMembers);
    return result;
}

template <typename T>
bool LazyBST<T>::deleteStudentHelper(TreeNode<T>*& currNode, int data, LazyBST<Faculty>& facultyMembers){
    if(currNode == NULL){
        return false; 
    }
    if(currNode->getData()->getID() > data){
        return deleteStudentHelper(currNode->m_left, data, facultyMembers);
    }
    else if(currNode->getData()->getID() < data){
        return deleteStudentHelper(currNode->m_right, data, facultyMembers);
    }
    else {
        if(currNode->m_left == NULL && currNode->m_right == NULL){
            int facultyID = currNode->getData()->getAdvisorID();
            TreeNode<Faculty>* facultyNode = facultyMembers.findNode(facultyID);
            if(facultyNode != NULL){
                DblList<int>* advisees = facultyNode->getData().getAdvisees();
                int index = advisees->indexOf(data);
                if(index != -1){
                    advisees->remove(index);
                }
            }
            delete currNode;
            currNode = NULL;
            --m_size;
        }
        else if(currNode->m_left == NULL) {
            TreeNode<T>* temp = currNode;
            currNode = currNode->m_right;
            delete temp;
            --m_size;
        }
        else if(currNode->m_right == NULL) {
            TreeNode<T>* temp = currNode;
            currNode = currNode->m_left;
            delete temp;
            --m_size;
        }
        else{
            TreeNode<T>* successor = currNode->m_right;
            while (successor->m_left != NULL) {
                successor = successor->m_left;
            }
            currNode->setData(successor->getData());
            return deleteStudentHelper(currNode->m_right, successor->getData()->getID(), facultyMembers);
        }
        return true;
    }
}

//helps find the student node for the deleteStudent method
template <typename T>
TreeNode<T>* LazyBST<T>::findNode(int key){
    TreeNode<T>* currNode = m_root;
    while(currNode != NULL){
        if(currNode->getData().getID() == key){
            return currNode;
        }else if(currNode->getData().getID() > key){
            currNode = currNode->m_left;
        }else{
            currNode = currNode->m_right;
        }
    }
    return NULL;
}

//find node method for adding a student that returns a bool to check if advisor ID exists
template <typename T>
bool LazyBST<T>::findNodeFaculty(int key){
    TreeNode<T>* currNode = m_root;
    while(currNode != NULL){
        if(currNode->getData().getID() == key){
            return true;
        }else if(currNode->getData().getID() > key){
            currNode = currNode->m_left;
        }else{
            currNode = currNode->m_right;
        }
    }
    return false;
}

template <typename T>
bool LazyBST<T>::findNodeStudentTrue(int key){
    TreeNode<T>* currNode = m_root;
    while(currNode != NULL){
        if(currNode->getData()->getID() == key){
            return true;
        }else if(currNode->getData()->getID() > key){
            currNode = currNode->m_left;
        }else{
            currNode = currNode->m_right;
        }
    }
    return false;
}

//method for finding a student node when removing an advisee from a faculty list
template <typename T>
TreeNode<T>* LazyBST<T>::findNodeStudent(int key){
    TreeNode<T>* currNode = m_root;
    while(currNode != NULL){
        if(currNode->getData()->getID() == key){
            return currNode;
        }else if(currNode->getData()->getID() > key){
            currNode = currNode->m_left;
        }else{
            currNode = currNode->m_right;
        }
    }
    return NULL;
}


template <typename T>
bool LazyBST<T>::changeStudentAdvisor(int data, int newID,  LazyBST<Faculty>& facultyMembers){ 
    bool result = ChangeStudentAdvisorHelper(m_root, data, newID, facultyMembers);
    return result;
}

template <typename T>
bool LazyBST<T>::ChangeStudentAdvisorHelper(TreeNode<T>*& currNode, int studentID, int newAdvisorID, LazyBST<Faculty>& facultyMembers){
    bool found = false;
    if(currNode == NULL){
        return false; 
    }
    if(currNode->getData()->getID() > studentID) {
        found = ChangeStudentAdvisorHelper(currNode->m_left, studentID, newAdvisorID, facultyMembers);
    }
    else if(currNode->getData()->getID() < studentID){
        found = ChangeStudentAdvisorHelper(currNode->m_right, studentID, newAdvisorID, facultyMembers);
    }
    else{
        int currentAdvisorID = currNode->getData()->getAdvisorID();
        if(currentAdvisorID == newAdvisorID){
            return false;
        }
        else{
            facultyMembers.removeAdvisee(currentAdvisorID, studentID);
            facultyMembers.addAdvisee(newAdvisorID, studentID);
            currNode->getData()->setAdvisorID(newAdvisorID);
            found = true;
        }
    }
    return found;
}

//method to find a faculty member and add an advisee to their list
template <typename T>
void LazyBST<T>::addAdvisee(int advisorID, int studentID) {
    TreeNode<T>* currNode = m_root;
    while(currNode != NULL) {
        if(currNode->getData().getID() == advisorID){
            currNode->getData().addAdvisee(studentID);
            break;
        }
        else if(currNode->getData().getID() > advisorID){
            currNode = currNode->m_left;
        }
        else{
            currNode = currNode->m_right;
        }
    }
}

//removes an advisee based on the  from the given faculty 
template <typename T>
bool LazyBST<T>::removeAdvisee(int data, int oldID){ 
    bool result = removeAdviseeHelper(m_root, data, oldID);
    return result;
}

//helper method for removing and advisee from given faculty member
template <typename T>
bool LazyBST<T>::removeAdviseeHelper(TreeNode<T>*& currNode, int data, int oldID){
    bool found = false;
    if(currNode == NULL){
        return false; 
    }
    if(currNode->getData().getID() > data){
        found = removeAdviseeHelper(currNode->m_left, data, oldID);
    }
    else if(currNode->getData().getID() < data){
        found = removeAdviseeHelper(currNode->m_right, data, oldID);
    }
    else {
        DblList<int>* list = new DblList<int>();
        list = currNode->getData().getAdvisees();
        if(list->size() == 0){
            cout << "Advisor has no advisees" << endl;
        }
        for(int i = 0; i < list->size(); i++){
            if(list->get(i) == oldID){
                list->remove(i);
                found = true;
            }
        }
    }
    return found;
}

//creates the string of faculty member info for the output file when exiting the program
template <typename T>
string LazyBST<T>::createOutputFileFaculty(){
    string result;
    result += createOutputFileHelperFaculty(m_root);
    return result;
}

// helper for createOutputFileHelperFaculty
template <typename T>
string LazyBST<T>::createOutputFileHelperFaculty(TreeNode<T>* currNode){
    string result;
    if(currNode != NULL){
        result += createOutputFileHelperFaculty(currNode->m_left);
        result += currNode->getData().storeInfo();
        result += createOutputFileHelperFaculty(currNode->m_right);
    } else if(m_root == NULL){
        cout << "There are no students in the table!" << endl;
    }
    return result;
}

//creates and returns the string of students
template <typename T>
string LazyBST<T>::createOutputFileStudent(){
    string result;
    result += createOutputFileHelperStudent(m_root);
    return result;
}

//helper for createOutputFileStudent
template <typename T>
string LazyBST<T>::createOutputFileHelperStudent(TreeNode<T>* currNode){
    string result;
    if(currNode != NULL){
        result += createOutputFileHelperStudent(currNode->m_left);
        result += currNode->getData()->storeInfo();
        result += createOutputFileHelperStudent(currNode ->m_right);
    } else if(m_root == NULL){
        cout << "There are no students in the table!" << endl;
    }
    return result;
}

//creating the 'log file' for the output using methods from the LaxyBST class
template<typename T>
void LazyBST<T>::finalOutputFile(LazyBST<Faculty>& facultyMembers, LazyBST<Student*>& students){
    ofstream outputFile("runLog.txt");
    outputFile << students.createOutputFileStudent();
    outputFile << facultyMembers.createOutputFileFaculty();
    outputFile.close();
}

//getting left depth
template <typename T>
int LazyBST<T>::getLeftDepth(){
    if(m_root == nullptr) return 0;
    return leftDepthHelper(m_root->m_left);
}

//getting right depth
template <typename T>
int LazyBST<T>::getRightDepth(){
    if(m_root == nullptr) return 0;
    return rightDepthHelper(m_root->m_right);
}


template <typename T>
int LazyBST<T>::leftDepthHelper(TreeNode<T>* parent){
    if(parent == nullptr) return 0;
    return 1 + max(leftDepthHelper(parent->m_left), leftDepthHelper(parent->m_right));
}


template <typename T>
int LazyBST<T>::rightDepthHelper(TreeNode<T>* parent){
    if(parent == nullptr) return 0;
    return 1 + max(rightDepthHelper(parent->m_left), rightDepthHelper(parent->m_right));
}

//checks the depth of both trees and adjusts accordingly
template <typename T>
void LazyBST<T>::checkDepths(){
    int leftDepth = getLeftDepth();
    int rightDepth = getRightDepth();
    if((double)leftDepth / rightDepth > 1.5 || (double)rightDepth / leftDepth > 1.5){ 
        rebalancedTree();
    }
}



//method to traverse the tree in order and store it in the passed array in order.
template <typename T>
void LazyBST<T>::storeTree(TreeNode<T>* currNode, T* arr, int& index){
    if(currNode == NULL){
        return;
    }
    storeTree(currNode->m_left, arr, index);
    arr[index++] = currNode->getData();
    storeTree(currNode->m_right, arr, index);
}

//method that creates the array and returns to be used when rebalancing
template <typename T>
T* LazyBST<T>::toArray(){
    T* arr = new T[m_size];
    int index = 0;
    storeTree(m_root, arr, index);
    return arr;
}

//helper method that does the rebalancing of the tree recursively
template <typename T>
TreeNode<T>* LazyBST<T>::rebalanceHelper(T* arr, int start, int end){
    if(start > end){
        return NULL;
    }
    int mid = (start + end) / 2;
    TreeNode<T>* newNode = new TreeNode<T>(arr[mid]);
    newNode->m_left = rebalanceHelper(arr, start, mid - 1);
    newNode->m_right = rebalanceHelper(arr, mid + 1, end);
    return newNode;
}

//tree that rebalances the method and deletes the array freeing up the space
template <typename T>
void LazyBST<T>::rebalancedTree(){
    T* arr = toArray();
    m_root = rebalanceHelper(arr, 0, m_size - 1);
    delete[] arr;
}


template <typename T> 
bool LazyBST<T>::contains(T data){ 
    return containsHelper(m_root, data);
}

template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T>* currNode, T data){
    if(currNode == NULL){
        return false;
    }else if(data < currNode->getData()){
        return containsHelper(currNode->m_left, data);
    }else if(data > currNode->getData()){
        return containsHelper(currNode->m_right, data);
    }else{
        return true;
    }
}

template <typename T>
void LazyBST<T>::insert(T data){
    TreeNode<T>* newNode = new TreeNode<T>(data);
    insertHelper(m_root, newNode);
    ++m_size;
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& currNode, TreeNode<T>* newNode){
    if(currNode == NULL){
        currNode = newNode; 
    }else if(newNode->getData() < currNode->getData()){
        insertHelper(currNode->m_left, newNode);
    }else if(newNode->getData() > currNode->getData()){
        insertHelper(currNode->m_right, newNode);
    }
}
template <typename T>
void LazyBST<T>::printTreePostFix(){
    printPostHelper(m_root);
}

template <typename T>
void LazyBST<T>::printPostHelper(TreeNode<T>* currNode){
    if(currNode != NULL){
        printPostHelper(currNode -> m_left);
        printPostHelper(currNode -> m_right);
        cout << currNode -> getData() << endl;
    }
}

template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* child){
    while(child -> m_left != NULL){
        child = child->m_left;
    }
    return child;
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
    while(target != NULL && target->m_data != key){
        parent = target;
        if(key < target -> m_data){
            target = target -> m_left;
        }else{
            target = target -> m_right;
        }
    }
}

template <typename T>
void LazyBST<T>::remove(T data){
    //check if empty
    if(m_root == NULL){
        cout << "The tree is empty! You can't remove anything!" << endl;
    }
    TreeNode<T>* target = NULL;
    TreeNode<T>* parent = NULL;
    target = m_root;
    findTarget(data, target, parent);
    if(target == NULL){ //value wasn't in the tree, nothing to do
        return;
    }
    //case 1 - check if leaf (including the root)
    if(target->m_left == NULL && target->m_right == NULL){ //no children
        if(target == m_root){
            m_root = NULL;
        }else{ //it's not the root
            if(target == parent->m_left){
                parent->m_left = NULL;
            }else{
                parent->m_right = NULL;
            }
        }
        delete target; //free memory
    }else if(target->m_left != NULL && target->m_right != NULL){ //case 2 - 2 children case
        TreeNode<T>* suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value);
        target->m_data = value;
        
    }else{ //case 3 - 1 child
        TreeNode<T>* child;
        if(target->m_left != NULL){
            child = target->m_left;
        }else{
            child = target->m_right;
        }
        if(target == m_root){
            m_root = child;
        }else{
            if(target == parent->m_left){
                parent->m_left = child;
            }else{
                parent->m_right = child;
            }
        }
        delete target; //free memory
    }
    --m_size;
}

#endif