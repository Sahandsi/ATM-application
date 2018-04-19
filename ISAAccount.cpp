#include "ISAAccount.h"




// default constructor
ISAAccount::ISAAccount() : 
	SavingsAccount(), 
	maximumYearlyDeposit_(0), 
	currentYearlyDeposit_(0),
	endDepositPeriod_(Date())
{

}

ISAAccount::ISAAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double minimumBalance, const double maxYearlyDeposit, const double currentYearlyDeposit, const Date & endDepositPeriod)
	: SavingsAccount(acctNum, transList, cd, balance, minimumBalance),
	maximumYearlyDeposit_(maxYearlyDeposit),
	currentYearlyDeposit_(currentYearlyDeposit_),
	endDepositPeriod_(endDepositPeriod_)
{}

ISAAccount::~ISAAccount()
{}

double ISAAccount::getMaximumYearlyDeposit() const
{
	return maximumYearlyDeposit_;
}

double ISAAccount::getCurrentYearlyDeposit() const
{
	return currentYearlyDeposit_;
}

Date ISAAccount::getEndDepositPeriod() const
{
	return endDepositPeriod_;
}

void ISAAccount::updateCurrentYearlyDeposit(const double yearlyDeposit)
{
	currentYearlyDeposit_ += yearlyDeposit;
}

ostream & ISAAccount::putAccountDetailsInStream(ostream & os) const
{
	// add all the account details to the stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit_ << "\n";
	os << currentYearlyDeposit_ << "\n";
	os << endDepositPeriod_ << "\n";
	return os;
}

istream & ISAAccount::getAccountDataFromStream(istream & is)
{
	SavingsAccount::getAccountDataFromStream(is);
	is >> maximumYearlyDeposit_;
	is >> currentYearlyDeposit_;
	is >> endDepositPeriod_;
	return is;
}

const string ISAAccount::prepareFormattedAccountDetails() const
{
	ostringstream os;
	os << SavingsAccount::prepareFormattedAccountDetails();
	os << "\n      CURRENT YEARLY DEPOSIT:    " << currentYearlyDeposit_;
	os << "\n      MAX YEARS DEPOSIT:    " << "\234" << setw(10) << maximumYearlyDeposit_;
	os << "\n      DEPOSIT RENEWAL DATE:    " << endDepositPeriod_.toFormattedString();
	os << "\n      ----------------------------------------";
	return os.str();
}


bool ISAAccount::canTransferIn(double amount) const
{
	return ((amount >= 0.0) && (currentYearlyDeposit_ + amount <= maximumYearlyDeposit_)
		&& Date::currentDate() < endDepositPeriod_);
}


void ISAAccount::recordTransferIn(double amount, const string & activeAccountNum)
{
	// updating bank account balance and transactions
	BankAccount::recordTransferIn(amount, activeAccountNum);
	// update the yearly deposit
	updateCurrentYearlyDeposit(amount);
}

void ISAAccount::recordDeposit(double amount)
{
	if (canTransferIn(amount))
	{
		BankAccount::recordDeposit(amount);
		// update currently yearly deposit
		updateCurrentYearlyDeposit(amount);
	}
}

bool ISAAccount::canWithdraw(double amount) const
{
	// only need to check the savings account version
	return SavingsAccount::canWithdraw(amount);
}

double ISAAccount::maxBorrowable() const
{
	return SavingsAccount::maxBorrowable();
}






