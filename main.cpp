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

    // Copy constructor
    BankAccount(const BankAccount& other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = new double(*other.balance);
    }

    // Copy assignment operator
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
};
