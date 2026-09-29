#include "BankAccount.h"

#include <iostream>

double BankAccount::getBalance() const
{
    return m_balance;
} 

void BankAccount::setBalance(double newBalance)
{
    m_balance = newBalance;
} 