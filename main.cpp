#include <iostream>
#include <string>

using namespace std;

// Functions declarations
bool login();
void showMenu();
void checkBalance(int balance);
void deposit(int &balance, string history[], int &count);
void withdraw(int &balance, string history[], int &count);
void showHistory(string history[], int count);

int main() {
    // Check PIN first
    if (login() == false) {
        cout << "ATM Blocked! Too many wrong attempts." << endl;
        return 0;
    }

    int balance = 0;
    string transactionHistory[100];
    int transactionCount = 0;
    int choice;

    // Main program loop
    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            checkBalance(balance);
        } 
        else if (choice == 2) {
            deposit(balance, transactionHistory, transactionCount);
        } 
        else if (choice == 3) {
            withdraw(balance, transactionHistory, transactionCount);
        } 
        else if (choice == 4) {
            showHistory(transactionHistory, transactionCount);
        } 
        else if (choice == 5) {
            cout << "Thank you for using BK ATM. Goodbye!" << endl;
        } 
        else {
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function to check PIN (Maximum 3 attempts)
bool login() {
    int correctPIN = 12345;
    int enteredPIN;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter your PIN: ";
        cin >> enteredPIN;

        if (enteredPIN == correctPIN) {
            cout << "Login Successful!" << endl;
            return true;
        } else {
            attempts++;
            cout << "Wrong PIN! Attempts used: " << attempts << "/3" << endl;
        }
    }
    return false;
}

// Function to display options
void showMenu() {
    cout << "\n--- ATM MENU ---" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transaction History" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
}

void checkBalance(int balance) {
    cout << "Current Balance: " << balance << " FRW" << endl;
}

void deposit(int &balance, string history[], int &count) {
    int amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount > 0) {
        balance = balance + amount;
        cout << "Deposit successful!" << endl;
        // Save to history array
        history[count] = "Deposited: " + to_string(amount) + " FRW";
        count++;
    } else {
        cout << "Invalid amount!" << endl;
    }
}

void withdraw(int &balance, string history[], int &count) {
    int amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount > balance) {
        cout << "Insufficient balance!" << endl;
    } else if (amount <= 0) {
        cout << "Invalid amount!" << endl;
    } else {
        balance = balance - amount;
        cout << "Withdrawal successful!" << endl;
        // Save to history array
        history[count] = "Withdrew: " + to_string(amount) + " FRW";
        count++;
    }
}

void showHistory(string history[], int count) {
    cout << "\n--- Transaction History ---" << endl;
    if (count == 0) {
        cout << "No transactions yet." << endl;
    } else {
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << history[i] << endl;
        }
    }
}