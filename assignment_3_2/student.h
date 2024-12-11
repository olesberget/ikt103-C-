//
// Created by mini- on 03.03.2023.
//

#ifndef ASSIGNMENT_3_2_STUDENT_H
#define ASSIGNMENT_3_2_STUDENT_H
#include <string>

using namespace std;

class Student {
public:
    Student(int id, string name, int age, int attendance);
    const int getId();
    const string getName();
    const int getAge();
    const int getAttendance();

private:
    int id_;
    string name_;
    int age_;
    int attendance_;
};


#endif //ASSIGNMENT_3_2_STUDENT_H
