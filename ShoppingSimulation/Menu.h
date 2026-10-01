#pragma once
#include <vector>
#include "Customer.h"

void ignoreLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// create customer stuffs

std::string createFName()
{
    std::string newfirstName{};

    std::cout << "What is your first name?: ";
    std::cin >> newfirstName;

    // validation

    return newfirstName;
}

std::string createLName()
{
    std::string newLastName{};

    std::cout << "What is your last name?: ";
    std::cin >> newLastName;

    // validation

    return newLastName;
}

std::string createEmail()
{
    std::string newEmail{};

    std::cout << "What is your email?: ";
    std::cin >> newEmail;

    return newEmail;
}

std::string createPhoneNumber()
{
    std::string newPhoneNumber{};

    std::cout << "What is your phone number?: ";
    std::cin >> newPhoneNumber;

    return newPhoneNumber;
}

std::string createAddress()
{
    std::string newAddress{};

    std::cout << "What is your address?: ";
    std::getline(std::cin >> std::ws, newAddress);

    return newAddress;
}

std::string createOccupation()
{
    std::string newOccupation{};

    std::cout << "What is your occupation?: ";
    std::getline(std::cin >> std::ws, newOccupation);

    return newOccupation;
}

void viewAccountDetails(const std::vector<Customer>& customers)
{
    // print all customers details
    if (customers.size() == 0)
    {
        std::cout << "There are no customers available to view " << '\n' << '\n';
        return;
    }

    for (const Customer& customer : customers)
    {
        customer.printInformationInvidual();
        std::cout << '\n';
    }
}


Customer* findCustomerByAccountId(std::vector<Customer>& customers, int customerId)
{
    for (Customer& customer : customers)
    {
        if (customer.getId() == customerId)
        {
            std::cout << "Account found!" << '\n';
            return &customer;
        }
        
    }
    
    std::cout << "Account not found! Please try again!" << '\n';
    return nullptr;
}

int getAccountTypeChoice(int option)
{
    while (true)
    {
        int accountTypeChoice{};
        
        std::cout << "1. Chequing Account" << '\n';
        std::cout << "2. Savings Account" << '\n';

        std::cout << "Which account do you want to " << (option == 1 ? "deposit to" : "withdraw from") << " (1 for Chequing, 2 for Savings)?: ";
        std::cin >> accountTypeChoice;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Only choose from 1 for Chequing or 2 for Savings." << '\n';
            continue;
        }
        
        // catch values that are higher 
        
        return accountTypeChoice;
    }
}

double getAmount(int accountTypeChoice, int action)
{
    double amount{};
    
    while (true)
    {
        std::cout << "Enter the amount to be " << (action == 1 ? "deposited to" : "withdrawn from" ) << " your " << (accountTypeChoice == 1 ? "chequing" : "savings") << " account: ";
        std::cin >> amount;
        
        if (!std::cin)
        {
            std::cout << "Only enter numerical $$$ amount!" << '\n';
            ignoreLine();
            continue;
        } 
        
        return amount;

    }
}

int getAccountID()
{
    int accountID{};
    
    while (true)
    {
        std::cout << "What is your Account ID:? ";
        std::cin >> accountID;
            
        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Please only input numerical numbers: " << '\n';
            continue;
        }
        
        return accountID;
    }
}


void handleCustomerAction(int action, int accountTypeChoice, Customer* customer, double processAmount)
{
    BankAccountType::Type bankAccountType{ accountTypeChoice == 1 ? BankAccountType::chequing : BankAccountType::savings };
    
    switch (action)
    {
        case 1: // deposit
        customer->depositToAccount(bankAccountType, processAmount);
        break;
        
        case 2: // withdraw
        customer->withdrawFromAccount(bankAccountType, processAmount);
        break;
    }
}

void handleTransactionProcess(std::vector<Customer>& customers, int action)
{
    while (true)
    {
        int accountID(getAccountID());
        Customer* customer{findCustomerByAccountId(customers, accountID)};
    
        if (customer != nullptr) // if customer exists
        {
            int accountTypeChoice{ getAccountTypeChoice(action)};
            
            // if action 1 == deposit, 2 == withdraw
            
            double getProcessAmount{ getAmount(accountTypeChoice, action)};
            
            // if action 1 == deposit, 2 == withdraw
            
            // 1 == checking, 2 == savings 
            handleCustomerAction(action, accountTypeChoice, customer, getProcessAmount);
            break;
        }
    }
    
}

double setupInitialChequingBalance()
{
    double initalChequingBalance{};

    while (true)
    {
        std::cout << "How much initial balance would you want to deposit to your chequing account?: ";
        std::cin >> initalChequingBalance;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Only input $$$ amounts" << '\n';
            continue;
        }

        else if (initalChequingBalance <= 0)
        {
            ignoreLine();
            std::cout << "Invalid input! You can't deposit amounts from 0 to negative" << '\n';
            continue;
        }

        ignoreLine();
        return initalChequingBalance;
    }
}

double setupInitialSavingsBalance()
{
    double initialSavingsBalance{};

    while (true)
    {
        std::cout << "How much initial balance would you want to deposit to your savings account?: ";
        std::cin >> initialSavingsBalance;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Only input $$$ amounts" << '\n';
            continue;
        }

        else if (initialSavingsBalance <= 0)
        {
            ignoreLine();
            std::cout << "Invalid input! You can't deposit amounts from 0 to negative" << '\n';
            continue;
        }

        ignoreLine();
        return initialSavingsBalance;
    }
}

void pressToContinue()
{
    std::cout << "\nPress Enter to return to the main menu continue..." << '\n';
    std::cin.get(); // waits for the user
}

void createNewAccount(std::vector<Customer>& customers)
{
    BankAccount newChequingAccount{BankAccountType::chequing, setupInitialChequingBalance()};
    BankAccount newSavingsAccount{BankAccountType::savings, setupInitialSavingsBalance()};

    std::string firstName{createFName()};
    std::string lastName{createLName()};
    std::string email{createEmail()};
    std::string phoneNumber{createPhoneNumber()};
    std::string address{createAddress()};
    std::string occupation{createOccupation()};

    Customer newCustomer{
        newChequingAccount,
        newSavingsAccount,
        firstName,
        lastName,
        email,
        phoneNumber,
        address,
        occupation
    };

    // adds to our vector
    customers.push_back(newCustomer);

    newCustomer.printInformationInvidual();

    std::cout << "--- Customer Account Created Successfully! ---" << '\n';
}

int printEditMenuOptions()
{
    int choice{};
    
    while (true)
    {
        std::cout << "1. First name" << '\n';
        std::cout << "2. Second name" << '\n';
        std::cout << "3. Email" << '\n';
        std::cout << "4. Phone Number" << '\n';
        std::cout << "5. Address" << '\n';
        std::cout << "6. Occupation" << '\n';
        std::cout << "7. Return to Main Menu" << '\n' << '\n';
        
        std::cout << "Select field to update: ";
        std::cin >> choice;
        
        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Only choose from 1 - 7. \n";
            continue;
        }
        
        ignoreLine();
        return choice;
    }
    
}

void editUpdateAccounts(std::vector<Customer>& customers)
{
    while (true)
    {
        int accountID{getAccountID()};
        Customer* customer{findCustomerByAccountId(customers, accountID)};

        if (customer != nullptr)
        {
            customer->printInformationInvidual();

            int choice{printEditMenuOptions()};
            std::string newEntry{};


            switch (choice)
            {
            case 1:
                std::cout << "Enter new first name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatefName(newEntry);

                std::cout << "First name successfully changed!" << "\n" << "\n";

                // brings back to the while true above
                continue;

            case 2:
                std::cout << "Enter new last name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatelName(newEntry);

                std::cout << "Last name successfully!" << "\n" << "\n";
                continue;

            case 3:
                std::cout << "Enter new email: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updateEmail(newEntry);

                std::cout << "Email successfully changed!" << "\n" << "\n";

                continue;
            case 4:
                std::cout << "Enter new phone number: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatePhone(newEntry);

                std::cout << "Phone number successfully changed!" << "\n" << "\n";

                continue;
            case 5:

                std::cout << "Enter new address: ";
                std::getline(std::cin >> std::ws, newEntry);

                customer->updateAddress(newEntry);
                std::cout << "Address successfully changed!" << "\n" << "\n";

                continue;
            case 6:
                std::cout << "Enter new occupation: ";
                std::getline(std::cin >> std::ws, newEntry);

                customer->updateOccupation(newEntry);
                std::cout << "Occupation successfully changed!" << "\n" << "\n";

                continue;

            case 7:
                std::cout << '\n';
                return;

            default:
                break;
            }
        }
    }
}

void testData(std::vector<Customer>& customers)
{
    Customer c(BankAccount(BankAccountType::chequing, 100.00),
               BankAccount(BankAccountType::savings, 200.00),
               "Emile",
               "TEST LNAME",
               "EMAIL",
               "PHONE",
               "ADDRESS",
               "OCCUPATION");

    customers.push_back(c);

    Customer d(BankAccount(BankAccountType::chequing, 200.00),
               BankAccount(BankAccountType::savings, 400.00),
               "TEST",
               "TEST",
               "TEST EMAIL",
               "TEST PHONE",
               "TEST ADDRESS",
               "TEST OCCUPATION");

    customers.push_back(d);
}


void showMenu(std::vector<Customer>& customers)
{
    while (true)
    {
        int option{};

        std::cout << "=== BANK MANAGEMENT SYSTEM ===\n";
        std::cout << "\t1. View Account Details" << '\n'; // will print all customer's details
        std::cout << "\t2. Withdraw Funds" << '\n';
        std::cout << "\t3. Deposit Funds" << '\n';
        std::cout << "\t4. Create New Accounts" << '\n';
        std::cout << "\t5. Edit/Update Accounts" << '\n';
        std::cout << "\t6. Exit" << '\n';

        std::cout << "\nPlease choose an option: ";
        std::cin >> option;

        if (!std::cin) // input validation // std::cin only works with int data types
        {
            ignoreLine();
            std::cout << "Invalid input. Only choose from 1 - 5" << '\n' << '\n';
            continue;
        }

        switch (option)
        {
        case 1:
            viewAccountDetails(customers);
            break;

        case 2:
            // 1 == deposit, 2 == withdraw
            handleTransactionProcess(customers, 2);
            break;

        case 3:
            // 1 == deposit, 2 == withdraw
            handleTransactionProcess(customers, 1);
            break;

        case 4:
            createNewAccount(customers);
            pressToContinue();
            break;

        case 5:
            editUpdateAccounts(customers);
            break;

        case 6:
            return;
        }
    }
}
