//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


#ifndef CurrentAccountH
#define CurrentAccountH

#include "BankAccount.h"
class CurrentAccount : public BankAccount
{
public:
	CurrentAccount();
	CurrentAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance, const double overdraftLimit);
	~CurrentAccount();

	// accessors
	double getOverdraftLimit() const;


	// virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;
	virtual const string prepareFormattedAccountDetails() const;
	virtual const bool canTransferOut(double amount) const;

private:
	double overdraftLimit_;
};




#endif // !CurrentAccountH

