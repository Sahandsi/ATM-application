#ifndef SavingsAccountH
#define SavingsAccountH

#include "BankAccount.h"
class SavingsAccount : public BankAccount
{
public:
	SavingsAccount(const double minimumBalance);
	SavingsAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double minimumBalance);
	~SavingsAccount();

	// pure virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const = 0;
	virtual istream& getAccountDataFromStream(istream& is) = 0;

	// accessors
	double getMinimumBalance() const;

	
	// virtual functions
	virtual const bool canTransferOut(double amount) const;

private:
	double minimumBalance_;
};

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator




#endif // !SavingsAccountH

