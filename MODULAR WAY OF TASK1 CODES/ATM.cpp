#include "ATM.h"
#include <iostream>

// Constructor to initialize the ATM with some test accounts
ATM::ATM() {
    accounts.emplace_back(std::make_shared<Account>("123456", "1111", 500.00));
    accounts.emplace_back(std::make_shared<Account>("789012", "2222", 1000.00));
}

// Internal method to display the ATM menu
void ATM::showMenu() const {
    std::cout << "\n===== ATM Menu =====\n"
              << "1. Check Balance\n"
              << "2. Deposit Money\n"
              << "3. Withdraw Money\n"
              << "4. Exit\n";
}

// Method to handle balance checking
void ATM::checkBalance() const {
    std::cout << "Current Balance: $" << current_account->getBalance() << "\n";
}

// Method to handle money deposits
void ATM::depositMoney() {
    double amount;
    std::cout << "Enter the amount to deposit: $";
    std::cin >> amount;
    current_account->deposit(amount);
    std::cout << "Deposited: $" << amount << "\n";
}

// Method to handle money withdrawals
void ATM::withdrawMoney() {
    double amount;
    std::cout << "Enter the amount to withdraw: $";
    std::cin >> amount;
    if (current_account->withdraw(amount)) {
        std::cout << "Withdrawn: $" << amount << "\n";
    }
}

// Helper method to find an account by account number
std::shared_ptr<Account> ATM::findAccount(const std::string& acc_number) {
    for (const auto& account : accounts) {
        if (account->getAccountNumber() == acc_number) {
            return account;
        }
    }
    return nullptr;
}

// Method to start the ATM interface
void ATM::start() {
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
