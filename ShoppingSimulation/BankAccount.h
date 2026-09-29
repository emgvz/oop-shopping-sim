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
    BankAccount(BankAccountType::Type accountType, double balance) :
    m_accountType(accountType),
    m_balance(balance) {}
    
    double getBalance() const;
    void setBalance(double newBalance);
    
};


#endif