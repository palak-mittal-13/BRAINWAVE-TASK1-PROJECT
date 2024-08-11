#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include <vector>
#include <memory>

class ATM {
private:
    std::vector<std::shared_ptr<Account>> accounts;
    std::shared_ptr<Account> current_account;

    void showMenu() const;
    void checkBalance() const;
    void depositMoney();
    void withdrawMoney();
    std::shared_ptr<Account> findAccount(const std::string& acc_number);

public:
    ATM();
    void start();
};

#endif // ATM_H
