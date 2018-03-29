#include "CurrentAcount.h"

// implicitly call the bank account constructor
CurrentAccount::CurrentAccount() : overdraftLimit_(0.0)
{}

//explicitly call the bank account constructor
CurrentAccount::CurrentAccount(const string& acctNum, 
		const TransactionList& transList, 
		const Date& cd, const double balance, const double overdraftLimit) 
		: BankAccount(acctNum, transList, cd, balance), overdraftLimit_(overdraftLimit)
{}


CurrentAccount::~CurrentAccount()  
{}

double CurrentAccount::getOverdraftLimit() const
{
	return overdraftLimit_;
}

ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << getAccountNumber() << "\n";			//put account number
	os << getCreationDate() << "\n";			//put creation date
	os << getBalance() << "\n";					//put balance
	os << overdraftLimit_ << "\n";				//put overdraft limit (accessible in this class)
	return os;
}


istream& CurrentAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream by calling its version
	BankAccount::getDataFromStream(is);
	// store overdraft limit from the stream
	is >> overdraftLimit_;
	return is;
}



const string CurrentAccount::prepareFormattedAccountDetails() const
{
	// get the account type based on the first character of the account number
	assert(getAccountType(getAccountNumber()[0]) != "UNKNOWN");
	ostringstream os;

	os << BankAccount::prepareFormattedAccountDetails();
	os << "\n      OVERDRAFT LIMIT:         \234" << setw(10) << overdraftLimit_;
	os << "\n      ----------------------------------------";
	return os.str();
}

const bool CurrentAccount::canTransferOut(double amount) const
{
	// checking if transfer results in balance lower than the overdraft limit
	return ((amount >= 0) && ((getBalance() - amount) >= overdraftLimit_));
}

