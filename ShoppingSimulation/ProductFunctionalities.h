#ifndef PRODUCTFUNCTIONALITIES_H
#define PRODUCTFUNCTIONALITIES_H
#include <iomanip>

void insertProductData(std::vector<Product>& products)
{
    products.push_back(Product{ Product::Clothing,
        "T-shirt",
        29.9,
        5,
        Product::InStock });

 
    products.push_back(Product{ Product::Clothing,
        "Denim Jeans",
        59.99,
        7,
        Product::InStock });


    products.push_back(Product{ Product::Gaming,
        "Gaming Laptop",
    1299.00,
    2,
    Product::InStock});

    products.push_back(Product{ Product::Electronics,
        "Mobile Phone",
    999.99,
    4,
    Product::InStock });

    products.push_back(Product{ Product::Medical,
        "First Aid Kit",
    22.99,
    9,
    Product::InStock });

    products.push_back(Product{ Product::Food,
        "Energy Drink",
    4.99,
    15,
    Product::InStock });

    products.push_back(Product{ Product::School,
        "Pencil",
    2.99,
    20,
    Product::InStock });

    products.push_back(Product{ Product::School,
        "Notebook",
    3.99,
    27,
    Product::InStock });


}

void browseCatalog(std::vector<Product>& products)
{
    clearScreen();

    // if the there are no products

    // if there are

    if (products.empty())
    {
        std::cout << "There are no products available to view." << '\n' << '\n';
        return;
    }

    std::cout << std::left << std::setw(10) << "ID";
    std::cout << std::setw(20) << "Product Name";
    std::cout << std::setw(15) << "Type";
    std::cout << std::setw(15) << "Price";
    std::cout << std::right << std::setw(15) << "Quantity";
    std::cout << std::right << std::setw(15) << "Status" << '\n';

    std::cout << "==========================================================================================" << "\n" << "\n";

    for (const Product& p : products)
    {
        p.printProducts();
        std::cout << '\n';
    }

    std::cout << "==========================================================================================" << "\n" << "\n";

}

void purchaseProducts(std::vector<Customer>& customer, std::vector<Product>& product, int bankOrShopping)
{
    clearScreen();

    std::cout << "Who is buying from Romnie's Store?" << '\n';

    /*
    ask account to identify who is buying
    - find accountID

    - show their balance for that account
    */

    handleTransactionProcess(customer, 0, bankOrShopping);
    
   // show the browseCatalog(product) list

    browseCatalog(product);
   
    // ask if they would like to proceed with their current account


    
    //ask which product id to purchase

    //find productid
    // product[id].getPrice();

    //if customer selects a product that has 0 qty, return back

    //check if their balance meets the product's price
    //if they meet the product's balance, ask how much qty is the user buying,

    //if user entered qty x price that is higher than what the user has on their checking

    //balance = 150 - (price X qty)
    //checking or savings account - balance (if this one is above 0, we should be good)*/



 
    
    
    
}

void transactionHistory(std::vector<Customer>& customer, std::vector<Product>& product)
{

}

void showShoppingMenu(std::vector<Customer>& customers, std::vector<Product>& products, int bankOrShopping)
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
             browseCatalog(products);
             pressToContinue();
            break;

        case 2:
             purchaseProducts(customers, products, bankOrShopping);
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

#endif