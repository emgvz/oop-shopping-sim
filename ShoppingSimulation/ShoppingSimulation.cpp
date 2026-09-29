#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Customer.h"

/*
 * Person class
 * Bank class 
 * Item class?
 * Store class
 * 
 * 
 * TODO

 * TABLE FORMATTING???
 */

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
        else if (userChoice == "y" || userChoice == "Y")
        {
            return false; // stop running
        }
    }
    
}


int main()
{
    std::vector<Customer> customers {};
    
    testData(customers); 
    do
    {
        std::cout << "Welcome to Shopping Simulation!" << '\n' << '\n';
        
        showMenu(customers);
    }
    while (continueTransaction());
    
    std::cout << "Thank you and hope to see you again!" << '\n';

    
    
    return 0;
}
