#include "Customer.h"
#include <iostream>

void Customer::depositToAccount(BankAccount::Type bankAccountType, double amountToDeposit)
{
    if (amountToDeposit >= 0)
    {
        // check bank account type
        BankAccount& account = { ( bankAccountType == BankAccount::chequing ) ? getChequingAccount()  : getSavingsAccount() };
        
        double newBalance {account.getBalance() + amountToDeposit };
        account.setBalance(newBalance);
    
        std::cout << "\nThe new balance for your " << (bankAccountType == BankAccount::chequing ? "Chequing" : "Savings") << " account is: " << "$" << account.getBalance() << '\n' << '\n'; 
    }
    else
    {
        std::cout << "\nI'm sorry. You can't deposit that amount" << '\n';
    }
}

void Customer::withdrawFromAccount(BankAccount::Type bankAccountType, double amountToWithdraw)
{
    // check bank account type
    BankAccount& account = { (bankAccountType == BankAccount::chequing ) ? getChequingAccount() : getSavingsAccount() };
    
    if (amountToWithdraw <= account.getBalance())
    {
        double newBalance {account.getBalance() - amountToWithdraw};
        account.setBalance(newBalance);
    
        std::cout << "\nThe new balance for your " << (bankAccountType == BankAccount::chequing ? "Chequing Account" : "Savings Account") << " is " << "$" << account.getBalance() << '\n' << '\n';
    }
    else
    {
        std::cout << "\nInsufficient amount to withdraw! Amount must be less than what you have in the account" << '\n' << '\n';
    }
}

void Customer::printInformationIndividual() const
{
    std::cout << "\n-------------------------------------\n";    
/*    std::cout << "ID: " << getId() << '\n';*/
    std::cout << "First name: " << getfName() << '\n';
    std::cout << "Last name: " << getlName() << '\n';
    std::cout << "Email: " << getEmail() << '\n';
    std::cout << "Phone number: " << getPhone() << '\n';
    std::cout << "Address: " << getAddress() << '\n';
    std::cout << "Occupation: " << getOccupation() << '\n';
    
    std::cout << "\nInitial checking balance: ";
    m_chequingAccount.printBalance();

    std::cout << "Initial savings balance: ";
    m_savingsAccount.printBalance();

    std::cout << "-------------------------------------\n\n";
}

void Customer::printInformation() const
{
    std::cout << "\n-------------------------------------\n";
    std::cout << "Hi " << getFullName() << '\n';
    std::cout << "ID: " << getId() << '\n';
    std::cout << "First name: " << getfName() << '\n';
    std::cout << "Last name: " << getlName() << '\n';
    std::cout << "Email: " << getEmail() << '\n';
    std::cout << "Phone number: " << getPhone() << '\n';
    std::cout << "Address: " << getAddress() << '\n';
    std::cout << "Occupation: " << getOccupation() << '\n';
    
    std::cout << "\nChecking account balance: "; 
    m_chequingAccount.printBalance();
    
    std::cout << "Savings account balance: ";
    m_savingsAccount.printBalance();
    
    std::cout << "-------------------------------------\n\n";
    
}

/* void Customer::printItemsBought() const
{

}

*/
