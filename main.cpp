#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

const int MAX_BOOKS = 100;

class Book {
private:
    string id, isbn, title, author, edition, publication, category;

public:
    void setDetails(string id, string isbn, string title, string author, string edition, string publication, string category) {
        this->id = id;
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }

    string getID() { return id; }
    string getCategory() { return category; }

    void display() {
        cout << id << "\t" << isbn << "\t" << title << "\t" << author << "\t"
             << edition << "\t" << publication << "\t" << category << endl;
    }

    void edit(string isbn, string title, string author, string edition, string publication, string category) {
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int count = 0;

    int findBookByID(const string& id) {
        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) return i;
        }
        return -1;
    }

    bool isValidCategory(const string& category) {
        return category == "Fiction" || category == "Non-fiction";
    }

    bool isValidID(const string& id) {
        if (id.empty()) return false;
        for (char c : id) {
            if (!isalnum(c)) return false;
        }
        return true;
    }

    void pause() {
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void addBook();
    void editBook();
    void searchBook();
    void deleteBook();
    void viewBooksByCategory();
    void viewAllBooks();
};

void Library::addBook() {
    string category;
    do {
        cout << "Enter category (Fiction / Non-fiction): ";
        getline(cin, category);
        if (!isValidCategory(category)) cout << "Category not found!\n";
    } while (!isValidCategory(category));

    string id;
    do {
        cout << "Enter Book ID (alphanumeric): ";
        getline(cin, id);
        if (!isValidID(id)) {
            cout << "Invalid ID! Use only letters and numbers.\n";
        } else if (findBookByID(id) != -1) {
            cout << "Duplicate ID! Enter another.\n";
        }
    } while (!isValidID(id) || findBookByID(id) != -1);

    string isbn, title, author, edition, publication;
    cout << "Enter ISBN: "; getline(cin, isbn);
    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Edition: "; getline(cin, edition);
    cout << "Enter Publication: "; getline(cin, publication);

    books[count++].setDetails(id, isbn, title, author, edition, publication, category);
    cout << "Book added successfully!\n";
    pause();
}

void Library::editBook() {
    string id;
    cout << "Enter Book ID to edit: ";
    getline(cin, id);

    int index = findBookByID(id);
    if (index == -1) {
        cout << "Book not found!\n";
        pause();
        return;
    }

    string isbn, title, author, edition, publication, category;
    cout << "Enter new ISBN: "; getline(cin, isbn);
    cout << "Enter new Title: "; getline(cin, title);
    cout << "Enter new Author: "; getline(cin, author);
    cout << "Enter new Edition: "; getline(cin, edition);
    cout << "Enter new Publication: "; getline(cin, publication);
    do {
        cout << "Enter new Category (Fiction / Non-fiction): ";
        getline(cin, category);
    } while (!isValidCategory(category));
    
    books[index].edit(isbn, title, author, edition, publication, category);
    cout << "Book edited successfully!\n";
    pause();
}

void Library::searchBook() {
    string id;
    cout << "Enter Book ID to search: ";
    getline(cin, id);

    int index = findBookByID(id);
    if (index == -1) cout << "Book not found!\n";
    else books[index].display();
    
    pause();
}

void Library::deleteBook() {
    string id;
    cout << "Enter Book ID to delete: ";
    getline(cin, id);

    int index = findBookByID(id);
    if (index == -1) {
        cout << "Book not found!\n";
        pause();
        return;
    }
    
    books[index].display();
    cout << "Confirm delete? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();
    if (confirm == 'y' || confirm == 'Y') {
        books[index] = books[--count];
        cout << "Book deleted successfully!\n";
    }
    pause();
}

void Library::viewBooksByCategory() {
    string category;
    do {
        cout << "Enter category (Fiction / Non-fiction): ";
        getline(cin, category);
    } while (!isValidCategory(category));

    cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
    for (int i = 0; i < count; i++) {
        if (books[i].getCategory() == category) books[i].display();
    }
    pause();
}

void Library::viewAllBooks() {
    if (count == 0) cout << "No books available.\n";
    else {
        cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
        for (int i = 0; i < count; i++) books[i].display();
    }
    pause();
}

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n====== Library Management System ======\n";
        cout << "1 - Add Book\n2 - Edit Book\n3 - Search Book\n4 - Delete Book\n5 - View Books by Category\n6 - View All Books\n7 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.editBook(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.deleteBook(); break;
            case 5: lib.viewBooksByCategory(); break;
            case 6: lib.viewAllBooks(); break;
        }
    } while (choice != 7);
    return 0;
}
