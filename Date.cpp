// Final Project Milestone 1
// Date Module
// File  Date.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
namespace sdds
{
	//---- MS3 Testing Variables ----//
	bool sdds_test = false;
	int sdds_year = 2022;
	int sdds_mon = 8;
	int sdds_day = 7;

	bool Date::validate()
	{
		errCode(NO_ERROR);
		if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
		{
			errCode(YEAR_ERROR);
		}
		else if (m_mon < 1 || m_mon > 12)
		{
			errCode(MON_ERROR);
		}
		else if (m_day < 1 || m_day > mdays())
		{
			errCode(DAY_ERROR);
		}
		return !bad();
	}
	int Date::mdays() const
	{
		int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
	}
	int Date::systemYear() const
	{
		int theYear = sdds_year;
		if (!sdds_test)
		{
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			theYear = lt.tm_year + 1900;
		}
		return theYear;
	}
	void Date::setToToday()
	{
		if (sdds_test)
		{
			m_day = sdds_day;
			m_mon = sdds_mon;
			m_year = sdds_year;
		}
		else
		{
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			m_day = lt.tm_mday;
			m_mon = lt.tm_mon + 1;
			m_year = lt.tm_year + 1900;
		}
		errCode(NO_ERROR);
	}
	int Date::daysSince0001_1_1() const
	{ // Rata Die day since 0001/01/01
		int ty = m_year;
		int tm = m_mon;
		if (tm < 3)
		{
			ty--;
			tm += 12;
		}
		return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
	}
	Date::Date() : m_CUR_YEAR(systemYear())
	{
		setToToday();
	}
	Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
	{
		m_year = year;
		m_mon = mon;
		m_day = day;
		validate();
	}
	const char *Date::dateStatus() const
	{
		return DATE_ERROR[errCode()];
	}
	int Date::currentYear() const
	{
		return m_CUR_YEAR;
	}
	void Date::errCode(int readErrorCode)
	{
		m_ErrorCode = readErrorCode;
	}
	int Date::errCode() const
	{
		return m_ErrorCode;
	}
	bool Date::bad() const
	{
		return m_ErrorCode != 0;
	}

	//---- Jesse Pirrotta - added the following functions ----//
	bool Date::checkIstream(std::istream &is)
	{
		if (is.fail())
		{
			// Flush Buffer
			// cin.clear();
			// cin.ignore(12345, '\n');

			// Error Code
			errCode(CIN_FAILED);

			// Return
			return false;
		}
		else
		{
			return true;
		}
	}

	// Deprecated - using new read function to comply with new requirements of file i/o

	// std::istream &Date::read(std::istream &is)
	// {
	// 	int year = 0, month = 0, day = 0;
	// 	bool validIn = false;

	// If checkIstream is false, the errCode will be set to CIN_FAILED

	// 	if (checkIstream(is))
	// 	{
	// 		is >> year;
	// 		getchar(); // Clear any characters in between the dates (i.e yyyy/mmmm/dddd, the slash is removed)
	// 		if (checkIstream(is))
	// 		{
	// 			is >> month;
	// 			getchar(); // Clear any characters in between the dates (i.e yyyy/mmmm/dddd, the slash is removed)
	// 			if (checkIstream(is))
	// 			{
	// 				is >> day;
	// 				validIn = true;
	// 			}
	// 		}
	// 	}

	// 	if (validIn)
	// 	{
	// 		this->m_year = year;
	// 		this->m_mon = month;
	// 		this->m_day = day;
	// 		validate();
	// 		if (this->bad())
	// 		{
	// 			is.setstate(ios::failbit);
	// 		}
	// 	}
	// 	return is;
	// }

	// New Read Function Compatible with File I/O
	istream &Date::read(istream &is)
	{
		Date tempDate;
		char del;

		is >> tempDate.m_year >> del >> tempDate.m_mon >> del >> tempDate.m_day;

		if (!is.fail())
		{
			if (tempDate.validate())
			{
				m_year = tempDate.m_year;
				m_mon = tempDate.m_mon;
				m_day = tempDate.m_day;
			}
			else
			{
				is.setstate(ios::failbit);
			}
		}

		if (is.fail())
		{
			errCode(CIN_FAILED);
		}
		return is;
	}

	std::ostream &Date::write(std::ostream &os) const
	{
		// If there is an error, print the error using dateStatus()
		if (this->bad())
			os << this->dateStatus();

		// If all is good, display the date
		else
			os << m_year << "/" << right << setfill('0') << setw(2) << m_mon << "/" << setw(2) << m_day;

		return os;
	}
	ostream &operator<<(ostream &os, const Date &RO)
	{
		return RO.write(os);
	}
	istream &operator>>(istream &is, Date &RO)
	{
		return RO.read(is);
	}

	bool Date::operator==(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() == rhs.daysSince0001_1_1());
	}
	bool Date::operator<(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() < rhs.daysSince0001_1_1());
	}
	bool Date::operator>(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() > rhs.daysSince0001_1_1());
	}
	bool Date::operator!=(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() != rhs.daysSince0001_1_1());
	}
	bool Date::operator>=(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() >= rhs.daysSince0001_1_1());
	}
	bool Date::operator<=(const Date &rhs) const
	{
		return (this->daysSince0001_1_1() <= rhs.daysSince0001_1_1());
	}

	int Date::operator-(Date rhs) const
	{
		return (this->daysSince0001_1_1() - rhs.daysSince0001_1_1());
	}

	Date::operator bool() const
	{
		return !bad();
	}
}