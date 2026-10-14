#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

namespace BankAccountType
{
    enum Type
    {
        chequing,
        savings,
        maxBankAccType
    };
}


class BankAccount
{
private:
    BankAccountType::Type m_accountType {};
    double m_balance {};
    
public:
    BankAccount(BankAccountType::Type accountType, double balance);
    
    double getBalance() const;
    void setBalance(double newBalance);
    
    void printBalance() const;
    
};


#endif