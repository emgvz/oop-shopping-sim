#pragma once
#include <vector>
#include <optional>

#include "Customer.h"
#include "Utilities.h"

#include "BankFunctionalities.h"
#include "ProductFunctionalities.h"

// test comment from laptop
void showMenu(std::vector<Customer>& customers, std::vector<Product>& products)
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
            showBankingMenu(customers, products);
            break;

        case 2:
            showShoppingMenu(customers, products);
            break;

        case 3:
            return;

        default:
            std::cout << "Invalid input. Only choose from 1 - 3." << '\n' << '\n';
            continue;
        }
    }
}