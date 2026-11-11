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

int main()
{
    std::vector<Customer> customers {};
    
    testData(customers); 
    
    do
    {
        // menu for 2 options 1. Banking 2. Shopping
        showMenu(customers);

    }
    while (continueTransaction());
    
    std::cout << "Thank you and we hope to see you again!" << '\n';

    
    
    return 0;
}
