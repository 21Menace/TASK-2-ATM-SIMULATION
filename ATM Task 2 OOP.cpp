//Suleiman Muriuki
//DSE-02-8564/2024

#include <iostream>
#include <string>
using namespace std;

// Base class "Account"
class Account {
private:
    string accountNumber;
    string pin;
    double balance;

public:
    // Constructor to initialize account details
    Account(string accNum, string pinCode, double initialBalance) {
        accountNumber = accNum;
        pin = pinCode;
        balance = initialBalance;
    }

    // Verifying if PIN is correct
    bool verifyPin(string enteredPin) {
        return enteredPin == pin;
    }

    // Deposit an amount into the account
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount. Please enter a positive value." << endl;
        }
    }

    // Withdrawal an amount from the account
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount. Please enter a positive value." << endl;
            return false;
        } else if (amount > balance) {
            cout << "Insufficient balance. Available balance: $" << balance << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrew: $" << amount << endl;
            return true;
        }
    }

    // Checking the current balance
    double getBalance() const {
        return balance;
    }
};

// Abstract base class for a transaction
class Transaction {
public:
    virtual void execute(Account &account) = 0; //executing transaction
};

// Derived class for deposit
class Deposit : public Transaction {
private:
    double amount;

public:
    // Constructor to set deposit amount
    Deposit(double amt) : amount(amt) {}

    // Depositing by calling deposit method
    void execute(Account &account) override {
        account.deposit(amount);
    }
};

// Derived class for withdrawal
class Withdrawal : public Transaction {
private:
    double amount;

public:
    // Set withdrawal amount
    Withdrawal(double amt) : amount(amt) {}

    // Withdrawal by calling withdraw method
    void execute(Account &account) override {
        account.withdraw(amount);
    }
};

// ATM class to interact with the ATM system
class ATM {
private:
    Account *currentAccount; // Pointer to the current user's account

public:
    // Constructor to initialize the pointer
    ATM() : currentAccount(NULL) {}

    // Insert card and verify PIN
    bool insertCard(Account &account, string enteredPin) {
        if (account.verifyPin(enteredPin)) {
            currentAccount = &account;
            cout << "PIN Verified" << endl;
            return true;
        } else {
            cout << "Incorrect PIN. Try again!" << endl;
            return false;
        }
    }

    // Method to perform a transaction
    void performTransaction(Transaction &transaction) {
        if (currentAccount != NULL) {
            transaction.execute(*currentAccount);
        } else {
            cout << "No account authenticated." << endl;
        }
    }

    // Method to check the balance
    void checkBalance() {
        if (currentAccount != NULL) {
            cout << "Current Balance: $" << currentAccount->getBalance() << endl;
        } else {
            cout << "No account authenticated." << endl;
        }
    }

    // Method to remove card
    void removeCard() {
        currentAccount = NULL;
        cout << "Session ended. Please remove your card." << endl;
    }
};

int main() {
    string accNum, pin;
    double initialBalance;

    // Prompting the user to enter account details
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Set your PIN: ";
    cin >> pin;
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;

    // Creating an account with the entered details
    Account myAccount(accNum, pin, initialBalance);

    // Creating an ATM instance
    ATM myATM;

    // Authenticate with PIN (single attempt)
    string enteredPin;
    cout << "Enter your PIN: ";
    cin >> enteredPin;

    if (myATM.insertCard(myAccount, enteredPin)) {
        int choice;
        do {
            cout << "\n--- ATM Menu ---\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Check Balance\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                double depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                Deposit depositTransaction(depositAmount);
                myATM.performTransaction(depositTransaction);
                break;
            }
            case 2: {
                double withdrawalAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawalAmount;
                Withdrawal withdrawTransaction(withdrawalAmount);
                myATM.performTransaction(withdrawTransaction);
                break;
            }
            case 3:
                myATM.checkBalance();
                break;
            case 4:
                cout << "Exiting the session." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);

        myATM.removeCard();
    } else {
        cout << "Authentication failed. Exiting the program." << endl;
    }

    return 0;
}

