#ifndef BANKFUNCTIONALITIES_H
#define BANKFUNCTIONALITIES_H

#include "PurchasingCustomer.h"

// create customer details

std::string createData(int& promptTracker)
{
    std::string quitPrompt{ "\nYou can quit anytime by typing quit or QUIT to any of the fields below\n" };
    std::string newData{};
    std::string prompt{ "What is your " };

    switch (promptTracker)
    {
    case 0:

        prompt += "first name?: ";
        std::cout << quitPrompt;
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);

        promptTracker++;
        return newData;

    case 1:
        prompt += "last name?: ";
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);

        promptTracker++;
        return newData;

    case 2:
        prompt += "email?: ";
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);

        promptTracker++;
        return newData;

    case 3:
        prompt += "phone number?: ";
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);

        promptTracker++;
        return newData;

    case 4:
        prompt += "address?: ";
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);

        promptTracker++;
        return newData;

    case 5:
        prompt += "occupation?: ";
        std::cout << prompt;

        std::getline(std::cin >> std::ws, newData);
        promptTracker = 0; // reset back to 0 // when user manages to reach the end 

        return newData;
    }
}

void pressToContinue()
{
    std::cout << "Press Enter to continue..." << '\n';

    std::cin.get(); // waits for the user to press something
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

int getAccountTypeChoice(std::string_view transactionType, std::string_view prompt)
{
    while (true)
    {
        int accountTypeChoice{};

        std::cout << "\t1. Chequing Account" << '\n';
        std::cout << "\t2. Savings Account" << '\n' << '\n';


        if (transactionType == "Withdraw" || transactionType == "Deposit" || transactionType == "Purchase")
        // if transaction is either withdraw or deposit
        std::cout << prompt;

        std::cin >> accountTypeChoice;

        if (accountTypeChoice > 2 || accountTypeChoice < 0)
        {
            std::cout << "Only available options are 1 for Chequing or 2 for Savings. Please try again." << '\n' << '\n';
            continue;
        }

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Only choose from 1 for Chequing or 2 for Savings." << '\n' << '\n';
            continue;
        }

        ignoreLine();
        return accountTypeChoice;
    }
}

double getAmount(std::string_view transactionType, std::string_view prompt)
{
    double amount{};

    while (true)
    {

        if (transactionType == "Withdraw" || transactionType == "Deposit")
        {
            std::cout << prompt;
        }

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

int getID(std::string_view prompt)
{
    int ID{};

    while (true)
    {
        // bank and shopping have individual prompts now
        std::cout << prompt;
        std::cin >> ID;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Please only input numerical numbers: " << '\n';
            continue;
        }

        if (ID == -1)
            return -1;

        ignoreLine();
        return ID;
    }
}

void handleCustomerAction(std::string_view transactionType, int accountTypeChoice, Customer* customer, double processAmount)
{
    BankAccount::Type bankAccountType{ accountTypeChoice == 1 ? BankAccount::chequing : BankAccount::savings };

    if (transactionType == "Withdraw" || transactionType == "Purchase")
    {
        customer->withdrawFromAccount(bankAccountType, processAmount);
    }

    if (transactionType == "Deposit")
    {
        customer->depositToAccount(bankAccountType, processAmount);
    }
    
}

bool confirmAccountUse(int accountType)
{
    while (true)
    {
        std::string custChoice{};

        std::cout << (accountType == 1 ? "Chequing " : "Savings ") << "account will be used for making this purchase? (y for yes, n for no): ";
        std::cin >> custChoice;

        if (custChoice == "y" || custChoice == "Y")
        {
            ignoreLine();
            return true;
        }

        if (custChoice == "n" || custChoice == "N")
        {
           ignoreLine();
           return false;
        }

        else
        {
            std::cout << "Only acceptable options are y or n. Please try again." << '\n';
            ignoreLine();
            continue;
        }
    }
}

PurchasingCustomer handleTransactionProcess(std::vector<Customer>& customers, std::vector<Product>& product, std::string_view transactionType)
{
    clearScreen();

    if (transactionType == "Withdraw" || transactionType == "Deposit")
    {
        std::cout << "=== BANK OF ROMNIE : " << transactionType << " ===\n";
        std::cout << transactionType << " has never been easier!\n\n";
    }

    if (transactionType == "Purchase")
    {
        std::cout << "=== SHOP OF ROMNIE : Purchase ===" << '\n';
    }
    
    
    while (true)
    {
        std::string accountIDPrompt{ "What is your Account ID? (-1 to go back to the "+ std::string
            (transactionType == "Withdraw" || transactionType == "Deposit" ? "Bank " : "Shopping ") + "Main Menu): "};

        int accountID( getID(accountIDPrompt) );

        if (accountID == -1)
        {
            break;
        }

        Customer* customer{ findCustomerByAccountId(customers, accountID) };

        if (customer != nullptr) // if customer exists
        {
            customer->printBalances();

            while (true)
            {
                std::string prompt{""};

                if (transactionType == "Withdraw" || transactionType == "Deposit")
                {
                    prompt = "Which account do you want to" + std::string(transactionType == "Withdraw" ? " withdraw from " : " deposit to ") + "(1 for Chequing, 2 for Savings): ";
                }

                if (transactionType == "Purchase")
                {
                    prompt = "Which account do you want to use for this purchase? (1 for Chequing, 2 for Savings): ";
                }

                int accountTypeChoice{ getAccountTypeChoice(transactionType, prompt) };

                PurchasingCustomer c{};

                if (transactionType == "Withdraw" || transactionType == "Deposit")
                {
                    std::string transactionPrompt{ "Enter the amount to be "
                        + std::string(transactionType == "Deposit" ? "deposited to" : "withdrawn from") 
                        + " your " + std::string(accountTypeChoice == 1 ? "chequing" : "savings") + " account: " };

                    double getProcessAmount{ getAmount(transactionType, transactionPrompt) };

                    handleCustomerAction(transactionType, accountTypeChoice, customer, getProcessAmount);

                    std::cout << "\n--- Updated Account Details ---\n";
                    customer->printBalances();

                    c.setAccountType(0);
                    c.setCustomer(nullptr);

                    pressToContinue();

                    // transaction logic

                    /*
                    
                    
                    */
                }

                if (transactionType == "Purchase")
                {
                    bool confirm{ confirmAccountUse(accountTypeChoice) };

                    if (!confirm)
                    {
                        continue;
                    }

                    c.setAccountType(accountTypeChoice);
                    c.setCustomer(customer);

                }

                return c;
            }
        }
    }

}

double setupCheckingSavingsBalance(int checkingSavings)
{
    double initialBalance{};

    while (true)
    {
        std::cout << "How much initial balance would you want to deposit to your " << (checkingSavings == 0 ? "checking" : "savings") << " account? (-1 to quit): ";
        std::cin >> initialBalance;

        if (initialBalance == -1)
        {
            return -1;
        }

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

bool printTemporaryCustomer(Customer customer)
{
    while (true)
    {
        customer.printInformationIndividual();

        std::cout << "Here is what you entered. Do you want to submit, or start over (1 for YES, 2 for NO)?: ";

        int tmpDec{};
        std::cin >> tmpDec;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Please try again!\n";
            continue;
        }

        ignoreLine();

        switch (tmpDec)
        {
        case 1:
            return true;

        case 2:
            return false;

        default:
            std::cout << "Invalid input! Only choose from 1 - 2!\n";
            continue;
        }
    }


}

void createNewAccount(std::vector<Customer>& customers)
{
    while (true)
    {
        clearScreen();

        std::cout << "Please fill up the details below to create your account." << '\n' << '\n';

        double initialChequingBal{ setupCheckingSavingsBalance(0) };
        if (initialChequingBal == -1) { return; }

        double initialSavingsBal{ setupCheckingSavingsBalance(1) };
        if (initialSavingsBal == -1) { return; }

        BankAccount newChequingAccount{ BankAccount::chequing, initialChequingBal };
        BankAccount newSavingsAccount{ BankAccount::savings, initialSavingsBal };

        static int promptTracker{ 0 };
        std::string firstName{ createData(promptTracker) };
        if (firstName == "quit" || firstName == "QUIT") { promptTracker = 0; return; }

        std::string lastName{ createData(promptTracker) };
        if (lastName == "quit" || lastName == "QUIT") { promptTracker = 0; return; }

        std::string email{ createData(promptTracker) };
        if (email == "quit" || email == "QUIT") { promptTracker = 0; return; }

        std::string phoneNumber{ createData(promptTracker) };
        if (phoneNumber == "quit" || phoneNumber == "QUIT") { promptTracker = 0; return; }

        std::string address{ createData(promptTracker) };
        if (address == "quit" || address == "QUIT") { promptTracker = 0; return; }

        std::string occupation{ createData(promptTracker) };
        if (occupation == "quit" || occupation == "QUIT") { promptTracker = 0; return; }


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


        // summary of what they entered

        bool confirmDetails{ printTemporaryCustomer(newCustomer) };

        // if user wanted to submit

        if (confirmDetails)
        {
            customers.push_back(newCustomer);

            std::cout << "\n--- Customer Account Created Successfully! ---\n";
            pressToContinue();

            break;
        }

        // if user wanted to start over
        else
        {
            continue;
        }

    }

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

// show previous change vs current change

void editUpdateAccounts(std::vector<Customer>& customers)
{
    while (true)
    {
        clearScreen();

        std::cout << "Before we make changes to your account, first we would like to ask for your Account ID." << '\n';
        std::string_view accountIDPrompt{ "What is your Account ID? (-1 to go back to the Bank Main Menu): " };

        int accountID{ getID(accountIDPrompt)};
        Customer* customer{ findCustomerByAccountId(customers, accountID) };

        if (customer != nullptr)
        {
            customer->printInformation();

            int choice{ printEditMenuOptions() };

            std::string newEntry{};

            switch (choice)
            {
            case 1:
                std::cout << "Enter new first name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatefName(newEntry);

                std::cout << "First name successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 2:
                std::cout << "Enter new last name: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatelName(newEntry);

                std::cout << "Last name successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 3:
                std::cout << "Enter new email: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updateEmail(newEntry);

                std::cout << "Email successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 4:
                std::cout << "Enter new phone number: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updatePhone(newEntry);

                std::cout << "Phone number successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 5:

                std::cout << "Enter new address: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updateAddress(newEntry);

                std::cout << "Address successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 6:
                std::cout << "Enter new occupation: ";

                std::getline(std::cin >> std::ws, newEntry);
                customer->updateOccupation(newEntry);

                std::cout << "Occupation successfully changed!" << "\n" << "\n";

                std::cout << "\n--- Updated Account Details ---\n";
                customer->printInformation();

                pressToContinue();
                return;

            case 7:
                return;

            default:
                std::cout << "\nOut of bounds! Only choose from 1 - 7!\n";

                pressToContinue();
                return;
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

void showBankingMenu(std::vector<Customer>& customers, std::vector<Product>& products)
{
    while (true)
    {
        clearScreen();

        std::string withdrawTransaction{ "Withdraw" };
        std::string depositTransaction{ "Deposit" };

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
            handleTransactionProcess(customers, products, withdrawTransaction);
            break;

        case 3:
            handleTransactionProcess(customers, products, depositTransaction);
            break;

        case 4:
            createNewAccount(customers);
            break;

        case 5:
            editUpdateAccounts(customers);
            break;

        case 6:
            return;
        }
    }
}

#endif 