//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
#include <cassert>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    ~BankAccount();

	BankAccount(const string & acctNum, const TransactionList & transList, const Date & cd, const double balance);

	//getter (assessor) functions
    const string getAccountNumber() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool isEmptyTransactionList() const;
	void produceTransactionsUpToDate(const Date& d, int& size, string& transactionString) const;
	//other operations
	
	const string prepareFormattedStatement() const;
	virtual void recordDeposit(double amount);
	void recordDeletionOfTransactionUpToDate(const Date& date);
	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;
	virtual bool canTransferIn(double amount) const;
	virtual const bool canTransferOut(double amount) const;
	void recordTransferOut(double amount, const string & transferAccountNum);
	virtual void recordTransferIn(double amount, const string & activeAccountNum);
    void recordWithdrawal(double amount);
	void produceTransactionsForAmount(double amount, string& transString, int& size) const;
	void produceTransactionsForTitle(const string& title, string& transString, int& size) const;
	void produceTransactionsForDate(const Date& date, string& transString, int& size) const;
	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	TransactionList produceNMostRecentTransactions(int number, string& transString, double& totalTrans) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	virtual istream& getAccountDataFromStream(istream& is);

	virtual const string prepareFormattedAccountDetails() const = 0;
	const string prepareFormattedMiniAccountDetails() const;
	const string prepareFormattedTransactionList() const;
	
	static const string getAccountType(const string& filename);
	static const string getAccountType(char n);
	
private:
    //data items
    string accountNumber_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	void updateBalance(double amount);
	ostream& putTransactionInStream(ostream& os) const;
	istream& getTransactionsDataFromStream(istream& is);
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
