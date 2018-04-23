//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING


#include "UserInterface.h" 

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

void UserInterface::wait() const
{
	cout << "\n";
	outputLine("Press RETURN to go back to menu...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
void UserInterface::endProgram() const
{
	cout << "\n";
	outputLine("Press RETURN to end program...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
void UserInterface::showTransactionsUpToDateOnScreen(bool isEmpty, const Date& date, int size, const string& transactionString) const
{
	if (isEmpty == false && transactionString != "")
	{
		outputLine(transactionString);
	}
	else
	{
		ostringstream os;
		os << "NO TRANSACTION IN BANK ACCOUNT UP TO DATE " << setfill('0');
		os << setw(2) << date.getDay() << "/";
		os << setw(2) << date.getMonth() << "/";
		os << setw(4) << date.getYear();
		outputLine(os.str());
	}
}

void UserInterface::showFundsAvailableOnScreen(bool isAccountEmpty, const string& statement, double totalMaxBorrowable) const
{
	if (isAccountEmpty)
	{
		outputLine("NO ACCOUNT ACCESSIBLE WITH THIS CARD");
	}
	else
	{
		ostringstream os;
		os << statement;
		os << "\n" << setfill(' ');
		os << "\n      TOTOAL AVAILABLE FUNDS: \234" << totalMaxBorrowable;
		outputLine(os.str());
	}

}

void UserInterface::showMatchingTransactionsOnScreen(double amount, int size, const string & transString) const
{
	ostringstream os;
	os << transString;
	os << "\n\n\tTHERE ARE " << size << " TRANSACTIONS MATCHING THAT SEARCH CRITERION: " << amount;
	outputLine(os.str());
}

void UserInterface::showMatchingTransactionsOnScreen(const string& title, int size, const string& transString) const
{
	ostringstream os;
	os << transString;
	os << "\n\n\tTHERE ARE " << size << " TRANSACTIONS MATCHING THAT SEARCH CRITERION: " << title;
	outputLine(os.str());
}

void UserInterface::showMatchingTransactionsOnScreen(const Date& date, int size, const string & transString) const
{
	ostringstream os;
	os << transString;
	os << "\n\n\tTHERE ARE " << size << " TRANSACTIONS MATCHING THAT SEARCH CRITERION: ";
	os << setfill('0');
	os << setw(2) << date.getDay() << "/";
	os << setw(2) << date.getMonth() << "/";
	os << setw(4) << date.getYear();
	outputLine(os.str());
}

void UserInterface::showTransferOnScreen(bool trOutOk, bool trInOk, double transferAmount) const
{
	ostringstream os;
	// transaction can take place
	if (trOutOk && trInOk)
	{
		
		os << "THE TRANSFER HAS BEEN SUCCESSFUL: ";
		os << "\x9C" << transferAmount;
		outputLine(os.str());
	}

	// active account cannot transfer money to other account
	if (!trOutOk)
	{
		
		os << "INSUFFICENT FUNDS TO TRANSFER ";
		os << "\x9c" << transferAmount;
		outputLine(os.str());
	}

	// transfer amount cannot recieve money
	if (!trInOk)
	{
		
		os << "TRANSFER ACCOUNT CANNOT RECIEVE ";
		os << "\x9c" << transferAmount;
		outputLine(os.str());
	}
}

int UserInterface::showMainMenuAndGetCommand() const
{
	system("cls");
	cout << "\n\n";
	outputHeader("WELCOME TO THE ATM");
	outputLine(" 0                            Leave ATM ");
	outputLine(" 1                      Enter your card ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

int UserInterface::showAccountMenuAndGetCommand(const string& accNum) const
{
	outputHeader("ACCOUNT " + accNum + " MENU");
	outputLine(" 0                    Back to card menu ");
	outputLine(" 1                      Display balance ");
	outputLine(" 2                Withdraw from account ");
	outputLine(" 3                 Deposit into account ");
	outputLine(" 4                       Show statement ");
	outputLine(" 5                    Show all deposits  // TO BE IMPLEMENTED FOR Task 1c Preparation");
	outputLine(" 6                  Show mini statement  // TO BE IMPLEMENTED FOR Task 1c");
	outputLine(" 7                  Search Transactions  // TO BE IMPLEMENTED FOR Task 1c");
	outputLine(" 8    Clear all transactions up to date  // TO BE IMPLEMENTED FOR Task 1c");
	outputLine(" 9          Transfer to another account  // TO BE IMPLEMENTED FOR Task 1c");
	outputLine("----------------------------------------");
	return (readInCommand());
}

void UserInterface::showSearchMenu() const
{
	outputHeader("Search Menu");
	outputLine(" 0           Search By Amount ");
	outputLine(" 1           Search By Title ");
	outputLine(" 2           Search By Date");
	outputLine(" 3           Exit search menu");
	outputLine("----------------------------------------");
}

const string UserInterface::readInCardToBeProcessed() const {
	return askForInput("ENTER YOUR CARD NUMBER");
}

void UserInterface::showValidateCardOnScreen(int validCode, const string& cardNumber) const
{
	switch (validCode)
	{
	case VALID_CARD: {
		// Card exists and is accessible (and is not already open: TO BE IMPLEMENTED)
	} break;
	case UNKNOWN_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT EXIST");
	} break;
	case EMPTY_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT LINK TO ANY ACCOUNTS");
	} break;
	}
}

void UserInterface::showCardOnScreen(const string& cardDetails) const
{
	outputLine(cardDetails);
}

int UserInterface::showCardMenuAndGetCommand(const string& cardNumber) const
{
	outputHeader("CARD " + cardNumber + " MENU");
	outputLine(" 0           Stop banking & remove card ");
	outputLine(" 1            Manage individual account ");
	outputLine(" 2           Show total funds available  // TO BE IMPLEMENTED FOR Task 1c");
	outputLine("----------------------------------------");
	return (readInCommand());
}

void UserInterface::showCardAccounts(const string& cardNumber, const string& cardDetails) const
{
	outputHeader("CARD " + cardNumber + " ACCOUNTS");
	cout << cardDetails;
	outputLine("----------------------------------------\n");
}

const string UserInterface::readInAccountToBeProcessed() const {
	return askForInput("SELECT ACCOUNT TO MANAGE");
}

bool UserInterface::readInConfirmDeletion() const
{
	string input = askForInput("CONFIRM DELETION (N/Y)?");
	while (input != "n" && input != "N" && input != "y" && input != "Y")
	{
		outputLine("WRONG INPUT");
		input = askForInput("CONFIRM DELETION (N/Y)?");
	}

	// if the user wants to delete the transactions
	if (input == "y" || input == "Y")
	{
		return true;
	}
	// otherwise return false
	return false;
}

void UserInterface::showDeletionOfTransactionsUpToDateOnScreen(int size, const Date& date, bool deletionConfirmed) const
{
	// output list of transaction deleted if they have been deleted and up to which date
	if (deletionConfirmed)
	{
		ostringstream os;
		os << "THE " << size << " TRANSACTIONS IN BANK ACCOUNT UP TO DATE " << setfill('0');
		os << setw(2) << date.getDay() << "/";
		os << setw(2) << date.getMonth() << "/";
		os << setw(4) << date.getYear() << " HAVE BEEN DELETED";
		outputLine(os.str());
	}
}

void UserInterface::showNoTransactionsOnScreen() const
{
	outputLine("NO TRANSACTIONS IN BANK ACCOUNT");
}

void UserInterface::showMatchingTransactionsOnScreen() const
{
	outputLine("NO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN");
}

void UserInterface::showValidateAccountOnScreen(int validCode, const string& accNum) const
{
	switch (validCode)
	{
	case VALID_ACCOUNT:
	{
		outputLine("THE ACCOUNT " + accNum + " IS NOW OPEN!");
		// Account exists and is accessible with that card (and not already open: TO BE IMPLEMENTED)
	} break;
	case INVALID_ACCOUNT_TYPE:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT A RECOGNISED TYPE OF ACCOUNT!");
	} break;
	case UNKNOWN_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " DOES NOT EXIST!");
	} break;
	case UNACCESSIBLE_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT ACCESSIBLE WITH THIS CARD!");
	} break;
	case SAME_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS ALREADY OPEN");
	} break;
	}
}

//static 
const string UserInterface::cardFilename(const string& cn) {
	//read in card name & produce cashcard filename
	return FILEPATH + "card_" + cn + ".txt";	//read in card name & produce cashcard filename
}
//static
const string UserInterface::accountFilename(const string& an) {
	return FILEPATH + "account_" + an + ".txt";
}

//input functions
//option 6 
int UserInterface::readInNumberOfTransactions() const
{
	outputLine("NUMBER OF TRANSACTIONS TO VIEW: ");
	return (readInPositiveNumber());
}
double UserInterface::readInWithdrawalAmount() const {
	//ask for the amount to withdraw
	outputLine("AMOUNT TO WITHDRAW: \234");
	return (readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
	//ask for the amount to deposit
	outputLine("AMOUNT TO DEPOSIT: \234");
	return (readInPositiveAmount());
}

Date UserInterface::readInValidDate(const Date& cd) const 
{
	
	outputLine("ENTER A VALID DATE");
	int day, month, year;
	outputLine("DAY: ");
	cin >> day;
	outputLine("MONTH: ");
	cin >> month;
	outputLine("YEAR: ");
	cin >> year;

	Date aDate(day, month, year);
	
	//// if the date is not valid
	while (!aDate.isValid(cd))
	{
		outputLine("INVALID DATE");
		outputLine("DAY: ");
		cin >> day;
		outputLine("MONTH: ");
		cin >> month;
		outputLine("YEAR: ");
		cin >> year;
		aDate.setDate(day, month, year);
	}
	return aDate;
}

int UserInterface::readInSearchCommand() const
{
	return readInCommand();
}

const double UserInterface::readInTransferAmount() const
{
	outputLine("PLEASE ENTER THE TRANSFER AMOUNT");
	return readInPositiveAmount();
}

string UserInterface::readInTitle() const
{
	string title;
	title = askForInput("ENTER TITLE TO SEARCH ON TRANSACTIONS");
	cin.clear();
	while (title.empty())
	{
		title = askForInput("ENTER TITLE TO SEARCH ON TRANSACTIONS");
		cin.clear();
	}
	return title;
}

double UserInterface::readInAmount() const
{
	double amount;
	outputLine("ENTER AMOUNT TO SEARCH ON TRANSACTIONS: ");
	cin >> amount;
	return amount;
}

Date UserInterface::readInDate(const Date& creationDate) const
{
	return readInValidDate(creationDate);
}

//output functions

void UserInterface::showProduceBalanceOnScreen(double balance) const
{
	cout << "\n      THE CURRENT BALANCE IS: " << fixed << setprecision(2) << setfill(' ') << "\234" << setw(12) << balance;
}

void UserInterface::showWithdrawalOnScreen(bool trAuthorised, double withdrawnAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << withdrawnAmount << " WITHDRAWN FROM ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // not enough money
	}
}

void UserInterface::showDepositOnScreen(bool trAuthorised, double depositAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << depositAmount << " DEPOSITED INTO ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // too much to deposit
	}
}
void UserInterface::showStatementOnScreen(const string& statement) const {
	outputHeader("PREPARING STATEMENT...");
	cout << statement;
	outputLine("----------------------------------------\n");
}

//---------------------------------------------------------------------------
// private support member functions
//---------------------------------------------------------------------------

void UserInterface::showByeScreen() const
{
	outputLine("");
	outputHeader("THANK YOU FOR USING THE ATM");
	endProgram();
}

int UserInterface::readInCommand() const
{
	cout << "\n";
	outputLine("ENTER YOUR COMMAND: ");
	int com;
	cin >> com;
	return com;
}

void UserInterface::showErrorInvalidCommand() const
{
	outputLine("INVALID COMMAND CHOICE, TRY AGAIN");
}
void UserInterface::showMiniStatementOnScreen(bool isEmpty, double total, string str) const
{
	outputHeader("PREPARING MINI STATEMENT...");
	ostringstream os;
	
	if (!isEmpty)
	{
		os << "RECENT TRANSACTIONS REQUESTED AT ";
		os << Time::currentTime().toFormattedString();
		os << " ON ";
		os << Date::currentDate().toFormattedString();
		os << str;
		os << "\n      TOTAL: \234 " << fixed << setprecision(2) << total;
		outputLine(os.str());
	}
	else
	{
		showNoTransactionsOnScreen();
	}
}
double UserInterface::readInPositiveAmount() const
{
	double amount;
	cin >> amount;

	while (amount <= 0.0)
	{
		outputLine("AMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ");
		cin >> amount;
	}

	return amount;
}
//option 6 
int UserInterface::readInPositiveNumber() const
{
	int number;
	cin >> number;

	while (number <= 0)
	{
		outputLine("NUMBER SHOULD BE POSITIVE, TRY AGAIN: ");
		cin >> number; 
	}

	return number;
}
void UserInterface::outputHeader(const string& header) const
{
	// calculate lengths so we can centre the header
	const int length = header.size();
	const int borderWidth = 40;
	const int leftSpacePad = 6;
	const int paddingRequired = ((borderWidth - length) / 2) + leftSpacePad;

	outputLine("========================================");
	cout << "\n" << setfill(' ') << setw(paddingRequired) << ' ' << header;
	outputLine("========================================");
}

string UserInterface::askForInput(const string& promptForUser) const
{
	outputLine(promptForUser + ": ");
	string userInput;
	cin >> userInput;
	return userInput;
}

void UserInterface::outputLine(const string& text) const
{
	cout << "\n      " << text;
}
