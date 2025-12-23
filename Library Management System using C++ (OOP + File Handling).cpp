#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int i, string t, string a, bool is=false) {
        id = i;
        title = t;
        author = a;
        issued = is;
    }
};

vector<Book> books;

void saveToFile() {
    ofstream file("library.txt");
    for (auto &b : books) {
        file << b.id << " " << b.title << " " << b.author << " " << b.issued << endl;
    }
    file.close();
}

void loadFromFile() {
    ifstream file("library.txt");
    books.clear();
    int id; string title, author; bool issued;
    while (file >> id >> title >> author >> issued) {
        books.push_back(Book(id, title, author, issued));
    }
    file.close();
}

void addBook() {
    int id;
    string title, author;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Title: ";
    cin >> title;
    cout << "Enter Author: ";
    cin >> author;

    books.push_back(Book(id, title, author));
    saveToFile();
    cout << "Book Added Successfully\n";
}

void viewBooks() {
    loadFromFile();
    for (auto &b : books) {
        cout << "ID: " << b.id
             << " Title: " << b.title
             << " Author: " << b.author
             << " Issued: " << (b.issued ? "Yes" : "No") << endl;
    }
}

void issueBook() {
    loadFromFile();
    int id;
    cout << "Enter Book ID to Issue: ";
    cin >> id;
    for (auto &b : books) {
        if (b.id == id && !b.issued) {
            b.issued = true;
            saveToFile();
            cout << "Book Issued Successfully\n";
            return;
        }
    }
    cout << "Book Not Available\n";
}

void returnBook() {
    loadFromFile();
    int id;
    cout << "Enter Book ID to Return: ";
    cin >> id;
    for (auto &b : books) {
        if (b.id == id && b.issued) {
            b.issued = false;
            saveToFile();
            cout << "Book Returned Successfully\n";
            return;
        }
    }
    cout << "Invalid Book ID\n";
}

int main() {
    int choice;
    do {
        cout << "\n1.Add Book\n2.View Books\n3.Issue Book\n4.Return Book\n0.Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
        }
    } while (choice != 0);

    return 0;
}
