/*
Pranav Surampudi
2407260
surampudi@chapman.edu
CPSC350-03
PA5
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student{
    public:
        Student();
        Student(int studentID, string name, string level, string major, double GPA, int advisor);
        virtual~ Student();
        int getStudentID();
        void setStudentID(int studentID);
        void printInfo();
        string storeInfo();
        int getAdvisorID();
        void setAdvisorID(int temp);
        //overloaded operators for greater than and less than
        bool operator>(Student other){
            return m_studentID > other.m_studentID;
        }
        bool operator<(Student other){
            return m_studentID < other.m_studentID;
        }
    private:
        int m_studentID;
        string m_name;
        string m_standing;
        string m_major;
        double m_GPA;
        int m_advisorID;
};

#endif