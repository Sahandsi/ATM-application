#include "ChildAccount.h"

// default constructor
ChildAccount::ChildAccount() 
	: SavingsAccount(), minimumPaidIn_(0), maximumPaidIn_(0)
{}

ChildAccount::ChildAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double minimumBalance, const double minimumPaidIn, const double maximumPaidIn) 
	: SavingsAccount(acctNum, transList, cd, balance, minimumBalance), 
	minimumPaidIn_(minimumPaidIn), maximumPaidIn_(maximumPaidIn)
{}

ChildAccount::~ChildAccount()
{}

double ChildAccount::getMaximumPaidIn() const
{
	return maximumPaidIn_;
}

double ChildAccount::getMinimumPaidIn() const
{
	return minimumPaidIn_;
}



ostream& ChildAccount::putAccountDetailsInStream(ostream & os) const
{
	//put (unformatted) BankAccount details in stream
	os << getAccountNumber() << "\n";			//put account number
	os << getCreationDate() << "\n";			//put creation date
	os << getBalance()	 << "\n";				//put balance
	os << getMinimumBalance() << "\n";			//put mimimum balance (from saving account)
	os << minimumPaidIn_ << "\n";				//put maximum paid in
	os << maximumPaidIn_ << "\n";				//put minimum paid in
	return os;
}

istream& ChildAccount::getAccountDataFromStream(istream& is)
{
	SavingsAccount::getAccountDataFromStream(is);
	is >> minimumPaidIn_;
	is >> maximumPaidIn_;
	return is;
}

const string ChildAccount::prepareFormattedAccountDetails() const
{
	assert(getAccountType(getAccountNumber()[0]) != "UNKNOWN");
	ostringstream os;

	os << SavingsAccount::prepareFormattedAccountDetails();
	os << "\n      MAXIMUM PAID IN:         \234" << setw(10) << maximumPaidIn_;
	os << "\n      MINIMUM PAID IN:         \234" << setw(10) << minimumPaidIn_;
	os << "\n      ----------------------------------------";
	return os.str();
}


bool ChildAccount::canTransferIn(double amount) const
{
	// restricted money that can be transferred into this child account
	return ((amount >= 0) && ((amount >= minimumPaidIn_) && (amount <= maximumPaidIn_)));
}

double ChildAccount::maxBorrowable() const
{
	
	double amountFromSavings = SavingsAccount::maxBorrowable();

	// if less money is available the minimum amount of money that can be withdrawn
	if (amountFromSavings < minimumPaidIn_)
	{
		return 0.0; // cannot withdraw any money
	}
	// in between 
	else if (amountFromSavings < maximumPaidIn_)
	{
		return minimumPaidIn_;
	}
	// above maximum paid in
	else 
	{
		return maximumPaidIn_;
	}
}

bool ChildAccount::canWithdraw(double amount) const
{
	// check if amount is valid and less than max borrowable 
	// and balance remains greater than minimum balance
	return ((amount >= 0.0) && ((amount >= minimumPaidIn_) 
		&& (amount <= maximumPaidIn_)) && (amount <= maxBorrowable()) 
		&& (SavingsAccount::canWithdraw(amount)));
}




