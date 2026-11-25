#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Customer.h"

/*
TODO

balance after formatting,
table formatting

*/

int main()
{
    std::vector<Customer> customers {};
    std::vector<Product> products{};
    
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


