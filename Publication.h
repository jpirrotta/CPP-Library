// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include "Lib.h"
#include "Date.h"
#include "Streamable.h"

using namespace std;
namespace sdds
{
    class Publication : public Streamable
    {
    private:
        char *m_title;
        char m_shelfId[SDDS_SHELF_ID_LEN + 1]; // +1 for null terminator
        int m_membership;
        int m_libRef;
        Date m_date;

    public:
        // ---- Constructors ----
        Publication();

        // ---- Copy Constructor ----
        Publication(const Publication &cpy);

        //---- Assignment Operator Overload ----
        Publication &operator=(const Publication &cpy);

        // ---- Destructor ----
        ~Publication();

        // ---- Modifiers ---- //
        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();

        // ---- Queries ---- //
        virtual char type() const;
        bool onLoan() const;
        Date checkoutDate() const;
        bool operator==(const char *title) const;
        operator const char *() const;
        int getRef() const;

        // ---- Pure Virtual Streamable Implementations ---- //
        bool conIO(ios &io) const;
        ostream &write(ostream &os) const;
        istream &read(istream &istr);
        operator bool() const;
    };
}
#endif // SDDS_PUBLICATION_H