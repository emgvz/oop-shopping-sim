#include <iostream>
#include "Transaction.h"

std::string_view convertTransactionTypeToStr(Transaction::Type type)
{
	switch (type)
	{
	case Transaction::Withdrawal:
		return "Withdrawal";
	case Transaction::Deposit:
		return "Deposit";
	case Transaction::Purchase:
		return "Purchase";
	}
}

std::string_view convertStatusTypeToStr(Transaction::Status status)
{
	switch (status)
	{
	case Transaction::Successful:
		return "Successful";
	case Transaction::Unsuccessful:
		return "Unsuccessful";
	}
}

void Transaction::printTransaction() const
{
	std::cout << std::left << std::setw(10) << getTransactionID();
	std::cout << std::setw(20) << convertBankAccountTypeToStr(getAccountType());
	std::cout << std::setw(20) << convertTransactionTypeToStr(getTransactionType());
	std::cout << std::right << std::setw(20) << std::format("${}", getTransactionAmount());
	std::cout << std::right << std::setw(15) << std::format("${}", getBalanceAfter());
	std::cout << std::right << std::setw(15) << convertStatusTypeToStr(getTransactionStatus());
}
