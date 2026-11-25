#include "Customer.h"
#include "Product.h"
#include <iostream>
#include "iomanip"
#include "format"

bool Customer::depositToAccount(BankAccount::Type bankAccountType, double amountToDeposit)
{
    if (amountToDeposit >= 0)
    {
        // check bank account type
        BankAccount& account = { ( bankAccountType == BankAccount::chequing ) ? getChequingAccount()  : getSavingsAccount() };
        
        double newBalance {account.getBalance() + amountToDeposit };
        account.setBalance(newBalance);
    
        std::cout << "\nThe new balance for your " << (bankAccountType == BankAccount::chequing ? "Chequing" : "Savings") << " account is: " << "$" << account.getBalance() << '\n' << '\n'; 
        return true;
    }
    else
    {
        std::cout << "\nI'm sorry. You can't deposit that amount" << '\n';
        return false;
    }
}

bool Customer::withdrawFromAccount(BankAccount::Type bankAccountType, double amountToWithdraw)
{
    // check bank account type
    BankAccount& account = { (bankAccountType == BankAccount::chequing ) ? getChequingAccount() : getSavingsAccount() };
    
    if (amountToWithdraw <= account.getBalance())
    {
        double newBalance {account.getBalance() - amountToWithdraw};
        account.setBalance(newBalance);
    
        std::cout << "\nThe new balance for your " << (bankAccountType == BankAccount::chequing ? "Chequing Account" : "Savings Account") << " is " << "$" << account.getBalance() << '\n' << '\n';
        return true;
    }
    else
    {
        std::cout << "\nInsufficient funds! Please check the process amount again!" << '\n' << '\n';
        return false;
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

void Customer::printBalances() const
{
    std::cout << "\n-------------------------------------\n";
    std::cout << "ID: " << getId() << '\n';
    std::cout << "First name: " << getfName() << '\n';
    std::cout << "Last name: " << getlName() << '\n';
    std::cout << "\nChecking account balance: ";
    m_chequingAccount.printBalance();

    std::cout << "Savings account balance: ";
    m_savingsAccount.printBalance();

    std::cout << "-------------------------------------\n\n";

}

void Customer::addPurchasedItems(Product product, int custQtyPurchase)
{
    product.updateQuantity(custQtyPurchase);
    
    m_productsOwned.push_back(product);
}

void Customer::addTransactionItems(Transaction transaction)
{
    m_custTransaction.push_back(transaction);
}

void Customer::printItemsBought() const
{
    if (m_productsOwned.empty())
    {
        std::cout << "There are no products owned." << '\n' << '\n';
        return;
    }

    std::cout << "Hi! " << getFullName() << ". These are your products" << '\n' << '\n';


    std::cout << std::left << std::setw(10) << "ID";
    std::cout << std::setw(20) << "Product Name";
    std::cout << std::setw(15) << "Type";
    std::cout << std::setw(15) << "Price";
    std::cout << std::right << std::setw(15) << "Quantity";
    std::cout << std::right << std::setw(15) << "Total" << '\n';

    std::cout << "==========================================================================================" << "\n" << "\n";

    for (const Product& p : m_productsOwned)
    {
        p.printProductsCust();
        std::cout << '\n';
    }

    std::cout << "==========================================================================================" << "\n" << "\n";
}

void Customer::printTransactionBank() const
{
    if (m_custTransaction.empty())
    {
        std::cout << "There are no transactions available." << '\n' << '\n';
        return;
    }

    std::cout << "Viewing transactions of " << getFullName() << '\n' << '\n';

    std::cout << std::left << std::setw(10) << "ID";
    std::cout << std::setw(20) << "Account Type";
    std::cout << std::setw(20) << "Transaction Type";
    std::cout << std::right << std::setw(20) << "Transaction Amount";
    std::cout << std::right << std::setw(15) << "Balance";
    std::cout << std::right << std::setw(15) << "Status" << '\n';


    std::cout << "====================================================================================================" << "\n" << "\n";

    for (const Transaction& t : m_custTransaction)
    {
        t.printTransactionBank();
        std::cout << '\n';
    }

    std::cout << "====================================================================================================" << "\n" << "\n";

}

void Customer::printTransactionPurchase() const
{
    if (m_productsOwned.empty())
    {
        std::cout << "There are no transactions available." << '\n' << '\n';
        return;
    }

    std::cout << std::left << std::setw(10) << "ID";
    std::cout << std::left << std::setw(20) << "Account Type";
    std::cout << std::left << std::setw(20) << "Transaction Type";
    std::cout << std::left << std::setw(20) << "Product Type";
    std::cout << std::right << std::setw(15) << "Product Name";
    std::cout << std::right << std::setw(15) << "Unit Price";
    std::cout << std::right << std::setw(15) << "Quantity Bought";
    std::cout << std::right << std::setw(15) << "Transaction Amount";
    std::cout << std::right << std::setw(15) << "Balance";
    std::cout << std::right << std::setw(10) << "Status" << '\n';

    std::cout << "====================================================================================================" << "\n" << "\n";

    for (const Transaction& t : m_custTransaction)
    {
        t.printTransactionPurchase();
        std::cout << '\n';
    }

    std::cout << "====================================================================================================" << "\n" << "\n";

}




