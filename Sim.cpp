/*
Pranav Surampudi
2407260
surampudi@chapman.edu
CPSC350-03
PA5
*/

#include "Sim.h"
#include "Faculty.h"
#include "Student.h"

#include <string>
#include <limits>// to make sure that the input given is not greater than 11
#include <iostream> 

//constructor with default values of 1000 that increment 
Sim::Sim(){
    studentID = 1000;
    facultyID = 1000;
}

//destructor 
Sim::~Sim(){

}


void Sim::simulateMenu(){
    int input = 0;
    string menu;
    menu += "1: Print all students and their information (sorted by ascending id #)\n";
    menu += "2: Print all faculty and their information (sorted by ascending id #)\n";
    menu += "3: Find and display student information given the student id\n";
    menu += "4: Find and display faculty information given the faculty id\n";
    menu += "5: Add a new student\n";
    menu += "6: Delete a student given the id\n";
    menu += "7: Add a new faculty member\n";
    menu += "8: Delete a faculty member given the id\n";
    menu += "9: Change a student's advisor given the student id and the new faculty id\n";
    menu += "10: Remove an advisee from a faculty member given the ids\n";
    menu += "11: Exit\n";
    while(input != 11){
        cout << menu << endl;
        cout << "Enter a number based on the menu: " << endl;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number from 1 to 11." << endl;
            continue;
        }
        switch (input){
            case 1:
                cout << "Printing all student's info in ascending order based on ID: " << endl;
                students.printTreeInOrderStudent();
                break;
            case 2:
                cout << "Printing all faculty's info in ascending order based on ID: " << endl;
                facultys.printTreeInOrderFaculty();
                break;
            case 3:
                if(students.size() == 0){
                    cout << "There are no students in the table so no info can be printed!" << endl;
                }else { 
                    cout << "Enter the ID of the student you would like to find: " << endl;
                    int student;
                    if (!(cin >> student)) {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid input, please enter a integer." << endl;
                        break;
                    }
                    bool checkStudent;
                    checkStudent = students.printStudentInfo(student);
                    if(checkStudent == false){
                        cout << "Student could not be found make sure the ID is correct and exists!" << endl;
                    } else {
                        //do nothing
                    }
                }
                break;
            case 4:
                if(facultys.size() == 0){
                    cout << "There are no faculty members in the table so no info can be printed!" << endl;
                } else {
                    cout << "Enter the ID of the faculty you would like to find: " << endl;
                    int faculty;
                    if (!(cin >> faculty)) {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input, please enter a valid integer." << endl;
                        break;
                    }
                    bool checkFaculty;
                    checkFaculty = facultys.printFacultyInfo(faculty);
                    if(checkFaculty == false){
                        cout << "Faculty member could not be found make sure the ID is correct and exists!" << endl;
                    }
                }
                break;
            case 5:
                addStudent();
                students.checkDepths();
                break;
            case 6:
                if(students.size() == 0){
                    cout << "Student table is empty, no student can be deleted!" << endl;
                    break;
                }
                cout << "Enter the ID of the student you would like to delete: " << endl;
                int deleteID;
                if (!(cin >> deleteID)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input, please enter a valid integer." << endl;
                    break;
                }
                bool deletedStudent;
                deletedStudent = students.deleteStudent(deleteID, facultys);
                if(deletedStudent == false){
                    cout << "Student could not be found, therefore no one was deleted. Make sure the ID is correct and exists!" << endl;
                }
                students.checkDepths();
                break;
            case 7:
                addFaculty();
                facultys.checkDepths();
                break;
            case 8:
                if(facultys.size() == 0){
                    cout << "There are no faculty members in the table so no one can be deleted!" << endl;
                } else {
                    cout << "Enter the ID of the faculty member you would like to delete: " << endl;
                    int deleteIDFaculty;
                    if (!(cin >> deleteIDFaculty)) { 
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid input, please enter a valid integer." << endl;
                        break;
                    };
                    bool deletedFaculty;
                    deletedFaculty = facultys.deleteFaculty(deleteIDFaculty);
                    if(deletedFaculty == false){
                        cout << "Faculty member could not be found, therefore no one was deleted. Make sure the ID is correct and exists!" << endl;
                    }
                    facultys.checkDepths();
                }
                break;
            case 9:
                if(students.size() == 0){
                    cout << "Student table is empty, no student can be deleted!" << endl;
                    break;
                }
                cout << "Enter the Student's ID which you would like to change: " << endl;
                int userInput;
                if (!(cin >> userInput)) { 
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid input, please enter a valid integer." << endl;
                        break;
                }
                if(students.findNodeStudentTrue(userInput) == false){
                    cout << "That is not a valid student ID make sure it is correct and exists!" << endl;
                } else {
                    cout << "Enter the new faculty ID you would like to give the student: " << endl;
                    int changeID;
                    cin >> changeID;
                    if(facultys.findNodeFaculty(changeID) == false){
                        cout << "That is not a valid advisor ID make sure it is correct and exists!" << endl;
                    } else {
                        students.changeStudentAdvisor(userInput, changeID, facultys);
                    }
                }
                break;
            case 10:
                if(facultys.size() == 0){
                    cout << "There are no faculty members in the table so no one can be deleted!" << endl;
                    break;
                }
                cout << "Enter the Faculty's ID which you would like to remove an advisee from: " << endl;
                int user;
                if (!(cin >> user)) { 
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid input, please enter a valid integer." << endl;
                    break;
                }
                if(facultys.findNodeFaculty(user) == false){
                    cout << "That is not a valid advisor ID make sure it is correct and exists!" << endl;
                } else {
                    cout << "Enter the ID you would like to remove from Advisor's list: " << endl;
                    int removeID;
                    if (!(cin >> removeID)) { 
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid input, please enter a valid student ID." << endl;
                        break;
                    }
                    if(facultys.removeAdvisee(user, removeID) == true){
                        students.findNodeStudent(user)->getData()->setAdvisorID(-1);
                    } else {
                        cout << "Faculty's list did not contain this ID." << endl;
                    }
                }
                break;
            case 11:
                students.finalOutputFile(facultys, students);
                cout << "You have exited the menu." << endl;
                break;
            default:
                cout << "You enter an invalid number! Make sure it's between 1 and 11!" << endl;
                break;
        }
    }
}

//method that creates a new student object with inputed info and a unique ID which is an increment of the previous ID
void Sim::addStudent(){
    if(facultys.size() == 0){
        cout << "You can't make a student without advisors! Add an advisor first!" << endl;
    } else {
        cout << "Enter student name" << endl;
        cin.ignore();
        string name;
        getline(cin, name);
        cout << "Enter student standing" << endl;
        string standing;
        getline(cin, standing);
        cout << "Enter student major" << endl; 
        string major;
        getline(cin, major);
        cout << "Enter student GPA" << endl;
        double GPA;
        cin >> GPA;
        cout << "Enter advisor ID" << endl;
        int advisorID;
        cin >> advisorID;
        if(facultys.findNodeFaculty(advisorID) == false){
            cout << "That is not a valid advisor ID, therefore a student can't be made!" << endl;
        } else {
            studentID++;
            Student* S1 = new Student(studentID, name, standing, major, GPA, advisorID);
            students.insert(S1);
            facultys.findNode(advisorID)->getData().getAdvisees()->addBack(studentID);
            students.checkDepths();
        }
    }
}

//method that creates a new faculty object with inputed info and a unique ID which is an increment of the previous ID
void Sim::addFaculty(){
    facultyID++;
    cout << "Enter faculty name" << endl;
    cin.ignore();
    string name;
    getline(cin, name);
    cout << "Enter faculty position" << endl;
    string position;
    getline(cin, position);
    cout << "Enter faculty department" << endl;
    string department;
    getline(cin, department);
    Faculty F1(facultyID, name, position, department);
    facultys.insert(F1);
}