#ifndef ChildAccountH
#define ChildAccountH

#include "SavingsAccount.h"

class ChildAccount : public SavingsAccount
{
public:
	
	ChildAccount(const double minimumBalance);
	ChildAccount(const string & acctNum, const TransactionList & transList, 
				const Date & cd, const double balance, const double minimumBalance, 
				const double minimumPaidIn, const double maximumPaidIn);
	~ChildAccount();

	// accessors
	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;

	// virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	/*virtual istream& getAccountDataFromStream(istream& is);*/

	virtual const string prepareFormattedAccountDetails() const;
	virtual bool canTransferIn(double amount) const;

private:
	double maximumPaidIn_, minimumPaidIn_;
};




#endif // !ChildAccountH

