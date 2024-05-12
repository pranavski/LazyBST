/*
Pranav Surampudi
2407260
surampudi@chapman.edu
CPSC350-03
PA5
*/

#ifndef Sim_H
#define Sim_H


#include "LazyBST.h"

class Sim{
    public:
        Sim();
        virtual~ Sim();
        void simulateMenu();
        void addStudent();
        void addFaculty();
    private:
        int studentID;
        int facultyID;
        LazyBST<Student*> students;
        LazyBST<Faculty> facultys;
};

#endif