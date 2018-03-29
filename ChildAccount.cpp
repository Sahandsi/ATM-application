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
	os << maximumPaidIn_ << "\n";				//put maximum paid in
	os << minimumPaidIn_ << "\n";				//put minimum paid in
	return os;
}

istream& ChildAccount::getAccountDataFromStream(istream& is)
{
	SavingsAccount::getAccountDataFromStream(is);
	is >> maximumPaidIn_;
	is >> minimumPaidIn_;
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

//double ChildAccount::maxBorrowable() const
//{
//	//// if less money is available than depositing
//	//double maxBorrowableFromSaving = SavingsAccount::maxBorrowable();
//	//if (maxBorrowableFromSaving < minimumPaidIn_)
//	//{
//	//	return 0.0;
//	//}
//	//else if(maxBorrowableFromSaving > maximumPaidIn_)
//	//{
//	//	return SavingsAccount::maxBorrowable() - maximumPaidIn_;
//	//}
//}




