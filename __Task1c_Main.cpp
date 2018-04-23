//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 18
//Team: Asghar Mahmood b6005405, Claire Smith b6008661, Sam Simaei b5038121, Deepak Jindal b6019531 ALL SOFTWARE ENGINEERING

#include "ATM.h"         //include modules header files

//---------------------------------------------------------------------------

//main application

int main() { 
	//create the application
	ATM theATM; // default constructor called here
    //run it
	theATM.activateCashPoint();
	//destroy it - destructor called here
	return 0;
}
