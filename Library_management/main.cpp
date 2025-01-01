#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // For find_if
#include <iomanip>   // For formatted output

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    string genre;
    int year;
};

// Global variables
vector<Book> library;
int nextId = 1;

// Function declarations
void loadLibrary();
void saveLibrary();
void addBook();
void listBooks();
void searchBooks();
void deleteBook();
void menu();

int main() {
    loadLibrary();
    menu();
    saveLibrary();
    return 0;
}

// Load library data from file
void loadLibrary() {
    ifstream file("library.txt");
    if (file.is_open()) {
        Book book;
        while (file >> book.id >> book.year >> ws && getline(file, book.title) && getline(file, book.author) && getline(file, book.genre)) {
            library.push_back(book);
            nextId = max(nextId, book.id + 1);
        }
        file.close();
    }
}

// Save library data to file
void saveLibrary() {
    ofstream file("library.txt");
    if (file.is_open()) {
        for (const auto &book : library) {
            file << book.id << " " << book.year << endl
                 << book.title << endl
                 << book.author << endl
                 << book.genre << endl;
        }
        file.close();
    }
}

// Add a new book to the library
void addBook() {
    Book book;
    book.id = nextId++;
    cin.ignore(); // Clear input buffer
    cout << "Enter book title: ";
    getline(cin, book.title);
    cout << "Enter author: ";
    getline(cin, book.author);
    cout << "Enter genre: ";
    getline(cin, book.genre);
    cout << "Enter publication year: ";
    cin >> book.year;

    library.push_back(book);
    cout << "Book added successfully!\n";
}

// List all books in the library
void listBooks() {
    if (library.empty()) {
        cout << "The library is empty.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(15) << "Genre" << setw(6) << "Year" << endl;
    cout << string(80, '-') << endl;
    for (const auto &book : library) {
        cout << left << setw(5) << book.id << setw(30) << book.title << setw(20) << book.author << setw(15) << book.genre << setw(6) << book.year << endl;
    }
}

// Search for books by title or author
void searchBooks() {
    string query;
    cin.ignore(); // Clear input buffer
    cout << "Enter title or author to search: ";
    getline(cin, query);

    bool found = false;
    for (const auto &book : library) {
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
            if (!found) {
                cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(15) << "Genre" << setw(6) << "Year" << endl;
                cout << string(80, '-') << endl;
            }
            found = true;
            cout << left << setw(5) << book.id << setw(30) << book.title << setw(20) << book.author << setw(15) << book.genre << setw(6) << book.year << endl;
        }
    }

    if (!found) {
        cout << "No books found matching your query.\n";
    }
}

// Delete a book by ID
void deleteBook() {
    int id;
    cout << "Enter the ID of the book to delete: ";
    cin >> id;

    auto it = find_if(library.begin(), library.end(), [id](const Book &book) { return book.id == id; });
    if (it != library.end()) {
        library.erase(it);
        cout << "Book deleted successfully!\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Main menu for user interaction
void menu() {
    int choice;
    do {
        cout << "\nLibrary Management Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. List All Books\n";
        cout << "3. Search Books\n";
        cout << "4. Delete Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                listBooks();
                break;
            case 3:
                searchBooks();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
