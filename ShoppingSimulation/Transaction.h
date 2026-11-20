#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "BankAccount.h"
#include "Product.h"
#include <string>
#include <string_view>
#include <chrono>


class Transaction
{
public:
	enum Type
	{
		Withdrawal,
		Deposit,
		Purchase
	};

	enum Status
	{
		Successful,
		Unsuccessful
	};

	Transaction() = default;

	// constructor for Transcation::Type == Withdrawal OR Deposit
	Transaction(BankAccount::Type accountType,
				Transaction::Type transactionType,
				double transactionAmount,
				double balanceAfter,
				Transaction::Status status);
	// date and time Hours::Minutes::Seconds

	// constructor for Transaction::Type == Purchase
	Transaction(BankAccount::Type accountType,
				Transaction::Type transactionType,
				Product::Type productType,
				std::string_view productName,
		        double unitPrice,
				int transactionQuantity,
				double transactionAmount,
				double balanceAfter);
	// date and time will be added later in this format Hours::Minutes::Seconds
	

	// setters
	void setBankAccountType(BankAccount::Type accountType) { m_accountType = accountType; }
	void setTransactionType(Transaction::Type transactionType) { m_transactionType = transactionType; }
	void setProductType(Product::Type productType) { m_productType = productType; }
	void setProductName(std::string_view productName) { m_productName = productName; }
	void setUnitPrice(double productUnitPrice) { m_unitPrice = productUnitPrice; }
	void setTransactionQuantity(int transactionQuantity) { m_transactionQuantity = transactionQuantity; }
	void setTransactionAmount(double transactionAmount){ m_transactionAmount = transactionAmount; }
	void setBalanceAfter(double balanceAfter) { m_balanceAfter = balanceAfter; }

	// getters
	int getTransactionID() const { return m_transactionID; }
	BankAccount::Type getAccountType() const { return m_accountType; }
	Transaction::Type getTransactionType() const { return m_transactionType; }
	Product::Type getProductType() const { return m_productType; }
	std::string_view getProductName() const { return m_productName; }
	double getUnitPrice() const { return m_unitPrice; }
	int getTransactionQuantity() const { return m_transactionQuantity; }
	double getTransactionAmount() const { return m_transactionAmount; }
	double getBalanceAfter() const { return m_balanceAfter; }
	Transaction::Status getTransactionStatus() const { return m_transactionStatus; }
	

	void printTransaction() const;
	
	
private:

	static inline int s_idIdentifier { 1 };
	int m_transactionID{};
	BankAccount::Type m_accountType{};
	Transaction::Type m_transactionType{};
	Transaction::Status m_transactionStatus{};

	// details will be N/A if customer's m_transactionType == Withdrawal or Deposit
	std::string m_productName{"N/A"};
	Product::Type m_productType{};
	double m_unitPrice{0.0};
	int m_transactionQuantity{0};
	double m_transactionAmount{0.0};

	double m_balanceAfter{};
	// time and date that transaction happened? m_timestamp {};

};

inline Transaction::Transaction(BankAccount::Type accountType,
	Transaction::Type transactionType,
	double transactionAmount,
	double balanceAfter,
	Transaction::Status status
	) :

	m_transactionID{ s_idIdentifier++ },
	m_accountType{ accountType },
	m_transactionType{ transactionType },
	m_transactionAmount{ transactionAmount },
	m_balanceAfter{ balanceAfter },
	m_transactionStatus { status}
	{}

inline Transaction::Transaction(BankAccount::Type accountType,
	Transaction::Type transactionType,
	Product::Type productType,
	std::string_view productName,
	double unitPrice,
	int transactionQuantity,
	double transactionAmount,
	double balanceAfter
	) :

	m_transactionID { s_idIdentifier++},
	m_accountType { accountType },
	m_transactionType { transactionType},
	m_productType { productType },
	m_productName { productName },
	m_unitPrice { unitPrice },
	m_transactionQuantity { transactionQuantity },
	m_transactionAmount { transactionAmount },
	m_balanceAfter { balanceAfter }
	{}

std::string_view convertTransactionTypeToStr(Transaction::Type type);

#endif



