/*
Pranav Surampudi
2407260
surampudi@chapman.edu
CPSC350-03
PA5
*/

#ifndef FACULTY_H
#define FACULTY_H

#include "DblList.h"

#include <iostream>
using namespace std;

class Faculty{
    public:
        Faculty();
        Faculty(int facultyID, string name, string level, string department);
        virtual~ Faculty();
        void printInfo();
        string storeInfo();
        void addAdvisee(int studentID);
        int getfacultyID();
        DblList<int>* getAdvisees();
        //overloaded operators for checking greater than or less than
        bool operator>(Faculty other){
            return m_facultyID > other.m_facultyID;
        }
        bool operator<(Faculty other){
            return m_facultyID < other.m_facultyID;
        }
    private:
        int m_facultyID;
        string m_name;
        string m_position;
        string m_department;
        DblList<int>* studentIds;
};

#endif