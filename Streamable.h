// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <iostream>

namespace sdds
{
    class Streamable
    {
    public:
        virtual std::ostream &write(std::ostream &os) const = 0;
        virtual std::istream &read(std::istream &is) = 0;
        virtual bool conIO(std::ios &io) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable();
    };
    std::ostream &operator<<(std::ostream &os, const Streamable &rhs);
    std::istream &operator>>(std::istream &is, Streamable &rhs);
}

#endif // SDDS_STREAMABLE_H__
