//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


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
	return ((amount >= 0.0) && ((amount >= minimumPaidIn_) 
		&& (amount <= maximumPaidIn_)) /*&& (amount <= maxBorrowable())*/);
}

double ChildAccount::maxBorrowable() const
{

	return 0;
}

bool ChildAccount::canWithdraw(double amount) const
{
	return false;
}




