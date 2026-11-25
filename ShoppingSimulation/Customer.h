#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <format>
#include <vector>

#include "BankAccount.h"
#include "Product.h"
#include "Transaction.h"
#include <string>
#include <string_view>


class Customer
{
private:
    static inline int s_idIdentifier{ 1 };
    int m_id{};
    
    // each customer will have 2 accounts with $0.0
    BankAccount m_chequingAccount{BankAccount::chequing, 0.0};
    BankAccount m_savingsAccount{BankAccount::savings, 0.0};
    
    std::string m_firstName{"???"};
    std::string m_lastName{"???"};
    std::string m_email{"???"};
    std::string m_phone{"???"};
    std::string m_address{"???"};
    std::string m_occupation{"???"};

    std::vector<Product> m_productsOwned{};
    std::vector<Product> wishlistProducts{};

    std::vector<Transaction> m_custTransaction{};
    
    // constructors
public:
    Customer() = default;
    
    Customer(BankAccount chequingAccount,
        BankAccount savingsAccount,
        std::string_view firstName,
        std::string_view lastName,
        std::string_view email,
        std::string_view phone,
        std::string_view address,
        std::string_view occupation
        );
    
    // setters
    
    void updatefName(std::string_view firstName) { m_firstName = firstName; }
    void updatelName(std::string_view lastName) { m_lastName = lastName; }
    void updateEmail(std::string_view email) { m_email = email; }
    void updatePhone(std::string_view phone) { m_phone = phone; }
    void updateAddress(std::string_view address) { m_address = address; }
    void updateOccupation(std::string_view occupation) { m_occupation = occupation; }
    
    // getters
    
    int getId() const { return m_id; }
    std::string_view getfName() const { return m_firstName; }
    std::string_view getlName() const { return m_lastName; }
    std::string getFullName() const { return std::format("{} {}", m_firstName, m_lastName); }
    std::string_view getEmail() const { return m_email; }
    std::string_view getPhone() const { return m_phone; }
    std::string_view getAddress() const { return m_address; }
    std::string_view getOccupation() const { return m_occupation; }

    std::vector<Product>& getProducts() { return m_productsOwned; }
    
    bool depositToAccount(BankAccount::Type bankAccountType, double amount);
    bool withdrawFromAccount(BankAccount::Type bankAccountType, double amount);

    // move balance from account to account soon
    
    BankAccount& getChequingAccount() { return m_chequingAccount; }
    BankAccount& getSavingsAccount() { return m_savingsAccount; }
    
    void printInformationIndividual() const;
    void printInformation() const;
    void printBalances() const;

    void addPurchasedItems(Product product, int custQtyPurchase);
    void printItemsBought() const;
    void addTransactionItems(Transaction transaction);
    void printTransactionBank() const;
    void printTransactionPurchase() const;
};

inline Customer::Customer(BankAccount chequingAccount,
        BankAccount savingsAccount,
        std::string_view firstName,
        std::string_view lastName,
        std::string_view email,
        std::string_view phone,
        std::string_view address,
        std::string_view occupation
        ) : 
    
    m_id( s_idIdentifier++ ),
    m_chequingAccount{ chequingAccount },
    m_savingsAccount{ savingsAccount },
    m_firstName{ firstName },
    m_lastName{ lastName },
    m_email{ email },
    m_phone { phone },
    m_address{ address },
    m_occupation{ occupation }
    
{}

#endif

