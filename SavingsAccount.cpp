#include "SavingsAccount.h"


// implicit constructor call to BankAccount
SavingsAccount::SavingsAccount()
	: minimumBalance_(0)
{}

// explicit constructor call to BankAccount
SavingsAccount::SavingsAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double minimumBalance)
	: BankAccount(acctNum, transList, cd, balance), minimumBalance_(minimumBalance)
{}

// destructor
SavingsAccount::~SavingsAccount()
{}


double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance_;
}

const bool SavingsAccount::canTransferOut(double amount) const
{
	// checking if transfer results in balance lower than the minimum balance
	return ((amount >= 0) && ((getBalance() - amount) >= minimumBalance_));
}

ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << minimumBalance_ << "\n";				//put minimum balance (accessible in this class)
	return os;
}

istream& SavingsAccount::getAccountDataFromStream(istream& is)
{
	// store the results in the bank account data members and in savings account data members
	BankAccount::getAccountDataFromStream(is);
	is >> minimumBalance_;
	return is;
}

const string SavingsAccount::prepareFormattedAccountDetails() const
{
	ostringstream os;
	os << BankAccount::prepareFormattedAccountDetails();
	os << "MINIMUM BALANCE " << "\234" << setw(10) << minimumBalance_;
	os << "\n      ----------------------------------------";
	return os.str();
}

