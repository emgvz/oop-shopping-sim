#include "BankAccount.h"

#include <iostream>

std::string_view convertBankAccountTypeToStr(BankAccount::Type type)
{
    switch (type)
    {
    case BankAccount::chequing:
        return "Chequing";
    case BankAccount::savings:
        return "Savings";
    }
}


double BankAccount::getBalance() const
{
    return m_balance;
} 

void BankAccount::setBalance(double newBalance)
{
    m_balance = newBalance;
}

void BankAccount::printBalance() const
{
    std::cout << "$" << getBalance() << "\n";
    
    
}
