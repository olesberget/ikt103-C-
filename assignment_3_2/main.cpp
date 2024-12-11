#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "rapidjson/document.h"
#include "student.h"
#include "student.cpp"

using namespace std;

int main() {
    ifstream ifs("students.json");
    string content((istreambuf_iterator<char>(ifs)),(istreambuf_iterator<char>()));
    ifs.close();
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    list<Student*> students;
    Student* youngest = nullptr;
    Student* oldest = nullptr;
    int sum_age = 0;
    int count_age = 0;
    int average_age = 0;
    vector<Student*> bad_students;

    for (auto& st_get : doc.GetArray()) {
        int id = st_get["id"].GetInt();
        string name = st_get["name"].GetString();
        int age = st_get["age"].GetInt();
        int attendance = st_get["attendance"].GetInt();
        students.push_back(new Student(id, name, age, attendance));
        cout << "Student " << id << ": " << name << ", " << age << " years old, " << attendance << "% attendance" << endl;}

    for (auto student : students) {
        if (youngest == nullptr || student->getAge() < youngest->getAge()) {youngest = student;}
        if (oldest == nullptr || student->getAge() > oldest->getAge()) {oldest = student;}

        sum_age += student->getAge();
        count_age++;
        average_age = count_age == 0 ? 0 : sum_age / count_age;

        if (student->getAttendance() < 30) {bad_students.push_back(student);}}

    cout << "Youngest: " << youngest->getName() << endl;
    cout << "Oldest: " << oldest->getName() << endl;
    cout << "Average age: " << average_age << endl;
    for (auto st_bd : bad_students) {cout << "Bad student: " << st_bd->getName() << endl;}

    for (auto st_de : students) {delete st_de;}
    return 0;
}