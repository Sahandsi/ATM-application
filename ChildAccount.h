//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


#ifndef ChildAccountH
#define ChildAccountH

#include "SavingsAccount.h";

class ChildAccount : public SavingsAccount
{
public:
	
	ChildAccount();
	ChildAccount(const string & acctNum, const TransactionList & transList, 
				const Date & cd, const double balance, const double minimumBalance, 
				const double minimumPaidIn, const double maximumPaidIn);
	~ChildAccount();

	// accessors
	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;

	// virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);

	virtual const string prepareFormattedAccountDetails() const;
	virtual bool canTransferIn(double amount) const;
	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;

private:
	double maximumPaidIn_, minimumPaidIn_;
};

#endif // !ChildAccountH
