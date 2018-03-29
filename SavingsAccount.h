#ifndef SavingsAccountH
#define SavingsAccountH

#include "BankAccount.h"
class SavingsAccount : public BankAccount
{
public:
	SavingsAccount();
	SavingsAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double minimumBalance);
	~SavingsAccount();

	// pure virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const = 0;
	virtual istream& getAccountDataFromStream(istream& is) = 0;
	virtual const string prepareFormattedAccountDetails() const;
	// accessors
	double getMinimumBalance() const;

	
	// virtual functions
	virtual const bool canTransferOut(double amount) const;
	virtual bool canWithdraw(double amount) const;
	virtual double maxBorrowable() const;

private:
	double minimumBalance_;
};

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator




#endif // !SavingsAccountH

