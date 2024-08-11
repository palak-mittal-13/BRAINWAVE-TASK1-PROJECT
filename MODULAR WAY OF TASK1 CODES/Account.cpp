#include "Account.h"
#include <iostream>

// Constructor
Account::Account(const std::string& acc_num, const std::string& pin, double initial_balance)
    : account_number(acc_num), pin_code(pin), balance(initial_balance) {}

// Get the account number
std::string Account::getAccountNumber() const {
    return account_number;
}

// Authenticate the user with the PIN
bool Account::authenticate(const std::string& pin) const {
    return pin_code == pin;
}

// Get the current balance
double Account::getBalance() const {
    return balance;
}

// Deposit money into the account
void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        std::cerr << "Invalid deposit amount!\n";
    }
}

// Withdraw money from the account
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    } else {
        std::cerr << "Invalid withdrawal amount or insufficient funds!\n";
        return false;
    }
}
