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

void withdrawFunds(std::vector<Customer>& customers)
{
    // check id
    // ask which account checking or savings
    // ask how much to withdraw
}

void depositFunds(std::vector<Customer>& customers)
{
    // check id
    // ask which account checking or savings
    // ask how much to deposit
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


void editUpdateAccounts(std::vector<Customer>& customers)
{
    // find the id first then update that id's information

    while (true)
    {
        int idLookUp{};

        std::cout << "Enter Account ID to edit/update user: ";
        std::cin >> idLookUp;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Please only input number. \n" << '\n';
            continue;
        }

        for (Customer& customer : customers)
        {
            if (customer.getId() == idLookUp)
            {
                std::cout << "\nCustomer found!" << '\n';
                customer.printInformation();

                while (true)
                {
                    int choice{};
                    
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

                    std::string newFirstName{};
                    std::string newLastName{};
                    std::string newEmail{};
                    std::string newPhoneNumber{};
                    std::string newAddress{};
                    std::string newOccupation{};
                    
                    switch (choice)
                    {
                    case 1:
                        std::cout << "Enter new first name: ";

                        std::getline(std::cin >> std::ws, newFirstName);
                        customer.updatefName(newFirstName);
                        
                        std::cout << "First name successfully changed!"  << "\n" << "\n";

                        continue; // brings back to the while true above

                    case 2:
                        std::cout << "Enter new last name: ";

                        std::getline(std::cin >> std::ws, newLastName);
                        customer.updatelName(newLastName);
                        
                        std::cout << "Last name successfully!"  << "\n" << "\n";
                        
                        continue;

                    case 3:
                        std::cout << "Enter new email: ";

                        std::getline(std::cin >> std::ws, newLastName);
                        customer.updateEmail(newEmail);

                        std::cout << "Email successfully changed!"  << "\n" << "\n";

                        continue;

                    case 4:
                        std::cout << "Enter new phone number: ";

                        std::getline(std::cin >> std::ws, newPhoneNumber);
                        customer.updatePhone(newPhoneNumber);

                        std::cout << "Phone number successfully changed!"  << "\n" << "\n";

                        continue;

                    case 5:
                        std::cout << "Enter new address: ";
                        std::getline(std::cin >> std::ws, newAddress);
                        
                        customer.updateAddress(newAddress);
                        std::cout << "Address successfully changed!"  << "\n" << "\n";
                        
                        continue;

                    case 6:
                        std::cout << "Enter new occupation: ";
                        std::getline(std::cin >> std::ws, newOccupation);
                        
                        customer.updateOccupation(newOccupation);
                        std::cout << "Occupation successfully changed!"  << "\n" << "\n";

                        continue;

                    case 7:
                        return;
                    }
                }
            }
        }
        
        ignoreLine();
        std::cout << "Account ID not found! Please try again!" << '\n';
    }
}


void testData(std::vector<Customer>& customers)
{
    Customer c(BankAccount(BankAccountType::chequing, 100.00),
        BankAccount(BankAccountType::savings, 200.00),
        "Emile",
        "LMAO",
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
            withdrawFunds(customers);
            break;

        case 3:
            depositFunds(customers);
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
