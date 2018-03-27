#include "CurrentAcount.h"

// implicitly call the bank account constructor
CurrentAccount::CurrentAccount(const double overdraftLimit) : overdraftLimit_(overdraftLimit)
{}

CurrentAccount::CurrentAccount(const string& acctNum, 
		const TransactionList& transList, 
		const Date& cd, const double balance, const double overdraftLimit) 
		: BankAccount("CURRENT", acctNum, transList, cd, balance), overdraftLimit_(overdraftLimit)
{}

//explicitly call the bank account constructor
CurrentAccount::~CurrentAccount()  
{}

double CurrentAccount::getOverdraftLimit() const
{
	return overdraftLimit_;
}

