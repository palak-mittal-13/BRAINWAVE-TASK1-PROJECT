#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Account class to handle user account operations
class Account {
private:
    std::string account_number; // Unique account identifier
    std::string pin_code;       // PIN for authentication
    double balance;             // Account balance

public:
    // Constructor to initialize an account with an optional initial balance
    Account(const std::string& acc_num, const std::string& pin, double initial_balance = 0.0)
        : account_number(acc_num), pin_code(pin), balance(initial_balance) {}

    // Accessor to get the account number
    std::string getAccountNumber() const { return account_number; }

    // Method to check if the provided PIN matches the account's PIN
    bool authenticate(const std::string& pin) const { return pin_code == pin; }

    // Accessor to get the current balance
    double getBalance() const { return balance; }

    // Method to deposit a specified amount
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        } else {
            std::cerr << "Invalid deposit amount!\n";
        }
    }

    // Method to withdraw a specified amount
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        } else {
            std::cerr << "Invalid withdrawal amount or insufficient funds!\n";
            return false;
        }
    }
};

// ATM class to manage user interactions and operations
class ATM {
private:
    std::vector<std::shared_ptr<Account>> accounts; // List of accounts
    std::shared_ptr<Account> current_account;       // Currently authenticated account

    // Internal method to display the ATM menu
    void showMenu() const {
        std::cout << "\n===== ATM Menu =====\n"
                  << "1. Check Balance\n"
                  << "2. Deposit Money\n"
                  << "3. Withdraw Money\n"
                  << "4. Exit\n";
    }

    // Method to handle balance checking
    void checkBalance() const {
        std::cout << "Current Balance: $" << current_account->getBalance() << "\n";
    }

    // Method to handle money deposits
    void depositMoney() {
        double amount;
        std::cout << "Enter the amount to deposit: $";
        std::cin >> amount;
        current_account->deposit(amount);
        std::cout << "Deposited: $" << amount << "\n";
    }

    // Method to handle money withdrawals
    void withdrawMoney() {
        double amount;
        std::cout << "Enter the amount to withdraw: $";
        std::cin >> amount;
        if (current_account->withdraw(amount)) {
            std::cout << "Withdrawn: $" << amount << "\n";
        }
    }

    // Helper method to find an account by account number
    std::shared_ptr<Account> findAccount(const std::string& acc_number) {
        for (const auto& account : accounts) {
            if (account->getAccountNumber() == acc_number) {
                return account;
            }
        }
        return nullptr;
    }

public:
    // Constructor to initialize the ATM with some test accounts
    ATM() {
        accounts.emplace_back(std::make_shared<Account>("123456", "1111", 500.00));
        accounts.emplace_back(std::make_shared<Account>("789012", "2222", 1000.00));
    }

    // Method to start the ATM interface
    void start() {
        std::string acc_number;
        std::string pin;

        std::cout << "Welcome to the ATM Interface\n";
        std::cout << "Enter Account Number: ";
        std::cin >> acc_number;
        std::cout << "Enter PIN: ";
        std::cin >> pin;

        current_account = findAccount(acc_number);
        if (current_account && current_account->authenticate(pin)) {
            int choice;
            do {
                showMenu();
                std::cout << "Choose an option: ";
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        checkBalance();
                        break;
                    case 2:
                        depositMoney();
                        break;
                    case 3:
                        withdrawMoney();
                        break;
                    case 4:
                        std::cout << "Thank you for using the ATM. Goodbye!\n";
                        break;
                    default:
                        std::cerr << "Invalid option. Please try again.\n";
                }
            } while (choice != 4);
        } else {
            std::cerr << "Authentication failed. Please check your account number and PIN.\n";
        }
    }
};

// Main function to launch the ATM interface
int main() {
    ATM atm;
    atm.start();
    return 0;
}
