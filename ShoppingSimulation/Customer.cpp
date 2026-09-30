#include "Customer.h"
#include <iostream>

void Customer::depositToAccount(BankAccountType::Type bankAccountType, double amountToDeposit)
{
    if (amountToDeposit >= 0)
    {
        // check bank account type
        BankAccount& account = { ( bankAccountType == BankAccountType::chequing ) ? getChequingAccount()  : getSavingsAccount() };
        double newBalance {account.getBalance() + amountToDeposit };
        account.setBalance(newBalance);
    
        std::cout << "The new balance for your " << (bankAccountType == BankAccountType::chequing ? "Chequing" : "Savings") << " account is: " << "$" << account.getBalance() << '\n' << '\n'; 
    }
    else
    {
        std::cout << "I'm sorry. You can't deposit that amount" << '\n';
    }
}

void Customer::withdrawFromAccount(BankAccountType::Type bankAccountType, double amountToWithdraw)
{
    // check bank account type
    BankAccount& account = { (bankAccountType == BankAccountType::chequing ) ? getChequingAccount() : getSavingsAccount() };
    
    if (amountToWithdraw <= account.getBalance())
    {
        double newBalance {account.getBalance() - amountToWithdraw};
        account.setBalance(newBalance);
    
        std::cout << "The new balance for your " << (bankAccountType == BankAccountType:: chequing ? "chequing" : "savings") << " is " << "$" << account.getBalance() << '\n' << '\n';
    }
    else
    {
        std::cout << "Insufficient amount to withdraw! Amount must be less than what you have in the account" << '\n' << '\n';
    }
}

void Customer::printInformationInvidual() const
{
    std::cout << "\n-------------------------------------\n";
    std::cout << "Hi " << getFullName() << ". These are your details." << '\n';
    
    std::cout << "ID: " << getId() << '\n';
    std::cout << "First name: " << getfName() << '\n';
    std::cout << "Last name: " << getlName() << '\n';
    std::cout << "Email: " << getEmail() << '\n';
    std::cout << "Phone number: " << getPhone() << '\n';
    std::cout << "Address: " << getAddress() << '\n';
    std::cout << "Occupation: " << getOccupation() << '\n';
    
    std::cout << "\nInitial checking balance: $" << m_chequingAccount.getBalance() << '\n';
    std::cout << "Initial savings balance: $" << m_savingsAccount.getBalance();
    std::cout << "\n-------------------------------------\n";

    
    std::cout << '\n';
    
}

void Customer::printInformation() const
{
    std::cout << "\n-------------------------------------\n";
    std::cout << "Hi " << getFullName() << ". These are your details." << '\n';
    
    std::cout << "ID: " << getId() << '\n';
    std::cout << "First name: " << getfName() << '\n';
    std::cout << "Last name: " << getlName() << '\n';
    std::cout << "Email: " << getEmail() << '\n';
    std::cout << "Phone number: " << getPhone() << '\n';
    std::cout << "Address: " << getAddress() << '\n';
    std::cout << "Occupation: " << getOccupation() << '\n';
    
    std::cout << "\nChecking account balance: $" << m_chequingAccount.getBalance() << '\n';
    std::cout << "Savings account balance: $" << m_savingsAccount.getBalance();
    std::cout << "\n-------------------------------------\n";

    
    std::cout << '\n';
    
}
