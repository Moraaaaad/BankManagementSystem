#include <iostream>   // Session 1: cin, cout
#include <string>     // Session 2: string type
using namespace std;

// ==================== Session 6: OOP ====================
class Account {
private:
    int accountNumber;      // Session 2: int
    string ownerName;       // Session 2: string
    double balance;         // Session 2: double
    bool isActive;          // Session 2: bool

public:
    Account() {
        accountNumber = -1;
        ownerName = "";
        balance = 0.0;
        isActive = false;
    }

    Account(int accNo, string name, double initialDeposit) {
        accountNumber = accNo;
        ownerName = name;
        balance = initialDeposit;
        isActive = true;
    }

    int getAccountNumber() { return accountNumber; }
    string getOwnerName() { return ownerName; }
    double getBalance() { return balance; }
    bool getStatus() { return isActive; }

    // Deposit money
    void deposit(double amount) {
        if (isActive && amount > 0) {
            balance += amount;
            cout << "Deposit successful. New Balance: " << balance << endl;
        } else {
            cout << "Deposit failed!" << endl;
        }
    }

    // Withdraw money
    void withdraw(double amount) {
        if (isActive && amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New Balance: " << balance << endl;
        } else {
            cout << "Withdrawal failed!" << endl;
        }
    }

    // Show account info
    void displayInfo() {
        cout << "Account No: " << accountNumber 
             << " | Owner: " << ownerName 
             << " | Balance: " << balance 
             << " | Status: " << (isActive ? "Active" : "Closed") 
             << endl;
    }
};

// ==================== Session 6: OOP (Bank Class) ====================
class Bank {
private:
    Account* accounts;   // Session 5: Pointer to dynamic array
    int size;
    int capacity;

public:
    Bank(int cap = 10) {
        capacity = cap;
        size = 0;
        accounts = new Account[capacity];
    }

    ~Bank() {
        delete[] accounts; // Session 4: dynamic memory management
    }

    // Session 4: Functions
    void createAccount(int accNo, string name, double initialDeposit) {
        if (size < capacity) {
            accounts[size] = Account(accNo, name, initialDeposit);
            size++;
            cout << "Account created successfully!" << endl;
        } else {
            cout << "Bank is full, cannot create more accounts." << endl;
        }
    }

    Account* findAccount(int accNo) {
        for (int i = 0; i < size; i++) {   // Session 3: Loop
            if (accounts[i].getAccountNumber() == accNo) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    void transfer(int fromAcc, int toAcc, double amount) {
        Account* sender = findAccount(fromAcc);
        Account* receiver = findAccount(toAcc);

        if (sender && receiver && sender->getBalance() >= amount) {
            sender->withdraw(amount);
            receiver->deposit(amount);
            cout << "Transfer successful!" << endl;
        } else {
            cout << "Transfer failed!" << endl;
        }
    }

    void showAllAccounts() {
        cout << "\n--- All Accounts ---" << endl;
        for (int i = 0; i < size; i++) {
            accounts[i].displayInfo();
        }
        cout << "---------------------" << endl;
    }
};

// ==================== Main Program ====================
int main() {
    Bank bank(100); // create bank with capacity of 100 accounts
    int choice;

    cout << "=== Welcome to Bank Management System ===" << endl;

    // Session 3: Loop for main menu
    do {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Show All Accounts\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            double initialDeposit;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter owner name: ";
            cin >> name;
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;
            bank.createAccount(accNo, name, initialDeposit);

        } else if (choice == 2) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter deposit amount: ";
            cin >> amount;
            Account* acc = bank.findAccount(accNo);
            if (acc) acc->deposit(amount);
            else cout << "Account not found!" << endl;

        } else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            Account* acc = bank.findAccount(accNo);
            if (acc) acc->withdraw(amount);
            else cout << "Account not found!" << endl;

        } else if (choice == 4) {
            int fromAcc, toAcc;
            double amount;
            cout << "Enter sender account number: ";
            cin >> fromAcc;
            cout << "Enter receiver account number: ";
            cin >> toAcc;
            cout << "Enter transfer amount: ";
            cin >> amount;
            bank.transfer(fromAcc, toAcc, amount);

        } else if (choice == 5) {
            bank.showAllAccounts();
        }

    } while (choice != 0);

    cout << "Thank you for using our Bank System!" << endl;
    return 0;
}
