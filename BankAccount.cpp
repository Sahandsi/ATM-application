//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "BankAccount.h"
#include "Constants.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
	: balance_(0.0)
{}
BankAccount::~BankAccount()
{}

BankAccount::BankAccount(const string& acctNum, const TransactionList& transList, const Date& cd, const double balance)
	:	accountNumber_(acctNum),
		transactions_(transList),
		creationDate_(cd),
		balance_(balance)
{} 

//____other public member functions

const string BankAccount::getAccountNumber() const {
	return accountNumber_;
}
const Date BankAccount::getCreationDate() const {
	return creationDate_;
}
double BankAccount::getBalance() const {
	return balance_;
}
const TransactionList BankAccount::getTransactions() const {
	return transactions_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}
void BankAccount::produceTransactionsUpToDate(const Date& date, int& size, string& transactionString) const
{
	TransactionList trl = transactions_.getTransactionsUpToDate(date);
	transactionString = trl.toFormattedString();
	size = trl.size();
}
//static
const string BankAccount::getAccountType(const string& filename) {
	return getAccountType(filename[13]); //14th char from the filename ("data/account_101.txt")
}
//static
const string BankAccount::getAccountType(char n) {
	//return account type ("BANK" for '0', "CURRENT" for '1', etc. or "UNKNOWN") 
	//(simply) identify type/class of account from the account number
	//'0' for bank account, '1' for current account, '2' for saving account, etc.
	switch (n)
	{
	case BANKACCOUNT_TYPE:		return "BANK"; 
//	case CURRENTACCOUNT_TYPE:	return "CURRENT"; break;
//etc..
	default:					return "UNKNOWN";
	}
}

void BankAccount::recordDeposit(double amountToDeposit) {
	//create a deposit transaction
	Transaction aTransaction("deposit_to_ATM", amountToDeposit);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(amountToDeposit);			//increase balance_
}

void BankAccount::recordDeletionOfTransactionUpToDate(const Date& date) 
{
	transactions_.deleteTransactionsUpToDate(date);
}

double BankAccount::maxBorrowable() const {
	//return borrowable amount
	return balance_;
}

bool BankAccount::canWithdraw(double amountToWithdraw) const {
	//check if enough money in account
	return amountToWithdraw <= maxBorrowable();
}
bool BankAccount::canTransferIn(double amount) const
{
	// will be differnt for other bank accounts such as a child account
	// this method will be virtual for question 5 as well as the method below
	return true;
}

const bool BankAccount::canTransferOut(double amount) const
{
	// check if the balance remaining after transfer will be greater than zero
	return ((balance_ - amount) >= 0.0);
}

void BankAccount::recordTransferOut(double amount, const string& transferAccountNum)
{
	// active account. adding new transaction and updating the balance.
	string strTransaction = ("transfer_to_" + transferAccountNum);
	Transaction inTransaction(strTransaction, amount);
	transactions_.addNewTransaction(inTransaction);
	updateBalance(-amount); // decrease balance from active account
}

void BankAccount::recordTransferIn(double amount, const string& activeAccountNum)
{
	// transfer account. adding new transaction and updating the balance.
	string strTransaction = ("transfer_from_" + activeAccountNum);
	Transaction inTransaction(strTransaction, amount);
	transactions_.addNewTransaction(inTransaction);
	updateBalance(amount); // increase balance on transfer account
}



void BankAccount::recordWithdrawal(double amountToWithdraw) {
	//create a withdrawal transaction
	Transaction aTransaction("withdrawal_from_ATM", -amountToWithdraw);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-amountToWithdraw);			//decrease balance_
}

void BankAccount::produceTransactionsForAmount(double amount, string& transactionString, int& size) const
{
	TransactionList trl = transactions_.getTransactionsForAmount(amount);
	size = trl.size();
	transactionString = trl.toFormattedString();
}

void BankAccount::produceTransactionsForTitle(const string& title, string& transString, int& size) const
{
	TransactionList trl = transactions_.getTransactionsForTitle(title);
	size = trl.size();
	transString = trl.toFormattedString();
}

void BankAccount::produceTransactionsForDate(const Date & date, string & transString, int & size) const
{
	TransactionList trl = transactions_.getTransactionsForDate(date);
	size = trl.size();
	transString = trl.toFormattedString();
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}
const string BankAccount::prepareFormattedMiniAccountDetails() const
{
	assert(getAccountType(accountNumber_[0]) != "UNKNOWN");
	ostringstream os;

	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE:         \234" << setw(10) << balance_;
	os << "\n      AVAILABLE FUNDS: \234" << setw(10) << maxBorrowable();
	os << "\n      ----------------------------------------";
	return os.str();
}
void BankAccount::readInBankAccountFromFile(const string& fileName) {
	ifstream fromFile;
	fromFile.open(fileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		fromFile >> (*this);  	//read  all info from bank account file
	fromFile.close();			//close file: optional here
}
TransactionList BankAccount::produceNMostRecentTransactions(int number, string& transString, double& totalTrans) const
{
	TransactionList trl = transactions_.getMostRecentTransactions(number);
	totalTrans = trl.getTotalTransactions();
	transString = trl.toFormattedString();
	return trl;
}
void BankAccount::storeBankAccountInFile(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& BankAccount::putDataInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	putAccountDetailsInStream(os);			//put bank account core information in stream
	putTransactionInStream(os);				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putTransactionInStream(ostream& os) const {
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountNumber_ << "\n";			//put account number
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& BankAccount::getDataFromStream(istream& is) {
	//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	getTransactionsDataFromStream(is);		//get all transactions from stream (if any)
	return is;
}
istream& BankAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountNumber_;					//get account number
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}
istream& BankAccount::getTransactionsDataFromStream(istream& is) {
	is >> transactions_;					//get all transactions from stream (if any)
	return is;
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------
void BankAccount::updateBalance(double amount) {
	balance_ += amount;   //add/take amount to/from balance_
}
const string BankAccount::prepareFormattedAccountDetails() const
{
	assert(getAccountType(accountNumber_[0]) != "UNKNOWN");
	ostringstream os;

	os << "\n      ACCOUNT TYPE:    " << getAccountType(accountNumber_[0]) << " ACCOUNT";
	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << "\n      CREATION DATE:   " << creationDate_.toFormattedString();
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE:         \234" << setw(10) << balance_;
	os << "\n      ----------------------------------------";
	return os.str();
}

const string BankAccount::prepareFormattedTransactionList() const
{
	ostringstream os;

	if (!transactions_.size() == 0)
	{
		os << "\n      TRANSACTIONS:";
		os << transactions_.toFormattedString();
	}
	else
	{
		os << "\n      NO TRANSACTIONS IN BANK ACCOUNT!";
	}

	return os.str();
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
	//put (unformatted) BankAccount details in stream
	return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
	//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}
