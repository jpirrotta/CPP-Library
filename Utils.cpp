// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/***********************************************************************
// OOP244 Utils Module:
// File  utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace sdds
{
	unsigned int verifyInt(const int max)
	{
		int userIn;
		bool validate = true;
		do
		{
			validate = true;
			cin >> userIn;
			if (cin.fail())
			{
				// Flush Buffer
				cin.clear();
				cin.ignore(12345, '\n');
				cout << "Invalid Selection, try again: ";
				validate = false;
			}
			else if (userIn < 0 || userIn > max)
			{
				cout << "Invalid Selection, try again: ";
				validate = false;
			}
		} while (validate == false);

		return userIn;
	}
}

//  /
//	/