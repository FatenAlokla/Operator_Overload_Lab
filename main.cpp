#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double* balance;

public:
    // Default constructor
    BankAccount() {
        accountNumber = "000000";
        accountHolderName = "Unknown";
        balance =  new double(0);
    }

    // Parameterized constructor
    BankAccount(string accNum, string holderName, double bal) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance =  new double(bal);
    }

    // Getters
    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    // Setter
    void setAccountHolderName(const string& name) {
        accountHolderName = name;
    }

    // Deposit
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Withdraw
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

int main() {
    vector<BankAccount> accounts;
    int choice;

    do {
        cout << "\n=== Bank Account Menu ===\n";
        cout << "1. Create Account\n";
        cout << "2. Display Account Info\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); //

        if (choice == 1) { // Create Account
            string accNum, name;
            double bal;

            cout << "Enter account number: ";
            cin >> accNum;
            cin.ignore();

            cout << "Enter account holder name: ";
            getline(cin, name);

            cout << "Enter initial balance: ";
            cin >> bal;

            BankAccount newAcc(accNum, name, bal);
            accounts.push_back(newAcc);

            cout << "Account created successfully!\n";
        }

        else if (choice == 2) { // Display Account Info
            string accNum;
            cout << "Enter account number: ";
            cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    cout << "\nAccount Number: " << acc.getAccountNumber() << "\n";
                    cout << "Account Holder: " << acc.getAccountHolderName() << "\n";
                    cout << "Balance: $" << acc.getBalance() << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 3) { // Deposit
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    acc.deposit(amount);
                    cout << "Deposit successful. New balance: $" << acc.getBalance() << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 4) { // Withdraw
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    if (acc.withdraw(amount)) {
                        cout << "Withdrawal successful. New balance: $" << acc.getBalance() << "\n";
                    } else {
                        cout << "Insufficient funds or invalid amount.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 5) { // Exit
            cout << "Exiting program...\n";
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
