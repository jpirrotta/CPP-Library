// Jesse Pirrotta
// 169115219
// jpirrotta@myseneca.ca
// Finished July 24th 2022
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"

using namespace std;
namespace sdds
{
    std::ostream &operator<<(std::ostream &os, const Streamable &stream)
    {
        if (stream)
        {
            stream.write(os);
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Streamable &stream)
    {
        stream.read(is);
        return is;
    }
    Streamable::~Streamable()
    {
        ;
    }
}