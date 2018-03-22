//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)


#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"
<<<<<<< HEAD
#include "Time.h"
=======

>>>>>>> 624b5ba771d6d3a06ddb60252178327263f2488a

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class UserInterface {
public:
	void showByeScreen() const;

	int showMainMenuAndGetCommand() const;
	int showCardMenuAndGetCommand(const string& cardNum) const;
	int showAccountMenuAndGetCommand(const string& accNum) const;
	void showSearchMenu() const;
	void showErrorInvalidCommand() const;
	void wait() const;
	void endProgram() const;
	void showTransactionsUpToDateOnScreen(bool isEmpty, const Date& date, int size, const string& transactionString) const;
	void showMatchingTransactionsOnScreen(double amount, int size, const string& transString) const;
	void showMatchingTransactionsOnScreen(const string& title, int size, const string& transString) const;
	void showMatchingTransactionsOnScreen(const Date& date, int size, const string& transString) const;
	const string readInCardToBeProcessed() const;
	Date readInValidDate(const Date& cd) const;
	int readInSearchCommand() const;
	string readInTitle() const;
	double readInAmount()  const;
	Date readInDate(const Date& date) const;
	void showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void showCardAccounts(const string& cardNum, const string& cardSt) const;
	const string readInAccountToBeProcessed() const;
	bool readInConfirmDeletion() const;
	void showDeletionOfTransactionsUpToDateOnScreen(int size, const Date& date, bool deletionConfirmed) const;
	void showNoTransactionsOnScreen() const;
	void showMatchingTransactionsOnScreen() const;
	void showValidateAccountOnScreen(int valid, const string& acctNum) const;
	void showFundsAvailableOnScreen(bool isAccountEmpty, const string& statement, double totalMaxBorrowable) const;
	static const string cardFilename(const string& cn);
	static const string accountFilename(const string& an);

	double readInWithdrawalAmount() const;
	double readInDepositAmount() const;
	int readInNumberOfTransactions() const;

	void showProduceBalanceOnScreen(double bal) const;
	void showDepositOnScreen(bool auth, double deposit) const;
	void showWithdrawalOnScreen(bool auth, double withdrawal) const;
	void showStatementOnScreen(const string&) const;
	void showMiniStatementOnScreen(bool, double, string)const;

private:
	//support functions
	int readInCommand() const;
	double readInPositiveAmount() const;
	int readInPositiveNumber() const;
	void outputHeader(const string&) const;
	string askForInput(const string&) const;
	void outputLine(const string&) const;
};

#endif
