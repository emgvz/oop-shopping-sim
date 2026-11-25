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
	Product::InStock });

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

	products.push_back(Product{ Product::School,
		"Ballpen",
	3.99,
	0,
	Product::OutOfStock });

	products.push_back(Product{ Product::Gaming,
		"VR Headset",
	499.99,
	0,
	Product::OutOfStock });


}

void browseCatalog(std::vector<Product>& products)
{
	clearScreen();

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

int getProductQty(Product* product)
{
	while (true)
	{
		if (product->getQuantity() == 0)
		{
			std::cout << "Sorry this product is out of stock! Please choose another product!" << '\n';
			return -1;
		}

		int pQty{};

		std::cout << "How many of " << product->getPName() << " are you buying?: ";
		std::cin >> pQty;

		if (!std::cin)
		{
			ignoreLine();
			std::cout << "Invalid quantity! Please try again!" << '\n';
			continue;
		}

		if (pQty <= 0)
		{
			ignoreLine();
			std::cout << "Sorry! Quantities should be greater than 0" << '\n';
			continue;
		}

		ignoreLine();
		return pQty;
	}
}

Product* findProductByProductId(std::vector<Product>& products, int pID)
{
	for (Product& product : products)
	{
		if (product.getPID() == pID)
		{
			std::cout << "Product found!" << '\n';
			return &product;
		}
	}

	std::cout << "Product not found on the catalog. Please try again!" << '\n';
	return nullptr;
}

bool checkProductQty(Product* product, int custQty)
{
	if (custQty <= product->getQuantity())
	{
		return true;
	}
	else
	{
		std::cout << "Sorry, we don't have enough stock for that quantity! Only " << product->getQuantity() << " left.\n";
		return false;
	}
		
}

void purchaseProducts(std::vector<Customer>& customer, std::vector<Product>& products, Transaction::Type transactionType)
{
	PurchasingCustomer purchasingCust{ handleTransactionProcess(customer, products, transactionType) };

	if (purchasingCust.getCustomer() != nullptr)
	{
		while (true)
		{
			clearScreen();

			browseCatalog(products);

			std::cout << "Welcome customer: " << purchasingCust.getCustomer()->getFullName() << '\n';

			std::string_view productIDPrompt{ "What is your Product ID? (-1 to go back to the Shopping Main Menu): " };

			int productID{ getID(productIDPrompt) };

			if (productID == -1)
			{
				return;
			}

			//find productid
			Product* product{ findProductByProductId(products, productID) };

			if (product == nullptr)
			{
				pressToContinue();
				continue;
			}

			if (product != nullptr)
			{
				// check product stock

				int custQtyPurchase{ getProductQty(product) };

				//if customer selects a product that has 0 qty, return back
				if (custQtyPurchase == -1) // if product qty == 0
				{
					pressToContinue();
					continue;
				}

				if (checkProductQty(product, custQtyPurchase))
				{
					double pPrice{ product->getPrice() };

					// if qty of the customer > qty of product
					double custTotal{ custQtyPurchase * pPrice };

					Transaction::Status orderStatus{};

					if (handleCustomerAction(transactionType, purchasingCust.getAccountType(), purchasingCust.getCustomer(), custTotal))
					{
						orderStatus = Transaction::Successful;
					}

					else
					{
						orderStatus = Transaction::Unsuccessful;
						break;
					}

					// make changes to the product's quantity
					int newProductQty{ product->getQuantity() - custQtyPurchase };

					// quantity and out of stock changes
					if (newProductQty == 0)
					{
						product->updateQuantity(0);
						product->updateStatus(product->OutOfStock);
					}

					if (newProductQty > 0)
					{
						product->updateQuantity(newProductQty);
					}

					BankAccount::Type accountUsedTransaction{ getAccountType(purchasingCust.getAccountType()) };

					double custAfterBalance{ balanceAfterTransaction(accountUsedTransaction, purchasingCust.getCustomer()) };

					Transaction newTransaction{ accountUsedTransaction,
						transactionType,
						product->getPType(),
						product->getPName(),
						product->getPrice(),
						custQtyPurchase,
						custTotal,
						custAfterBalance,
						orderStatus
					};

					// add purchased items to customer's shopping cart, prints their items (switching status and calculating total by getPrice() * getQty()

					purchasingCust.getCustomer()->addPurchasedItems(*product, custQtyPurchase); // we're deferencing the pointer here to unwrap it
					purchasingCust.getCustomer()->addTransactionItems(newTransaction);
					purchasingCust.getCustomer()->printTransactionPurchase();

					pressToContinue();
				}
				else // when customer ordered more than the products stock
				{
					pressToContinue();
				}
				
			}
		}
	}
}

void viewTransactionHistory(std::vector<Customer>& customer, std::vector<Product>& product)
{
	while (true)
	{
		clearScreen();

		std::string_view accountIDPrompt{ "What is your Account ID? (-1 to go back to the Shopping Main Menu): " };

		int accountID{ getID(accountIDPrompt) };

		if (accountID == -1)
		{
			return;
		}

		Customer* transactionCustomer{ findCustomerByAccountId(customer, accountID) };
		
		if (transactionCustomer != nullptr)
		{
			std::cout << '\n';

			transactionCustomer->printTransactionPurchase();
			pressToContinue();
		}
	}
}

void viewPurchaseTransaction(std::vector<Customer>& customer, std::vector<Product>& product)
{
	while (true)
	{
		clearScreen();

		std::string_view accountIDPrompt{ "What is your Account ID? (-1 to go back to the Shopping Main Menu): " };

		int accountID{ getID(accountIDPrompt) };

		if (accountID == -1)
		{
			return;
		}

		Customer* transactionCustomer{ findCustomerByAccountId(customer, accountID) };

		if (transactionCustomer != nullptr)
		{
			std::cout << '\n';

			transactionCustomer->printItemsBought();
			pressToContinue();
		}
	}

}

void showShoppingMenu(std::vector<Customer>& customers, std::vector<Product>& products)
{
	while (true)
	{
		int shoppingOption{};

		Transaction::Type purchaseTransaction{ Transaction::Purchase };

		clearScreen();
		std::cout << "=== SHOPPING MENU ===\n";
		std::cout << "\t1. Browse Catalog" << '\n';
		std::cout << "\t2. Make a Purchase" << '\n';
		std::cout << "\t3. View Purchase Transaction" << '\n';
		std::cout << "\t4. View Purchased Items" << '\n';

		std::cout << "\t5. Back to Main Menu" << '\n' << '\n';

		std::cout << "Please choose an option: ";
		std::cin >> shoppingOption;

		if (!std::cin)
		{
			ignoreLine();
			std::cout << "Invalid input. Only choose from 1 - 5." << '\n';
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
			purchaseProducts(customers, products, purchaseTransaction);
			break;

		case 3:
			viewTransactionHistory(customers, products);
			pressToContinue();
			break;

		case 4:
			viewPurchaseTransaction(customers, products);
			pressToContinue();
			break;

		case 5:
			return;

		default:
			std::cout << "Invalid input. Only choose from 1 - 5." << '\n' << '\n';
			continue;
		}
	}
}

#endif