#ifndef _POLYNOM_H_
#define _POLYNOM_H_

#include <stdlib.h>
#include <iostream>
#include "TMonom.h"
#include "TList.h"
#include "Exception.h"

        using namespace std;

    class Polynom
    {
    private:

        TList<unsigned int, double>* mon;
        bool Check(string&);

    public:
        Polynom();
        Polynom(TList<unsigned int, double>&);
        Polynom(const Polynom&);
        Polynom(string&);
        ~Polynom();

        const Polynom& operator=(const Polynom&);
        Polynom operator+(const Polynom&) const;
        Polynom operator+(const TMonom&) const;
        Polynom operator-(const TMonom&) const;
        Polynom operator-(const Polynom&) const;
        Polynom operator*(const Polynom&) const;
        Polynom operator*(const TMonom&) const;
        Polynom operator-() const;

        friend std::ostream& operator<<(std::ostream& out, const Polynom monom);
    };

#endif
