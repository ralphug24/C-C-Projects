#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Expense {
    int id;
    string category;
    double amount;
    string date;
};

// Global variables
vector<Expense> expenses;
int nextId = 1;

// Function declarations
void loadExpenses();
void saveExpenses();
void addExpense();
void viewExpenses();
void deleteExpense();
void menu();

int main() {
    loadExpenses();
    menu();
    saveExpenses();
    return 0;
}

// Load expenses from file
void loadExpenses() {
    ifstream file("expenses.txt");
    if (file.is_open()) {
        Expense exp;
        while (file >> exp.id >> exp.amount >> exp.date >> ws && getline(file, exp.category)) {
            expenses.push_back(exp);
            nextId = max(nextId, exp.id + 1);
        }
        file.close();
    }
}

// Save expenses to file
void saveExpenses() {
    ofstream file("expenses.txt");
    if (file.is_open()) {
        for (const auto &exp : expenses) {
            file << exp.id << " " << exp.amount << " " << exp.date << " " << exp.category << endl;
        }
        file.close();
    }
}

// Add a new expense
void addExpense() {
    Expense exp;
    exp.id = nextId++;
    cout << "Enter category: ";
    cin.ignore();
    getline(cin, exp.category);
    cout << "Enter amount: ";
    cin >> exp.amount;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> exp.date;
    expenses.push_back(exp);
    cout << "Expense added successfully!\n";
}

// View all expenses
void viewExpenses() {
    if (expenses.empty()) {
        cout << "No expenses to display.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Category" << setw(10) << "Amount" << setw(12) << "Date" << endl;
    cout << string(42, '-') << endl;
    for (const auto &exp : expenses) {
        cout << left << setw(5) << exp.id << setw(15) << exp.category << setw(10) << exp.amount << setw(12) << exp.date << endl;
    }
}

// Delete an expense
void deleteExpense() {
    int id;
    cout << "Enter the ID of the expense to delete: ";
    cin >> id;
    auto it = find_if(expenses.begin(), expenses.end(), [id](const Expense &exp) { return exp.id == id; });
    if (it != expenses.end()) {
        expenses.erase(it);
        cout << "Expense deleted successfully!\n";
    } else {
        cout << "Expense not found.\n";
    }
}

// Menu for user interaction
void menu() {
    int choice;
    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Delete Expense\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                deleteExpense();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}
