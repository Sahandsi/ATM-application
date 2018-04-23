//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
: day_(0), month_(0), year_(0)
{}
Date::Date(int d, int m, int y) 	//constructor
: day_(d), month_(m), year_(y)
{}

//____other public member functions
int Date::getDay() const {
	return day_;
}
int Date::getMonth() const {
	return month_;
}
int Date::getYear() const {
	return year_;
}
const Date Date::currentDate() {	//returns the current date
	time_t now(time(0));
	struct tm t;
	localtime_s(&t, &now);
	return Date(t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900);
}

bool Date::isValid(const Date& creationDate) const
{
	
	// (this) is the pointer to the date to be validated

	// validate year where (this) after the creationdate and before the current date (included)
	if (creationDate < (*this) && (*this) <= currentDate())
	{
		// validate month 
		if (this->getMonth() >= 1 && this->getMonth() <= 12)
		{
			// validate days in each month
			switch (this->getMonth())
			{
				case 1: // January
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 2: // Febuary
				{
					if (this->getDay() >= 1 && this->getDay() <= 28)
						return true;
				}
				break;
				case 3:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 4:
				{
					if (this->getDay() >= 1 && this->getDay() <= 30)
						return true;
				}
				break;
				case 5:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 6:
				{
					if (this->getDay() >= 1 && this->getDay() <= 30)
						return true;
				}
				break;
				case 7:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 8:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 9:
				{
					if (this->getDay() >= 1 && this->getDay() <= 30)
						return true;
				}
				break;
				case 10:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
				case 11:
				{
					if (this->getDay() >= 1 && this->getDay() <= 30)
						return true;
				}
				break;
				case 12:
				{
					if (this->getDay() >= 1 && this->getDay() <= 31)
						return true;
				}
				break;
			}
		}
	}

	// otherwise, invalid date
	return false;
}
void Date::setDate(int d, int m, int y) {
	day_ = d;
	month_ = m;
	year_ = y;
}
string Date::toFormattedString() const {
//return date formatted as string ("DD/MM/YYYY")
	ostringstream os;
	os << setfill('0');
	os << setw(2) << day_ << "/";
	os << setw(2) << month_ << "/";
	os << setw(4) << year_;
	return (os.str());
}

ostream& Date::putDataInStream(ostream& os) const {
//put (unformatted) date (D/M/Y) into an output stream
	os << day_ << "/";
	os << month_ << "/";
	os << year_;
	return os;
}
istream& Date::getDataFromStream(istream& is) {
//read in date from (semi-formatted) input stream (D/M/Y)
	char ch;			//(any) colon field delimiter
	is >> day_ >> ch >> month_ >> ch >> year_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==(const Date& d) const { //comparison operator
	return
		((day_ == d.day_) &&
		(month_ == d.month_) &&
		(year_ == d.year_));
}
bool Date::operator!=(const Date& d) const {
	return (!(*this == d));
}
bool Date::operator<(const Date& d) const { //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ((year_ < d.year_)
	     || ((year_ == d.year_) && (month_ < d.month_) )
	     || ((year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_)));
}

bool Date::operator <=(const Date& d) const {
	return
		(!(*this > d));
}

bool Date::operator>(const Date& d) const {
	return ((year_ > d.year_)
		|| ((year_ == d.year_) && (month_ > d.month_))
		|| ((year_ == d.year_) && (month_ == d.month_) && (day_ > d.day_)));
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& aDate) {
    return (aDate.putDataInStream(os));
}
istream& operator>>(istream& is, Date& aDate) {
	return (aDate.getDataFromStream(is));
}
