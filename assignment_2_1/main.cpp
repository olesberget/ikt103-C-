#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    int id;
    string name, email;

    Student(int id, const string &name, const string &email) : id(id), name(name), email(email) {}
    int getId() const {return this->id;}
    string getName() {return this->name;}
    string getEmail() {return this->email;}
    void setName(string name) {this->name = name;}
    void setEmail(string email) {this->email = email;}
};
class Test {
public:
    int id;
    string courseName, testName, date;

    Test(int id, const string &courseName, const string &testName, const string &date) : id(id), courseName(courseName), testName(testName), date(date){}
    int getId() {return this->id;}
    string getCourseName() {return this->courseName;}
    string getTestName() {return this->testName;}
    string getDate() {return this->date;}
    void setCourseName(string courseName) {
        this->courseName = courseName;}
    void setTestName(string testName) {
        this->testName = testName;}
    void setDate(string date) {
        this->date = date;}
};
class TestResult {
public:
    int testId, studentId, grade;

    TestResult(int testId, int studentId, int grade) : testId(testId), studentId(studentId), grade(grade) {}
    int getTestId() {return this->testId;}
    int getStudentId() {return this->studentId;}
    int getGrade() {return this->grade;}
    void setScore(int grade) {
        this->grade = grade;}
    TestResult() {
    }
};




int main() {

    int choice = 0;

    int studentIdCounter = 1;
    int testIdCounter = 1;

    vector<Student> students;
    map<int, int> studentIdToIndex;

    vector<Test> tests;
    map<int, int> testIdToIndex;

    vector<TestResult> testResults;

    while (true) {
        cout << "Please choose:" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Edit student" << endl;
        cout << "3. Remove student" << endl;
        cout << "4. Add test" << endl;
        cout << "5. Edit test" << endl;
        cout << "6. Remove test" << endl;
        cout << "7. Add test result" << endl;
        cout << "8. Edit test result" << endl;
        cout << "9. Remove test result" << endl;
        cout << "10. Show all info" << endl;
        cout << "11. Exit" << endl;
        cin >> choice;


        switch (choice)
        {
            case 1:{
                cout << "Enter name: ";
                string name;
                cin.ignore();
                getline(cin, name);

                cout << "Enter email: ";
                string email;
                getline(cin, email);

                int id = studentIdCounter;
                studentIdCounter++;

                Student student(id, name, email);
                students.push_back(student);
                studentIdToIndex[id] = students.size() - 1;
                cout << "Student added with id: " << id << endl;
                break;
            }
            case 2:{
                if (students.empty())
                {cout << "No students to edit" << endl; break;}

                cout << "Select student to edit (by id):" << endl;
                int counter = 1;
                for (auto& student : students) {
                    cout << counter << ". " << student.getName() << " (id: " << student.getId() << ")" << endl;
                    counter++;
                }
                cout << counter << ". Back to menu" << endl;

                int choice;
                cin >> choice;
                if (choice == counter) {break;}

                auto it = students.begin();
                advance(it, choice - 1);

                cout << "Enter new name: ";
                string name;
                cin.ignore();
                getline(cin, name);
                it->setName(name);

                cout << "Enter new email: ";
                string email;
                getline(cin, email);
                it->setEmail(email);

                cout << "Student edited" << endl;
                break;
            }
            case 3:{
                if (students.empty()) {
                    cout << "No students to remove" << endl;
                    break;
                }
                cout << "Select student to remove (by id):" << endl;

                int counter = 1;
                for (auto& student : students) {
                    cout << counter << ". " << student.getName() << " (id: " << student.getId() << ")" << endl;
                    counter++;}
                cout << counter << ". Back to menu" << endl;
                int choice;
                cin >> choice;
                if (choice == counter) {break;}
                auto it = students.begin();
                advance(it, choice - 1);
                int id = it->getId();
                students.erase(it);
                studentIdToIndex.erase(id);

                cout << "Student removed" << endl;
                break;
            }
            case 4:{
                cout << "Enter course name: ";
                string courseName;
                cin.ignore();
                getline(cin, courseName);

                cout << "Enter test name: ";
                string testName;
                getline(cin, testName);

                cout << "Enter date (format: YYYY.MM.DD): ";
                string date;
                getline(cin, date);

                int id = testIdCounter;
                testIdCounter++;

                Test test(id, courseName, testName, date);
                tests.push_back(test);
                testIdToIndex[id] = tests.size() - 1;

                cout << "Test added with id: " << id << endl;
                break;
            }
            case 5:{
                if (tests.empty()) {cout << "No tests to edit" << endl; break;}

                cout << "Select test to edit (by id):" << endl;
                int counter = 1;
                for (auto& test : tests) {
                    cout << counter << ". " << test.getTestName() << " (id: " << test.getId() << ")" << endl;
                    counter++;}
                cout << counter << ". Back to menu" << endl;

                int choice;
                cin >> choice;
                if (choice == counter) {break;}
                auto it = tests.begin();
                advance(it, choice - 1);

                cout << "Enter new course name: ";
                string courseName;
                cin.ignore();
                getline(cin, courseName);
                it->setCourseName(courseName);

                cout << "Enter new test name: ";
                string testName;
                getline(cin, testName);
                it->setTestName(testName);

                cout << "Enter new date: ";
                string date;
                getline(cin, date);
                it->setDate(date);

                cout << "Test edited" << endl;
                break;
            }
            case 6:{
                if (tests.empty()) {cout << "No tests to remove" << endl; break;}

                cout << "Select test to remove (by id):" << endl;
                int counter = 1;
                for (auto & test : tests) {
                    cout << counter << ". " << test.getTestName() << " (id: " << test.getId() << ")" << endl;
                    counter++;}
                cout << counter << ". Back to menu" << endl;

                int choice;
                cin >> choice;
                if (choice == counter) {break;}
                auto it = tests.begin();
                advance(it, choice - 1);
                int id = it->getId();
                tests.erase(it);
                testIdToIndex.erase(id);

                for (int i = 0; i < testResults.size(); i++) {
                    if (testResults[i].getTestId() == id) {
                        testResults.erase(testResults.begin() + i);
                        i--;}}

                cout << "Test removed" << endl;
                break;
            }
            case 7: {
                if (students.empty()) {cout << "No students to add test result for" << endl; break;}
                if (tests.empty()) {cout << "No tests to add results for" << endl; break;}

                cout << "Select student to add test result for (by id):" << endl;
                int counter = 1;
                for (auto & student : students) {
                    cout << counter << ". " << student.getName() << " (id: " << student.getId() << ")" << endl; counter++;}
                cout << counter << ". Back to menu" << endl;

                int studentChoice;
                cin >> studentChoice;
                if (studentChoice == counter) {break;}

                auto studentIt = students.begin();
                advance(studentIt, studentChoice - 1);
                int studentId = studentIt->getId();
                cout << "Select test to add result for (by id):" << endl;
                counter = 1;
                for (auto & test : tests) {
                    cout << counter << ". " << test.getTestName() << " (id: " << test.getId() << ")" << endl; counter++;}
                cout << counter << ". Back to menu" << endl;
                int testChoice;
                cin >> testChoice;
                if (testChoice == counter) {break;}
                auto testIt = tests.begin();
                advance(testIt, testChoice - 1);
                int testId = testIt->getId();

                cout << "Enter grade: ";
                int grade;
                cin.ignore();
                cin >> grade;

                TestResult testResult(testId, studentId, grade);
                testResults.push_back(testResult);
                cout << "Test result added" << endl;
                break;
            }
            case 8:{
                if (testResults.empty()) {cout << "No test results to edit" << endl; break;}

                cout << "Select student (by id):" << endl;
                int counter = 1;
                map<int, int> studentIdToCounter;
                for (auto & student : students) {
                    int studentId = student.getId();
                    if (studentIdToIndex.count(studentId) > 0) {
                        cout << counter << ". " << student.getName() << " (id: " << studentId << ")" << endl;
                        studentIdToCounter[studentId] = counter;
                        counter++;}
                }
                cout << counter << ". Back to menu" << endl;
                int choice;
                cin >> choice;
                if (choice == counter) {break;}
                int selectedStudentId = 0;
                for (const auto& [studentId, count] : studentIdToCounter) {
                    if (count == choice) {
                        selectedStudentId = studentId;
                        break;}
                }
                cout << "Select course (by id):" << endl;
                counter = 1;
                map<int, int> testIdToCounter;
                for (auto & test : tests) {
                    int testId = test.getId();
                    if (testIdToIndex.count(testId) > 0) {
                        std::cout << counter << ". " << test.getCourseName() << " (id: " << testId << ")" << std::endl;
                        testIdToCounter[testId] = counter;
                        counter++;
                    }
                }
                cout << counter << ". Back to menu" << endl;
                cin >> choice;
                if (choice == counter) {break;}
                int selectedTestId = 0;
                for (const auto& [testId, count] : testIdToCounter) {
                    if (count == choice) {
                        selectedTestId = testId;
                        break;}
                }

                cout << "Enter new score:" << endl;
                int newScore;
                cin >> newScore;

                for (auto & testResult : testResults) {
                    if (testResult.getStudentId() == selectedStudentId && testResult.getTestId() == selectedTestId) {
                        testResult.setScore(newScore);
                        break;
                    }
                }
                break;
            }
            case 9:{
                if (testResults.empty()) {cout << "No test results to remove" << endl;break;}

                cout << "Select student (by id):" << endl;
                int counter = 1;
                map<int, int> studentIdToCounter;
                for (auto & student : students) {
                    int studentId = student.getId();
                    if (studentIdToIndex.count(studentId) != 0) {
                        std::cout << counter << ". " << student.getName() << " (id: " << studentId << ")" << std::endl;
                        studentIdToCounter[studentId] = counter;
                        counter++;}
                }
                cout << counter << ". Back to menu" << endl;

                int choice;
                cin >> choice;
                if (choice == counter) {break;}
                int selectedStudentId = 0;
                for (const auto& [studentId, count] : studentIdToCounter) {
                    if (count == choice) {
                        selectedStudentId = studentId;
                        break;}
                }
                cout << "Select course (by id):" << std::endl;
                counter = 1;
                map<int, int> testIdToCounter;
                for (auto & test : tests) {
                    int testId = test.getId();
                    if (testIdToIndex.count(testId) != 0) {
                        std::cout << counter << ". " << test.getCourseName() << " (id: " << testId << ")" << std::endl;
                        testIdToCounter[testId] = counter;
                        counter++;}
                }
                cout << counter << ". Back to menu" << endl;
                cin >> choice;
                if (choice == counter) {break;}
                int selectedTestId = 0;
                for (const auto& [testId, count] : testIdToCounter) {
                    if (count == choice) {
                        selectedTestId = testId;
                        break;}
                }
                for (auto it = testResults.begin(); it != testResults.end();) {
                    if (it->getStudentId() == selectedStudentId && it->getTestId() == selectedTestId) {
                        it = testResults.erase(it);
                    } else {
                        it++;
                    }
                }
                break;
            }
            case 10:{
                cout << "All Student Information:" << endl;
                for (auto & student : students) {
                    cout << "student id = " << student.getId() << ", name = " << student.getName() << ", email = " << student.getEmail() << endl;
                }
                cout << "All Test Information:" << endl;
                for (auto & test : tests) {
                    cout << "test id = " << test.getId() << ", course name = " << test.getCourseName() << ", test name = "
                         << test.getTestName() << ", date = " << test.getDate() << endl;
                }
                cout << "All Test Result Information:" << endl;
                for (auto & testResult : testResults) {
                    string courseName = "";
                    string testName = "";
                    int testId = testResult.getTestId();
                    for (auto & test : tests) {
                        if (test.getId() == testId) {
                            courseName = test.getCourseName();
                            testName = test.getTestName();
                            break;
                        }
                    }
                    if (!courseName.empty() && !testName.empty()) {
                        cout << "student id = " << testResult.getStudentId() << ", course name = " << courseName << ", test id = "
                             << testId << ", test name = " << testName << ", grade = " << testResult.getGrade() << endl;
                    }
                }
                break;
            }
            case 11:
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }

    }

}
