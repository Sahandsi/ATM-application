#ifndef CurrentAccountH
#define CurrentAccountH

#include "BankAccount.h"
class CurrentAccount : public BankAccount
{
public:
	CurrentAccount(const double overdraftLimit);
	CurrentAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double overdraftLimit);
	~CurrentAccount();

	// accessors
	double getOverdraftLimit() const;


	// virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	/*virtual istream& getAccountDataFromStream(istream& is);*/

	virtual const string prepareFormattedAccountDetails() const;
	virtual const bool canTransferOut(double amount) const;

private:
	double overdraftLimit_;
};

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator




#endif // !CurrentAccountH

