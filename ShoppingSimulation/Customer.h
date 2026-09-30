#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <format>

#include "BankAccount.h"
#include <string>
#include <string_view>


class Customer
{
private:
    static inline int s_idIdentifier{ 1 };
    int m_id{};
    
    // each customer will have 2 accounts with $0.0
    BankAccount m_chequingAccount{BankAccountType::chequing, 0.0};
    BankAccount m_savingsAccount{BankAccountType::savings, 0.0};
    
    std::string m_firstName{"???"};
    std::string m_lastName{"???"};
    std::string m_email{"???"};
    std::string m_phone{"???"};
    std::string m_address{"???"};
    std::string m_occupation{"???"};
    
    // constructors
public:
    Customer() = default;
    
    Customer(const BankAccount& chequingAccount,
        const BankAccount& savingsAccount,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& email,
        const std::string& phone,
        const std::string& address,
        const std::string& occupation
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
    
    void depositToAccount(BankAccountType::Type bankAccountType, double amount);
    void withdrawFromAccount(BankAccountType::Type bankAccountType, double amount);
    
    // move balance from account to account soon
    
    BankAccount& getChequingAccount() { return m_chequingAccount; }
    BankAccount& getSavingsAccount() { return m_savingsAccount; }
    
    void printInformationInvidual() const;
    void printInformation() const;
    
};

#endif

