#include "BankAccount.h"

#include <iostream>

// test comment

BankAccount::BankAccount(BankAccountType::Type accountType, double balance) :
m_accountType{accountType},
m_balance{balance} {}

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
