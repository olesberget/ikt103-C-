#include <iostream>
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

int main() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);

    int choice = 0;
    while (true) {
        cout << "1. Read all students\n"
                "2. Get student by id\n"
                "3. Add student\n"
                "4. Edit student\n"
                "5. Remove student\n"
                "6. Search\n"
                "7. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:{
                SQLite::Statement query(db, "SELECT * FROM students");
                bool found = false;
                while (query.executeStep()) {
                    found = true;
                    int id = query.getColumn("id");
                    int year = query.getColumn("year");
                    string name = query.getColumn("name");
                    string email = query.getColumn("email");
                    cout << "id: " << id << ", name: " << name << ", email: " << email << ", year: " << year << endl;
                }   if (!found) {cout << "No students found" << endl;}break;}

            case 2:{
                int id;
                cout << "Enter the student id: ";
                cin >> id;
                SQLite::Statement query(db, "SELECT * FROM students WHERE id = ?");
                query.bind(1, id);
                if (query.executeStep()) {
                    string name = query.getColumn("name");
                    string email = query.getColumn("email");
                    int year = query.getColumn("year");
                    cout << "id: " << id << ", name: " << name << ", email: " << email << ", year: " << year << endl;
                } else {cout << "Student not found" << endl;}break;}

            case 3:{
                int year;
                string name, email;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter year: ";
                cin >> year;

                SQLite::Statement query(db, "INSERT INTO students (name, email, year) VALUES (?, ?, ?)");
                query.bind(1, name);
                query.bind(2, email);
                query.bind(3, year);
                query.exec();

                int id = db.getLastInsertRowid();
                cout << "Added student: " << "id: "<< id << ", name: " << name << ", email: " << email << ", year: " << year << endl;
                cout << "Student was added successfully" << endl;break;}

            case 4:{
                int id;
                cout << "Enter the student id: ";
                cin >> id;

                SQLite::Statement findQuery(db, "SELECT * FROM students WHERE id = ?");
                findQuery.bind(1, id);

                if (findQuery.executeStep()) {
                    string name, email;
                    int year;
                    cout << "Enter the new name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter the new email: ";
                    cin >> email;
                    cout << "Enter the new year: ";
                    cin >> year;

                    SQLite::Statement updateQuery(db, "UPDATE students SET name = ?, email = ?, year = ? WHERE id = ?");
                    updateQuery.bind(1, name);
                    updateQuery.bind(2, email);
                    updateQuery.bind(3, year);
                    updateQuery.bind(4, id);
                    updateQuery.exec();

                    cout << "Student was edited successfully" << endl;}
                else {cout << "Student not found" << endl;}break;}

            case 5:{
                int id;
                cout << "Enter the student id: ";
                cin >> id;
                SQLite::Statement query(db, "DELETE FROM students WHERE id = ?");
                query.bind(1, id);
                if (query.exec() > 0) {cout << "Student was removed successfully" << endl;}
                else {cout << "Student not found" << endl;}break;}

            case 6:{
                string keyword;
                cout << "Enter keyword to search: ";
                cin.ignore();
                getline(cin, keyword);

                SQLite::Statement query(db, "SELECT * FROM students WHERE name LIKE ? OR email LIKE ?");
                string pattern = "%" + keyword + "%";
                query.bind(1, pattern);
                query.bind(2, pattern);

                bool found = false;
                while (query.executeStep()) {
                    found = true;
                    int id = query.getColumn("id");
                    string name = query.getColumn("name");
                    string email = query.getColumn("email");
                    int year = query.getColumn("year");
                    cout << "id: " << id << ", name: " << name << ", email: " << email << ", year: " << year << endl;
                }
                if (!found) {cout << "No students found." << endl;}break;}

            case 7:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    }
    return 0;
}
