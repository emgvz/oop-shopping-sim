#pragma once
#include <vector>
#include <optional>

#include "Customer.h"

bool continueTransaction()
{
    while (true)
    {
        std::string userChoice{};
        
        std::cout << "Are you sure you want to exit the application? (y to exit, n to return to menu): ";
        std::cin >> userChoice;
        
        if (userChoice == "n" || userChoice == "N")
        {
            return true;
        }
        if (userChoice == "y" || userChoice == "Y")
        {
            return false; // stop running
        }
    }
    
}

void clearScreen()
{
#if defined(_WIN32) || defined (_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ignoreLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// create customer details

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
    clearScreen();

    if (customers.empty())
    {
        std::cout << "There are no customers available to view " << '\n' << '\n';
        return;
    }

    std::cout << "Here are the customer's details registered in the Bank of Romnie" << '\n';

    for (const Customer& customer : customers)
    {
        customer.printInformation();
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
            std::cout << "Please try again! Only choose from 1 for Chequing or 2 for Savings." << '\n';
            continue;
        }
        
        // catch values that are higher 
        ignoreLine();
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

        ignoreLine();
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
    BankAccount::Type bankAccountType{ accountTypeChoice == 1 ? BankAccount::chequing : BankAccount::savings };
    
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

double setupCheckingSavingsBalance(int checkingSavings)
{
    double initialBalance{};

    while (true)
    {
        std::cout << "How much initial balance would you want to deposit to your " << (checkingSavings == 0 ? "checking" : "savings") << " account?: ";
        std::cin >> initialBalance;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Only input $$$ amounts" << '\n';
            continue;
        }

        else if (initialBalance <= 0)
        {
            ignoreLine();
            std::cout << "Invalid input! You can't deposit amounts from 0 to negative" << '\n';
            continue;
        }

        ignoreLine();
        return initialBalance;
    }

}

void pressToContinue()
{
    std::cout << "\nPress Enter to return to the main menu continue..." << '\n';

    std::cin.get(); // waits for the user to press something
}

void createNewAccount(std::vector<Customer>& customers)
{
    clearScreen();

    std::cout << "Please fill up the details below to create your account."<< '\n' << '\n';

    BankAccount newChequingAccount{BankAccount::chequing, setupCheckingSavingsBalance(0)};
    BankAccount newSavingsAccount{BankAccount::savings, setupCheckingSavingsBalance(1)};

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

    customers.push_back(newCustomer);

    newCustomer.printInformationIndividual();

    std::cout << "--- Customer Account Created Successfully! ---" << '\n';
}

int printEditMenuOptions()
{
    int choice{};
    
    while (true)
    {
        std::cout << "1. First name" << '\n';
        std::cout << "2. Last name" << '\n';
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
            customer->printInformation();
            
            int choice{printEditMenuOptions()};
            
            std::string newEntry{};
            
            switch (choice)
            {
            case 1:
                std::cout << "Enter new first name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatefName(newEntry);

                std::cout << "First name successfully changed!" << "\n" << "\n";
                return;

            case 2:
                std::cout << "Enter new last name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatelName(newEntry);

                std::cout << "Last name successfully changed!" << "\n" << "\n";
                return;

            case 3:
                std::cout << "Enter new email: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updateEmail(newEntry);

                std::cout << "Email successfully changed!" << "\n" << "\n";
                return;
                
            case 4:
                std::cout << "Enter new phone number: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatePhone(newEntry);

                std::cout << "Phone number successfully changed!" << "\n" << "\n";
                return;
                
            case 5:

                std::cout << "Enter new address: ";
                std::getline(std::cin >> std::ws, newEntry);

                customer->updateAddress(newEntry);
                std::cout << "Address successfully changed!" << "\n" << "\n";
                return;
                
            case 6:
                std::cout << "Enter new occupation: ";
                std::getline(std::cin >> std::ws, newEntry);

                customer->updateOccupation(newEntry);
                std::cout << "Occupation successfully changed!" << "\n" << "\n";
                return;

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
    Customer c(BankAccount(BankAccount::chequing, 100.00),
               BankAccount(BankAccount::savings, 200.00),
               "Emile",
               "TEST LNAME",
               "EMAIL",
               "PHONE",
               "ADDRESS",
               "OCCUPATION");

    customers.push_back(c);

    Customer d(BankAccount(BankAccount::chequing, 200.00),
               BankAccount(BankAccount::savings, 400.00),
               "TEST",
               "TEST",
               "TEST EMAIL",
               "TEST PHONE",
               "TEST ADDRESS",
               "TEST OCCUPATION");

    customers.push_back(d);
}

void showBankingMenu(std::vector<Customer>& customers)
{
    while (true)
    {
        clearScreen();

        std::cout << "=== BANK MANAGEMENT SYSTEM ===\n";
        std::cout << "\t1. View Account Details" << '\n';
        std::cout << "\t2. Withdraw Funds" << '\n';
        std::cout << "\t3. Deposit Funds" << '\n';
        std::cout << "\t4. Create New Accounts" << '\n';
        std::cout << "\t5. Edit/Update Accounts" << '\n';
        std::cout << "\t6. Back to Main Menu" << '\n' << '\n';

        int option{};

        std::cout << "Please choose an option: ";
        std::cin >> option;

        if (!std::cin) // input validation // std::cin only works with int data types
        {
            ignoreLine();
            std::cout << "Invalid input. Only choose from 1 - 6" << '\n';
            continue;
        }

        ignoreLine();

        switch (option)
        {
        case 1:
            viewAccountDetails(customers);
            pressToContinue();
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

void showShoppingMenu(std::vector<Customer>& customer)
{
    while (true)
    {
        int shoppingOption{};

        clearScreen();
        std::cout << "=== SHOPPING MENU ===\n";
        std::cout << "\t1. Browse Catalog" << '\n';
        std::cout << "\t2. Make a Purchase" << '\n';
        std::cout << "\t3. View Transaction History" << '\n';
        std::cout << "\t4. Back to Main Menu" << '\n' << '\n';

        std::cout << "Please choose an option: ";
        std::cin >> shoppingOption;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input. Only choose from 1 - 4." << '\n';
            continue;
        }

        ignoreLine();


        switch (shoppingOption)
        {
        case 1:
            // browseCatalog();
            break;

        case 2:
            // purchaseItem();
            break;

        case 3:
            // viewTransactionHistory();
            break;

        case 4:
            return;

        default:
            std::cout << "Invalid input. Only choose from 1 - 4." << '\n' << '\n';
            continue;
        }
    }
}

void showMenu(std::vector<Customer>& customers)
{
    while (true)
    {
        int menuOption{};

        clearScreen();
        std::cout << "Welcome to Romnie's Banking and Shopping Simulation!" << '\n';

        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "\t1. Banking" << '\n';
        std::cout << "\t2. Shopping" << '\n';
        std::cout << "\t3. Exit" << '\n' << '\n';

        std::cout << "Please choose an option: ";
        std::cin >> menuOption;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input. Only choose from 1 - 3." << '\n' << '\n';
            continue;
        }

        ignoreLine();

        switch (menuOption)
        {
        case 1:
            showBankingMenu(customers);
            break;
        case 2:
            showShoppingMenu(customers);
            break;
        case 3:
            return;
        default:
            std::cout << "Invalid input. Only choose from 1 - 3." << '\n' << '\n';
            continue;
        }
    }
}