#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string account_number;
    std::string pin_code;
    double balance;

public:
    Account(const std::string& acc_num, const std::string& pin, double initial_balance = 0.0);

    std::string getAccountNumber() const;
    bool authenticate(const std::string& pin) const;
    double getBalance() const;
    void deposit(double amount);
    bool withdraw(double amount);
};

#endif // ACCOUNT_H
