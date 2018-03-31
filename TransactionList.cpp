//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {

	//listOfTransactions_.addInFront(tr);
	// insert at beginning of the list
    listOfTransactions_.insert(listOfTransactions_.begin(), tr);
	
}
const Transaction TransactionList::newestTransaction() const {
    //return (listOfTransactions_.first());
	// returns the latest transaction (head)
	return listOfTransactions_.front();
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
	// returns the older transactions (tail)
    trlist.deleteFirstTransaction();
    return trlist;
}

TransactionList TransactionList::getTransactionsUpToDate(const Date & date) const
{
	TransactionList copytr(*this);
	TransactionList rettr;

	// loop through all the transactions
	while (copytr.size() > 0)
	{
		if (copytr.newestTransaction().getDate() <= date)
		{
			rettr.addNewTransaction(copytr.newestTransaction()); // add to the return transaction
		}
		copytr.deleteFirstTransaction(); // move along the copy list
	}
	return rettr;
}

void TransactionList::deleteTransactionsUpToDate(const Date& date)
{
	// this-> refers to the actual transaction list not the copy
	// *this is used to create a copy of transactions list to loop over (copytr)

	TransactionList copytr(*this); // grab a copy to loop over
	while (copytr.size() > 0)
	{
		if (copytr.newestTransaction().getDate() <= date)
		{
			this->deleteGivenTransaction(copytr.newestTransaction());
		}
		copytr.deleteFirstTransaction(); // move along the copy list
	}
}


TransactionList TransactionList::getTransactionsForAmount(double amount) const
{
	TransactionList copytr(*this);
	TransactionList rettr;

	// loop through all the transactions
	while (copytr.size() > 0)
	{
		if (copytr.newestTransaction().getAmount() == amount)
		{
			rettr.addNewTransaction(copytr.newestTransaction()); // add to the return transaction
		}
		copytr.deleteFirstTransaction(); // move along the copy list
	}
	return rettr;
}
TransactionList TransactionList::getTransactionsForTitle(const string & title) const
{
	TransactionList copytr(*this);
	TransactionList rettr;

	// loop through all the transactions
	while (copytr.size() > 0)
	{
		//https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
		if (copytr.newestTransaction().getTitle().find(title) != string::npos)
		{
			rettr.addNewTransaction(copytr.newestTransaction()); // add to the return transaction
		}
		copytr.deleteFirstTransaction(); // move along the copy list
	}
	return rettr;
}
TransactionList TransactionList::getTransactionsForDate(const Date& date) const
{
	TransactionList copytr(*this);
	TransactionList rettr;

	// loop through all the transactions
	while (copytr.size() > 0)
	{
		//https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
		if (copytr.newestTransaction().getDate() == date)
		{
			rettr.addNewTransaction(copytr.newestTransaction()); // add to the return transaction
		}
		copytr.deleteFirstTransaction(); // move along the copy list
	}
	return rettr;
}
void TransactionList::deleteFirstTransaction() {
    //listOfTransactions_.deleteFirst();
	listOfTransactions_.pop_front();
}

void TransactionList::deleteGivenTransaction(const Transaction& tr) {
    listOfTransactions_.remove(tr);
}
int TransactionList::size() const {
    return (listOfTransactions_.size());
}
//option 6
TransactionList TransactionList::getMostRecentTransactions(int number) const {
	TransactionList tempList(*this);
	TransactionList rettr;
	// get the latest transactions for a certain number
	while (tempList.size() > 0 && number != 0)
	{
		rettr.addNewTransaction(tempList.newestTransaction());
		tempList.deleteFirstTransaction();
		number--;
	}
	return rettr;
}
//option 6
double TransactionList::getTotalTransactions()
{
	double total = 0;
	TransactionList tempList(*this);

	while (tempList.size() > 0)
	{
		total = total + tempList.newestTransaction().getAmount();
		tempList.deleteFirstTransaction();
	}

	return total;
}
const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os_transactionlist << endl << tempTrList.newestTransaction().toFormattedString();
        tempTrList.deleteFirstTransaction();
    }
	return (os_transactionlist.str());
}

ostream& TransactionList::putDataInStream(ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream(istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while (is) 	//while not end of file
	{
		listOfTransactions_.push_back(aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const TransactionList& aTransactionList) {
    return (aTransactionList.putDataInStream(os));
}
istream& operator>>(istream& is, TransactionList& aTransactionList) {
	return (aTransactionList.getDataFromStream(is));
}
