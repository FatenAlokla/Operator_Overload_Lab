#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double* balance;

public:
    // Default constructor
    BankAccount() {
        accountNumber = "000000";
        accountHolderName = "Unknown";
        balance = new double(0);
    }

    // Parameterized constructor
    BankAccount(std::string accNum, std::string holderName, double bal) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance = new double(bal);
    }

    // Destructor
    ~BankAccount() {
        delete balance;
        balance = nullptr;
    }

    // Constructor that duplicates another account's data
    BankAccount(const BankAccount& other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = new double(*other.balance);
    }

    // Assignment operator
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            accountNumber = other.accountNumber;
            accountHolderName = other.accountHolderName;
            delete balance;
            balance = new double(*other.balance);
        }
        return *this;
    }

    // Operator += (Deposit)
    BankAccount& operator+=(double amount) {
        if (amount > 0) {
            *balance += amount;
        }
        return *this;
    }

    // Operator -= (Withdraw)
    BankAccount& operator-=(double amount) {
        if (amount > 0 && *balance >= amount) {
            *balance -= amount;
        } else {
            std::cout << "Insufficient funds or invalid amount.\n";
        }
        return *this;
    }

    // Comparison operators
    bool operator==(const BankAccount& other) const {
        return accountNumber == other.accountNumber;
    }

    bool operator<(const BankAccount& other) const {
        return *balance < *other.balance;
    }

    bool operator>(const BankAccount& other) const {
        return *balance > *other.balance;
    }

    // Getters
    std::string getAccountNumber() const {
        return accountNumber;
    }

    std::string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return *balance;
    }

    // Setter
    void setAccountHolderName(const std::string& name) {
        accountHolderName = name;
    }

    // Static function to print account details
    static void printAccount(const BankAccount& account) {
        std::cout << "Account Number: " << account.accountNumber << "\n";
        std::cout << "Account Holder: " << account.accountHolderName << "\n";
        std::cout << "Balance: $" << *account.balance << "\n";
    }

    // Static function to create account from user input
    static BankAccount createAccountFromInput() {
        std::string accNum, name;
        double bal;

        std::cout << "Enter account number: ";
        std::cin >> accNum;
        std::cin.ignore();

        std::cout << "Enter account holder name: ";
        std::getline(std::cin, name);

        std::cout << "Enter initial balance: ";
        std::cin >> bal;

        return BankAccount(accNum, name, bal);
    }
};

int main() {
    std::vector<BankAccount> accounts;
    int choice;

    do {
        std::cout << "\n=== Bank Account Menu ===\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Display Account Info\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Withdraw\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) { // Create Account
            BankAccount newAcc = BankAccount::createAccountFromInput();
            accounts.push_back(newAcc);
            std::cout << "Account created successfully!\n";
        }
        else if (choice == 2) { // Display Account Info
            std::string accNum;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    BankAccount::printAccount(acc);
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Account not found.\n";
        }
        else if (choice == 3) { // Deposit
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    std::cout << "Enter deposit amount: ";
                    std::cin >> amount;
                    acc += amount; // uses operator+=
                    std::cout << "Deposit successful. New balance: $" << acc.getBalance() << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Account not found.\n";
        }
        else if (choice == 4) { // Withdraw
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> amount;
                    acc -= amount; // uses operator-=
                    std::cout << "New balance: $" << acc.getBalance() << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Account not found.\n";
        }
        else if (choice == 5) {
            std::cout << "Exiting program...\n";
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
