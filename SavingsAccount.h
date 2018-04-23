//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


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
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is) = 0;
	virtual const string prepareFormattedAccountDetails() const = 0;
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

