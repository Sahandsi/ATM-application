//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "ATM.h"

//---------------------------------------------------------------------------
//ATM: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

ATM::ATM()
	: p_theActiveAccount_(nullptr), p_theCard_(nullptr), theUI_()
{}

ATM::~ATM()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCard_ == nullptr);
}

//____other public member functions

void ATM::activateCashPoint() {
	int command( theUI_.showMainMenuAndGetCommand());
	while (command != QUIT_COMMAND)
	{
		executeCardCommand(command);
		theUI_.wait();
		command = theUI_.showMainMenuAndGetCommand();
	}
	theUI_.showByeScreen();
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void ATM::executeCardCommand(int option) {
	switch (option)
	{
		case 1:
		{
			string cardNum(theUI_.readInCardToBeProcessed());
			string cardFilename(theUI_.cardFilename(cardNum));
			int validCardCode(validateCard(cardFilename));	
			theUI_.showValidateCardOnScreen(validCardCode, cardNum);
			if (validCardCode == VALID_CARD) 
			{
				//dynamically create a card and store card data
				activateCard(cardFilename);

				//select request for active card 
				int option = theUI_.showCardMenuAndGetCommand(cardNum);
				while (option != QUIT_COMMAND)
				{
					switch (option)
					{
					case 1: m_card1_manageIndividualAccount();
						break;
					case 2: m_card2_showFundsAvailableOnAllAccounts();
						break;
						default:
							theUI_.showErrorInvalidCommand();
					}

					theUI_.wait();
					option = theUI_.showCardMenuAndGetCommand(cardNum);
				}

				//free memory space used by active card
				releaseCard();
			}
			break;
		}
		default:theUI_.showErrorInvalidCommand();
	}
}
void ATM::m_card1_manageIndividualAccount() {
	assert(p_theCard_ != nullptr);
	theUI_.showCardAccounts(p_theCard_->getCardNumber(), p_theCard_->toFormattedString());
	executeAccountCommand();
}
int ATM::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
		return UNKNOWN_CARD;
	else
		//card empty (exist but no bank account listed on card)
		if (!accountsListedOnCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}

void ATM::m_card2_showFundsAvailableOnAllAccounts() const
{
	assert(p_theCard_ != nullptr);
	double totalMaxBorrowable = 0;
	string mad = ""; // mini account details 
	List<string> accts = p_theCard_->getAccountsList();
	bool empty = accts.isEmpty(); // used to loop through the list
	bool emptyFirstTime = empty; // check if it was empty first time round
	while (!empty) // looping through all the acounts and getting the totol funds that can be withdrawn
	{
		string firstAccount = accts.first();
		BankAccount* pacct = activateAccount(theUI_.accountFilename(firstAccount));
		totalMaxBorrowable += pacct->maxBorrowable();
		mad += pacct->prepareFormattedMiniAccountDetails();
		// delete the bank account pointer
		releaseAccount(pacct, firstAccount);
		accts.deleteFirst();
		empty = accts.isEmpty();
	}

	theUI_.showFundsAvailableOnScreen(emptyFirstTime, mad, totalMaxBorrowable);

}

int ATM::validateAccount(const string& filename) const {
	//check that the account is valid 
	//NOTE: MORE WORK NEEDED here in case of transfer

	// TEMPORARY p_BA ACTIVATING A BANK ACCOUNT WITH THIS FILENAME
	BankAccount* p_tempBankAccount = activateAccount(filename);

	int accountState;
	if (!canOpenFile(filename))
		//account does not exist
		accountState = UNKNOWN_ACCOUNT;
	else
		//account type not recognised
		if (BankAccount::getAccountType(filename) == "UNKNOWN")
			//if (getAccountTypeCode(filename) == UNKNOWN_ACCOUNT_TYPE)
			accountState = INVALID_ACCOUNT_TYPE;
		else
			//unaccessible account (exists but not listed on card)
			if (!p_theCard_->onCard(filename))
				accountState = UNACCESSIBLE_ACCOUNT;
			else
				// if both of the account numbers are the same. same account is being used to transfer money
				if (p_theActiveAccount_ != nullptr && (p_theActiveAccount_->getAccountNumber() == p_tempBankAccount->getAccountNumber()))
					accountState = SAME_ACCOUNT;
				else
					//account valid (exists and accessible)
					accountState = VALID_ACCOUNT;

	// release the memory allocated to the temporary bank account
	if (p_tempBankAccount != nullptr)
		releaseAccount(p_tempBankAccount, filename);

	return accountState;
}
void ATM::executeAccountCommand() {
	assert(p_theActiveAccount_ == nullptr);
	//process from one account
	//select active account and check that it is valid
	const string anAccountNumber(theUI_.readInAccountToBeProcessed());
	const string bankAccountFilename(theUI_.accountFilename(anAccountNumber));
	const int validAccountCode(validateAccount(bankAccountFilename));
	theUI_.showValidateAccountOnScreen(validAccountCode, anAccountNumber);
	if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card and not already open
	{
		//dynamically create a bank account to store data from file
		p_theActiveAccount_ = activateAccount(bankAccountFilename);

		//select request for active account 
		int option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());
		while (option != QUIT_COMMAND)
		{
			switch (option)
			{
				case 1:	m_acct1_produceBalance();
					break;
				case 2: m_acct2_withdrawFromBankAccount();
					break;
				case 3:	m_acct3_depositToBankAccount();
					break;
				case 4:	m_acct4_produceStatement();
					break;
				case 6: m_acct6_showMiniStatement();
					break;
				case 7: m_acct7_searchForTransactions();
					break;
				case 8: m_acct8_clearTransactionsUpToDate();
					break;
				case 9: m_acct9_transferCashToAnotherAccount();
					break;
				default:theUI_.showErrorInvalidCommand();
			}
			theUI_.wait();
			option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());   //select another option
		}	

		//store new state of bank account in file and free bank account memory space
		p_theActiveAccount_ = releaseAccount(p_theActiveAccount_, bankAccountFilename);
	}
}

void ATM::searchTransactions() const
{
	theUI_.showSearchMenu();
	int option = theUI_.readInSearchCommand();
	switch (option)
	{
		case 0:
			m_trl1_showTransactionsForAmount();
			break;
		case 1:
			m_trl1_showTransactionsForTitle();
			break;
		case 2: 
			m_trl1_showTransactionsForDate();
		case 3: 
			return;
		default:
			break;
	}

}

void ATM::recordTransfer(double transferAmount, BankAccount* transferAccout)
{
	// transfer account
	string tAN = transferAccout->getAccountNumber();
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN);

	//active account
	string aAN = p_theActiveAccount_->getAccountNumber();
	transferAccout->recordTransferIn(transferAmount, aAN);
}

void ATM::m_trl1_showTransactionsForAmount() const
{
	string transString;
	int size;

	double amount = theUI_.readInAmount();
	p_theActiveAccount_->produceTransactionsForAmount(amount, transString, size);
	if (transString == "")
		theUI_.showMatchingTransactionsOnScreen();
	else 
		theUI_.showMatchingTransactionsOnScreen(amount, size, transString);
}

void ATM::m_trl1_showTransactionsForTitle() const
{
	string transString;
	int size;

	string title = theUI_.readInTitle();
	p_theActiveAccount_->produceTransactionsForTitle(title, transString, size);
	if (transString == "")
		theUI_.showMatchingTransactionsOnScreen();
	else
		theUI_.showMatchingTransactionsOnScreen(title, size, transString);
}

void ATM::m_trl1_showTransactionsForDate() const
{
	string transString;
	int size;
	Date cd = p_theActiveAccount_->getCreationDate();
	Date date = theUI_.readInDate(cd);
	p_theActiveAccount_->produceTransactionsForDate(date, transString, size);
	if (transString == "")
		theUI_.showMatchingTransactionsOnScreen();
	else
		theUI_.showMatchingTransactionsOnScreen(date, size, transString);
	
}

void ATM::attemptTransfer(BankAccount* transferAccount)
{
	double transferAmount = theUI_.readInTransferAmount();
	bool trOutOK = p_theActiveAccount_->canTransferOut(transferAmount);
	bool trInOk = transferAccount->canTransferIn(transferAmount);

	// if transfer can take place
	if (trOutOK && trInOk)
	{
		recordTransfer(transferAmount, transferAccount);
	}

	theUI_.showTransferOnScreen(trOutOK, trInOk, transferAmount);
}
//------ menu options
//---option 1
void ATM::m_acct1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen(balance);
}
//---option 2
void ATM::m_acct2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_.readInWithdrawalAmount());
	bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
	if (transactionAuthorised)
	{   //transaction is accepted: money can be withdrawn from account
		p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
	}   //else do nothing
	theUI_.showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void ATM::m_acct3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_.readInDepositAmount());
	p_theActiveAccount_->recordDeposit(amountToDeposit);
	theUI_.showDepositOnScreen(true, amountToDeposit);
}
//---option 4
void ATM::m_acct4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 6
void ATM::m_acct6_showMiniStatement() const {
	assert(p_theActiveAccount_ != nullptr);

	int numTransactions;
	string transactionString = "";
	double totalTransactions;

	//check if there are any transactions 
	bool isEmpty = p_theActiveAccount_->isEmptyTransactionList();

	//get user input if transactionlist isn't empty
	if (!isEmpty)
	{
		numTransactions = theUI_.readInNumberOfTransactions();
		p_theActiveAccount_->produceNMostRecentTransactions(numTransactions, transactionString, totalTransactions);
	}

	string mad = p_theActiveAccount_->prepareFormattedMiniAccountDetails();
	theUI_.showMiniStatementOnScreen(isEmpty, totalTransactions, mad + transactionString);
}
//---option 7
void ATM::m_acct7_searchForTransactions() const
{
	bool isEmpty = p_theActiveAccount_->isEmptyTransactionList();
	if (isEmpty)
	{
		theUI_.showNoTransactionsOnScreen();
	}
	else
	{
		searchTransactions();
	}	
}


//---option 8
void ATM::m_acct8_clearTransactionsUpToDate() {
	assert(p_theActiveAccount_ != nullptr);
	int size(0);
	bool deletionConfirmed;
	Date date;
	string transactionString = "";
	// check if the bank account transactions are empty
	bool isEmpty = p_theActiveAccount_->isEmptyTransactionList();
	if (isEmpty)
	{
		theUI_.showNoTransactionsOnScreen();
	}
	else if (!isEmpty)
	{
		// get the creation date of the bank account
		Date cd = p_theActiveAccount_->getCreationDate();
		// pass in the creation date to the valid date function
		date = theUI_.readInValidDate(cd);
		p_theActiveAccount_->produceTransactionsUpToDate(date, size, transactionString);
		// show the confirmation of transactions to delete
		theUI_.showTransactionsUpToDateOnScreen(isEmpty, date, size, transactionString);

		// confirm deletion
		if (!transactionString.empty())
		{
			deletionConfirmed = theUI_.readInConfirmDeletion();
			// delete the transactions if the user wants to
			if (deletionConfirmed)
			{
				p_theActiveAccount_->recordDeletionOfTransactionUpToDate(date);
			}
			// display number of transactions deleted
			theUI_.showDeletionOfTransactionsUpToDateOnScreen(size, date, deletionConfirmed);
		}
	}
}

//---option 9
void ATM::m_acct9_transferCashToAnotherAccount()
{
	// set it to null to avoid dangling pointer.
	BankAccount* transferAccount(nullptr);

	string cardDetails = p_theCard_->toFormattedString();
	theUI_.showCardOnScreen(cardDetails);

	// get the card details and show them on the screen
	string acctNum = theUI_.readInAccountToBeProcessed();
	string accountFileName = theUI_.accountFilename(acctNum);

	int validAccountCode = validateAccount(accountFileName);

	theUI_.showValidateAccountOnScreen(validAccountCode, acctNum);

	// if the account filename is valid (it exists)
	if (validAccountCode == 0)
	{
		// activate the transfer account
		transferAccount = activateAccount(accountFileName);
		attemptTransfer(transferAccount);
		releaseAccount(transferAccount, accountFileName);
	}

}
//------private file functions

bool ATM::canOpenFile(const string& filename) const {
	//check if a file already exist

	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail() return true
	return (!inFile.fail());	//close file automatically when inFile goes out of scope
}

bool ATM::accountsListedOnCard(const string& cashCardFileName) const {
	//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
	assert(!inFile.fail()); //file should exist at this point 
	//check that it contains some info in addition to card number
	string temp;
	inFile >> temp; //read card number
	inFile >> temp;	//ready first account data or eof if end of file found
	return (!inFile.eof());
}

void ATM::activateCard(const string& filename) {
	//dynamically create a cash card to store data from file
	//effectively create the cash card instance with the data
	assert(p_theCard_ == nullptr);
	p_theCard_ = new Card;
	assert(p_theCard_ != nullptr);
	p_theCard_->readInCardFromFile(filename);
}

void ATM::releaseCard() {
	//release the memory allocated to the dynamic instance of a card
	delete p_theCard_;
	p_theCard_ = nullptr;
}
//static member function
char ATM::getAccountTypeCode(const string& filename) {
	//(simply) identify type/class of account from the account number
	//starts with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return filename[13]; //14th char from the filename ("data/account_101.txt")
}

BankAccount* ATM::activateAccount(const string& filename) const {
	//Pre-condition: type of the account is valid
	assert(BankAccount::getAccountType(filename) != "UNKNOWN");
	//effectively create the active bank account instance of the appropriate class
	//and store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch (getAccountTypeCode(filename))
	{
		case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new BankAccount;    //points to a BankAccount object
			break;
	}
	assert(p_BA != nullptr); //check that the dynamic allocation has succeeded
	p_BA->readInBankAccountFromFile(filename); //read account details from file
	//use dynamic memory allocation: the bank account created will have to be released in releaseAccount
	return p_BA;
}

BankAccount* ATM::releaseAccount(BankAccount* p_BA, string filename) const {
	//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}
