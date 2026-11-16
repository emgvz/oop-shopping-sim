#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Customer.h"

/*
 * TODO
 * Item class?
 * Store class
 * Transaction class
 * TABLE FORMATTING???
 */

int main()
{
    std::vector<Customer> customers {};
    std::vector<Product> products{};
    // std::vector<Transaction> transactions{};

    
    testData(customers);
    insertProductData(products);
    
    do
    {
        showMenu(customers, products);

    }
    while (continueTransaction());
    
    std::cout << "Thank you and we hope to see you again!" << '\n';

    
    
    return 0;
}
