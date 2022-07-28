// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS

#include "Publication.h"
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <string.h>
using namespace std;
namespace sdds
{
    // Set all values to their defaults
    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = 0;
        resetDate();
    }

    //---- Rule of Three ----//
    // We have a destructor, therefore we create a copy constructor and an assignment operator overload to ensure
    // that the memory is properly freed when the object is destroyed.

    // Destructor
    Publication::~Publication()
    {
        delete[] m_title;
        m_title = nullptr;
    }
    // Copy Constructor
    Publication::Publication(const Publication &cpy)
    {
        m_title = nullptr;
        *this = cpy;
    }

    // Assignment Operator Overload
    Publication &Publication::operator=(const Publication &cpy)
    {
        if (cpy && this != &cpy)
        {
            if (m_title)
            {
                delete[] m_title;
                m_title = nullptr;
            }

            if (cpy.m_title != nullptr)
            {
                m_title = new char[strlen(cpy.m_title) + 1];
                strcpy(m_title, cpy.m_title);
            }
            strcpy(m_shelfId, cpy.m_shelfId);
            m_membership = cpy.m_membership;
            m_libRef = cpy.m_libRef;
            m_date = cpy.m_date;
        }
        return *this;
    }

    void Publication::set(int member_id)
    {
        // Verify that member_id is a valid, 5 digit (or less) integer
        if (member_id > 99999 || member_id < 0)
        {
            m_membership = 0;
        }
        else
        {
            m_membership = member_id;
        }
    }

    // set the lib ref number
    void Publication::setRef(int value)
    {
        if (value > -1)
        {
            m_libRef = value;
        }
        else
        {
            m_libRef = -1;
        }
    }

    // Sets the date to the current date
    void Publication::resetDate()
    {
        m_date = Date();
    }

    char Publication::type() const
    {
        return 'P';
    }

    bool Publication::onLoan() const
    {
        bool ret;
        if (this->m_membership != 0)
        {
            ret = true;
        }
        else
        {
            ret = false;
        }
        return ret;
    }

    Date Publication::checkoutDate() const
    {
        return m_date;
    }

    bool Publication::operator==(const char *title) const
    {
        bool ret;
        if (strstr(m_title, title) != nullptr)
        {
            ret = true;
        }
        else
        {
            ret = false;
        }
        return ret;
    }

    Publication::operator const char *() const
    {
        return m_title;
    }

    int Publication::getRef() const
    {
        return m_libRef;
    }

    bool Publication::conIO(ios &io) const
    {
        return &io == &cin || &io == &cout;
    }

    ostream &Publication::write(ostream &os) const
    {
        if (this)
        {
            if (conIO(os))
            {
                os << "| " << this->m_shelfId << " | ";
                os << std::setw(SDDS_TITLE_WIDTH) << std::setfill('.') << std::left << this->m_title;
                if (m_membership == 0)
                {
                    os << " |  N/A ";
                }
                else
                {
                    os << " | " << m_membership;
                }
                os << " | " << this->m_date << " |";
            }
            else
            {
                os << std::endl
                   << type() << '\t' << this->m_libRef << '\t' << this->m_shelfId
                   << '\t' << this->m_title << '\t' << this->m_membership << '\t' << this->m_date;
            }
        }
        return os;
    }

    // Read Function
    istream &Publication::read(istream &is)
    {
        Publication temp;
        temp.m_title = new char[255 + 1];
        char tlr[6];

        if (this->m_title)
        {
            delete[] this->m_title;
            m_title = nullptr;
            m_shelfId[0] = '\0';
            m_membership = 0;
            m_libRef = 0;
            resetDate();
        }

        if (conIO(is))
        {
            std::cout << "Shelf No: ";
            is.getline(temp.m_shelfId, SDDS_SHELF_ID_LEN + 1);

            std::cout << "Title: ";
            is.getline(temp.m_title, 255 + 1);

            std::cout << "Date: ";
            is >> temp.m_date;
        }
        else
        {
            is.getline(tlr, 6, '\t');
            temp.m_libRef = atoi(tlr);
            is.getline(temp.m_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            is.getline(temp.m_title, 255, '\t');

            is >> temp.m_membership;
            is >> temp.m_date;
        }
        if (is.good())
        {
            *this = temp;
        }
        return is;
    }
    // bool operator overload
    Publication::operator bool() const
    {
        bool ret;
        if (m_title != nullptr && m_shelfId[0] != '\0')
        {
            ret = true;
        }
        else
        {
            ret = false;
        }
        return ret;
    }
}