#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    
    http_client client(U("http://localhost:5000"));

    while (true) {
        cout << "1. Read all students\n"
             << "2. Get student by id\n"
             << "3. Add student\n"
             << "4. Edit student\n"
             << "5. Remove student\n"
             << "6. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:{
                client.request(methods::GET, U("/students/")).then([](http_response response)
                {if (response.status_code() == status_codes::OK) {
                        auto students = response.extract_json().get().as_array();
                        for (const auto& student : students) {
                            cout << "id: " << student.at(U("id")).as_integer() << ", ";
                            cout << "name: " << utility::conversions::to_utf8string(student.at(U("name")).as_string()) << ", ";
                            cout << "email: " << utility::conversions::to_utf8string(student.at(U("email")).as_string()) << ", ";
                            cout << "year: " << student.at(U("year")).as_integer() << endl;
                        }
                    }
                else {cout << "Error: " << response.status_code() << endl;}
                }).wait();
                break;
            }

            case 2: {
                int id;
                cout << "Enter student id: ";
                cin >> id;

                client.request(methods::GET,U("/students/") + utility::conversions::to_string_t(to_string(id))).then([](http_response response)
                {if (response.status_code() == status_codes::OK) {
                        auto student = response.extract_json().get();
                        cout << "id: " << student.at(U("id")).as_integer() << ", ";
                        cout << "name: " << utility::conversions::to_utf8string(student.at(U("name")).as_string()) << ", ";
                        cout << "email: " << utility::conversions::to_utf8string(student.at(U("email")).as_string()) << ", ";
                        cout << "year: " << student.at(U("year")).as_integer() << endl;
                    }
                else if (response.status_code() == status_codes::NotFound) {cout << "Student not found\n";}
                else {cout << "Error: " << response.status_code() << endl;}
                }).wait();
               break;
            }

            case 3: {
                int year;
                string name, email;


                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter year: ";
                cin >> year;

                json::value student;
                student[U("name")] = json::value::string(utility::conversions::to_string_t(name));
                student[U("email")] = json::value::string(utility::conversions::to_string_t(email));
                student[U("year")] = year;

                client.request(methods::POST, U("/students/"), student).then([](http_response response)
                {if (response.status_code() == status_codes::Created) {
                        json::value new_student = response.extract_json().get();
                        cout << "Added student: ";
                        cout << "id: " << new_student.at(U("id")).as_integer() << ", ";
                        cout << "name: " << utility::conversions::to_utf8string(new_student.at(U("name")).as_string()) << ", ";
                        cout << "email: " << utility::conversions::to_utf8string(new_student.at(U("email")).as_string()) << ", ";
                        cout << "year: " << new_student.at(U("year")).as_integer() << endl;
                    }
                else {cout << "Error: " << response.status_code() << endl;}
                }).wait();
                break;
            }

            case 4: {
                int id;
                int year;
                string name, email;


                cout << "Enter student id: ";
                cin >> id;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new email: ";
                getline(cin, email);
                cout << "Enter new year: ";
                cin >> year;

                json::value student;
                student[U("id")] = id;
                student[U("name")] = json::value::string(utility::conversions::to_string_t(name));
                student[U("email")] = json::value::string(utility::conversions::to_string_t(email));
                student[U("year")] = year;

                client.request(methods::PUT, U("/students/") + utility::conversions::to_string_t(to_string(id)), student).then([](http_response response) {
                    if (response.status_code() == status_codes::OK) {cout << "Student was edited successfully\n";}
                    else if (response.status_code() == status_codes::NotFound) {cout << "Student not found\n";}
                    else {cout << "Error: " << response.status_code() << endl;}
                }).wait();
                break;
            }

            case 5: {
                int id;
                cout << "Enter student id: ";
                cin >> id;

                client.request(methods::DEL, U("/students/") + utility::conversions::to_string_t(to_string(id))).then([](http_response response) {
                    if (response.status_code() == status_codes::NoContent) {cout << "Student was removed successfully" << endl;}
                    else if (response.status_code() == status_codes::NotFound) {cout << "Student not found" << endl;}
                    else {cout << "Error: " << response.status_code() << endl;}
                }).wait();
                break;
            }
            case 6:
                cout << "Exiting program...\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}