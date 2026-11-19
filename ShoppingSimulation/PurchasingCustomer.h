#ifndef PURCHASINGCUSTOMER_H
#define PURCHASINGCUSTOMER_H

#include "Customer.h"

class PurchasingCustomer
{
private:
	int m_accountType{ 0 };
	Customer* m_customer{ nullptr };


public:
	PurchasingCustomer() = default;

	PurchasingCustomer(int accountType, Customer* customer);

	// setters

	void setAccountType(int accountType) { m_accountType = accountType; }
	void setCustomer(Customer* customer) { m_customer = customer; }

	// getters
	int getAccountType() const { return m_accountType; }
	Customer* getCustomer() const { return m_customer; }
};

inline PurchasingCustomer::PurchasingCustomer(int accountType, Customer* customer) :

	m_accountType(accountType),
	m_customer(customer)

{}

#endif