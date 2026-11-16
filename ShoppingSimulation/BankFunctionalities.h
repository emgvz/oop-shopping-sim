#ifndef BANKFUNCTIONALITIES_H
#define BANKFUNCTIONALITIES_H

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
    std::cout << "Press Enter to return to the main menu continue..." << '\n';

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

int getAccountTypeChoice(int option)
{
    while (true)
    {
        int accountTypeChoice{};

        std::cout << "\t1. Chequing Account" << '\n';
        std::cout << "\t2. Savings Account" << '\n' << '\n';

        std::cout << "Which account do you want to " << (option == 1 ? "deposit to" : "withdraw from") << " (1 for Chequing, 2 for Savings)?: ";
        std::cin >> accountTypeChoice;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Please try again! Only choose from 1 for Chequing or 2 for Savings." << '\n';
            continue;
        }

        ignoreLine();
        return accountTypeChoice;
    }
}

double getAmount(int accountTypeChoice, int action)
{
    double amount{};

    while (true)
    {
        std::cout << "Enter the amount to be " << (action == 1 ? "deposited to" : "withdrawn from") << " your " << (accountTypeChoice == 1 ? "chequing" : "savings") << " account: ";
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
        std::cout << "What is your Account ID? (-1 to go back to the Bank Main Menu): ";
        std::cin >> accountID;

        if (!std::cin)
        {
            ignoreLine();
            std::cout << "Invalid input! Please only input numerical numbers: " << '\n';
            continue;
        }

        if (accountID == -1)
            return -1;

        ignoreLine();
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
    clearScreen();

    std::string_view transactionType{ action == 1 ? "Deposit" : "Withdrawal" };

    std::cout << "=== BANK OF ROMNIE : " << transactionType << " ===\n";
    std::cout << transactionType << " has never been easier!\n\n";

    while (true)
    {
        int accountID(getAccountID());

        if (accountID == -1)
        {
            break;
        }

        Customer* customer{ findCustomerByAccountId(customers, accountID) };

        if (customer != nullptr) // if customer exists
        {
            customer->printInformation();

            int accountTypeChoice{ getAccountTypeChoice(action) };

            // if action 1 == deposit, 2 == withdraw

            double getProcessAmount{ getAmount(accountTypeChoice, action) };

            // 1 == checking, 2 == savings 
            handleCustomerAction(action, accountTypeChoice, customer, getProcessAmount);

            std::cout << "\n--- Updated Account Details ---\n";
            customer->printInformation();

            pressToContinue();

            break;
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

        std::cout << "Here is what you want you entered. Do you want to submit, or start over (1 for YES, 2 for NO)?: ";

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

        int accountID{ getAccountID() };
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