//
// Created by mini- on 03.03.2023.
//

#include "student.h"

using namespace std;

Student::Student(int id, string name, int age, int attendance)
: id_(id), name_(name), age_(age), attendance_(attendance) {}

const int Student::getId() {
    return id_;
}

const string Student::getName() {
    return name_;
}

const int Student::getAge() {
    return age_;
}

const int Student::getAttendance() {
    return attendance_;
}