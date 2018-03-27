#ifndef ISAAccountH
#define ISAAccountH

#include "SavingsAccount.h"

class ISAAccount : public SavingsAccount
{
public:
	// constructors and destructors
	ISAAccount(const string & acctNum, const TransactionList & transList,
		const Date & cd, const double balance, const double minimumBalance,
		const double maxYearlyDeposit, const double currentYearlyDeposit,
		const Date& endDepositPeriod);
	~ISAAccount();

	// accessors
	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;

	// mutators
	void updateCurrentYearlyDeposit(const double yearlyDeposit);

	// virtual functions
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual const string prepareFormattedAccountDetails() const;
	virtual bool canTransferIn(double amount) const;
	virtual void recordTransferIn(double amount, const string & activeAccountNum); // to update yearly deposit
	virtual void recordDeposit(double amount);

private:
	double maximumYearlyDeposit_, currentYearlyDeposit_;
	Date endDepositPeriod_;
};







#endif // !ISAAccountH
