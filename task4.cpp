#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string note;

    Transaction(string t, double a, string n = "") {
        type = t;
        amount = a;
        note = n;
    }

    void display() const {
        cout << setw(10) << type << " | " << setw(10) << amount << " | " << note << endl;
    }
};

class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(string accNum) {
        accountNumber = accNum;
        balance = 0.0;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back(Transaction("Deposit", amount));
            cout << "Deposit successful.\n";
        } else {
            cout << "Invalid amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            history.push_back(Transaction("Withdraw", amount));
            cout << "Withdrawal successful.\n";
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }
    }

    bool transfer(Account& receiver, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            receiver.balance += amount;

            history.push_back(Transaction("Transfer To", amount, receiver.getAccountNumber()));
            receiver.history.push_back(Transaction("Transfer From", amount, accountNumber));

            cout << "Transfer successful.\n";
            return true;
        } else {
            cout << "Transfer failed: insufficient funds or invalid amount.\n";
            return false;
        }
    }

    void showTransactions() const {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        cout << setw(10) << "Type" << " | " << setw(10) << "Amount" << " | Note\n";
        cout << "-------------------------------------------\n";
        for (const auto& tx : history) {
            tx.display();
        }
    }

    void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber
             << "\nCurrent Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

class Customer {
private:
    string name;
    string customerID;
    Account* account;

public:
    Customer(string n, string id, string accNum) {
        name = n;
        customerID = id;
        account = new Account(accNum);
    }

    ~Customer() {
        delete account;
    }

    void showCustomerInfo() const {
        cout << "\nCustomer ID: " << customerID
             << "\nName: " << name;
        account->displayAccountInfo();
    }

    Account* getAccount() {
        return account;
    }
};

int main() {
    Customer customer1("Alice", "C101", "A101");
    Customer customer2("Bob", "C102", "A102");

    int choice;
    double amount;

    do {
        cout << "\n=== Banking System Menu ===\n";
        cout << "1. View Customer Info\n";
        cout << "2. Deposit to Alice\n";
        cout << "3. Withdraw from Alice\n";
        cout << "4. Transfer from Alice to Bob\n";
        cout << "5. Show Alice's Transactions\n";
        cout << "6. Show Bob's Transactions\n";
        cout << "7. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                customer1.showCustomerInfo();
                customer2.showCustomerInfo();
                break;

            case 2:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                if (cin.fail() || amount <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid amount.\n";
                    break;
                }
                customer1.getAccount()->deposit(amount);
                break;

            case 3:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if (cin.fail() || amount <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid amount.\n";
                    break;
                }
                customer1.getAccount()->withdraw(amount);
                break;

            case 4:
                cout << "Enter amount to transfer: ";
                cin >> amount;
                if (cin.fail() || amount <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid amount.\n";
                    break;
                }
                customer1.getAccount()->transfer(*customer2.getAccount(), amount);
                break;

            case 5:
                customer1.getAccount()->showTransactions();
                break;

            case 6:
                customer2.getAccount()->showTransactions();
                break;

            case 7:
                cout << "Thank you for using the banking system!\n";
                break;

            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 7);

    return 0;
}
