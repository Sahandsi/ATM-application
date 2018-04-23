//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"
#include "Time.h"


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
	void showFundsAvailableOnScreen(bool isAccountEmpty, const string & statement, double totalMaxBorrowable) const;
	void showMatchingTransactionsOnScreen(double amount, int size, const string& transString) const;
	void showMatchingTransactionsOnScreen(const string& title, int size, const string& transString) const;
	void showMatchingTransactionsOnScreen(const Date& date, int size, const string& transString) const;
	void showTransferOnScreen(bool trOutOk, bool trInOk, double transferAmount) const;
	const string readInCardToBeProcessed() const;
	Date readInValidDate(const Date& cd) const;
	int readInSearchCommand() const;
	const double readInTransferAmount() const;
	string readInTitle() const;
	double readInAmount()  const;
	Date readInDate(const Date& date) const;
	void showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void showCardOnScreen(const string & cardDetails) const;
	void showCardAccounts(const string& cardNum, const string& cardSt) const;
	const string readInAccountToBeProcessed() const;
	bool readInConfirmDeletion() const;
	void showDeletionOfTransactionsUpToDateOnScreen(int size, const Date& date, bool deletionConfirmed) const;
	void showNoTransactionsOnScreen() const;
	void showMatchingTransactionsOnScreen() const;
	void showValidateAccountOnScreen(int valid, const string& acctNum) const;

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
