#include "Polynom.h"

Polynom::Polynom()
{
    mon = new TList<unsigned int, double>;
}

Polynom::Polynom(TList<unsigned int, double>& l)
{
    mon = new TList<unsigned int, double>;
    l.Reset();
    while (!l.IsFull())
    {
        if (l.Current()->data != 0.)
            *this = *this + *(l.Current());
        l.Next();
    }
}

Polynom::Polynom(const Polynom& p)
{
    mon = new TList<unsigned int, double>(*(p.mon));
}

Polynom::~Polynom()
{
    delete mon;
}


bool Polynom::Check(string &str) //prov
{


    if (str.size() == 0)
        return false;
    if ((str[0] != '-') || (str[0] != '+'))
        str.insert(0, 1, '+');
    for (int i = 1; i < str.size(); i++)
    {

        if (str[i] == '^')
            if (((str[i - 1] != 'x') || (str[i - 1] != 'y') || (str[i - 1] != 'z'))
                && (str[i + 1] < '0' && str[i + 1] > '9'))
                if ((str[i + 2] >= '0') && (str[i + 2] <= '9'))
                    return false;
                else
                    return false;

        if ((str[i] == '.') || (str[i] == ','))
            if ((str[i - 1] < '0' && str[i - 1] > '9') || (str[i + 1] < '0' && str[i + 1] > '9'))
                return false;
    }
}


Polynom::Polynom(string& str)
{
    if (!Check(str))
        throw exception("Invalid polinom");
    mon = new TList<unsigned int, double>;
    for (int i = 0; i < str.size(); i++)
    {

        unsigned int degree = 0;
        double coef;
        if ((str[i + 1] == 'x') || (str[i + 1] == 'y') || (str[i + 1] == 'z'))
            if (str[i] == '-')
                coef = -1;
            else coef = 1;
        else
        {
            string Coef;
            if (str[i] == '-')
                Coef += '-';
            while ((str[i + 1] >= '0') && (str[i + 1] <= '9'))
            {
                Coef += str[i + 1];
                i++;
            }

            coef = strtod(Coef.c_str(), 0);
        }
        if ((str[i + 1] == 'x') || (str[i + 1] == 'y') || (str[i + 1] == 'z'))
            while (i < str.size() && (str[i + 1] != '-' && str[i + 1] != '+'))
                switch (str[i + 1])
                {
                case 'x':
                    i++;
                    if (str[i + 1] == '^')
                    {
                        i++;
                        degree += ((unsigned int)str[i + 1] - 48) * 100;
                        i++;
                    }
                    else degree += 100;
                    break;
                case 'y':
                    i++;
                    if (str[i + 1] == '^')
                    {
                        i++;
                        degree += ((unsigned int)str[i + 1] - 48) * 10;
                        i++;
                    }
                    else degree += 10;
                    break;
                case 'z':
                    i++;
                    if (str[i + 1] == '^')
                    {
                        i++;
                        degree += (unsigned int)str[i + 1] - 48;
                        i++;
                    }
                    else degree += 1;
                    break;
                case '\0':
                    i++;
                    break;
                default:
                    throw exception("Error");
                    break;
                }
        if (coef != 0)
        {
            TMonom monom(degree, coef);
            *this = *this + monom;
        }
    }
}

const Polynom& Polynom::operator=(const Polynom& pol)
{
    if (&pol == this)
        return *this;
    delete mon;
    mon = new TList<unsigned int, double>(*pol.mon);
    return *this;
}

Polynom Polynom::operator+(const Polynom& pol) const
{
    if (mon->IsEmpty())
        return pol;
    if (pol.mon->IsEmpty())
        return *this;
    Polynom res;
    mon->Reset();
    pol.mon->Reset();

    while (!mon->IsFull() && !pol.mon->IsFull())
    {
        if (mon->Current()->key == pol.mon->Current()->key)
        {
            TMonom m = *mon->Current() + *pol.mon->Current();
            if (m.data != 0)
                res.mon->InsertE(m);
            mon->Next();
            pol.mon->Next();
        }
        else if (mon->Current()->key > pol.mon->Current()->key)
        {
            res.mon->InsertE(*mon->Current());
            mon->Next();
        }
        else if (mon->Current()->key < pol.mon->Current()->key)
        {
            res.mon->InsertE(*pol.mon->Current());
            pol.mon->Next();
        }
    }
    if (mon->IsFull())
        while (!pol.mon->IsFull())
        {
            res.mon->InsertE(*pol.mon->Current());
            pol.mon->Next();
        }
    else
        while (!mon->IsFull())
        {
            res.mon->InsertE(*mon->Current());
            mon->Next();
        }
    return res;
}

Polynom Polynom::operator-() const
{
    if (mon->IsEmpty())
        return Polynom();
    Polynom res(*this);
    res.mon->Reset();
    while (!res.mon->IsFull())
    {
        res.mon->Current()->data *= -1;
        res.mon->Next();
    }
    return res;
}

Polynom Polynom::operator-(const Polynom& pol) const
{
    return *this + (-pol);
}

Polynom Polynom::operator-(const TMonom& m) const
{
    return *this + (-m);
}

Polynom Polynom::operator*(const Polynom& pol) const
{
    mon->Reset();
    Polynom result;
    TMonom m1;
    TMonom m2;
    while (!mon->IsFull())
    {
        Polynom tmp;
        m1 = *mon->Current();
        pol.mon->Reset();
        while (!pol.mon->IsFull())
        {
            m2 = m1 * (*pol.mon->Current());
            tmp.mon->InsertE(m2);
            pol.mon->Next();
        }
        result = result + tmp;
        mon->Next();
    }
    return result;
}

Polynom Polynom::operator+(const TMonom& m) const
{
    Polynom res(*this);
    if (res.mon->IsEmpty())
    {
        res.mon->InsertB(m.key, m.data);
        return res;
    }
    res.mon->Reset();
    while (!res.mon->IsFull())
    {
        if (res.mon->Current()->key == m.key)
        {
            *(res.mon->Current()) += m;
            if (res.mon->Current()->data == 0)
                res.mon->Delete(res.mon->Current()->key);
            return res;
        }
        else if (res.mon->Current()->key < m.key)
        {
            res.mon->InsertBefore(res.mon->Current()->key, m.key, m.data);
            return res;
        }
        res.mon->Next();
    }
    res.mon->InsertE(m.key, m.data);
    return res;
}


Polynom Polynom::operator*(const TMonom& m) const
{
    Polynom res(*this);
    res.mon->Reset();
    while (!res.mon->IsFull())
    {
        *res.mon->Current() = *res.mon->Current() * m;
        res.mon->Next();
    }
    return res;
}


ostream& operator<<(ostream& out, const Polynom pol)
{
    pol.mon->Reset();
    if (pol.mon->IsEmpty())
    {
        out << "0";
        return out;
    }
    out << pol.mon->Current();
    pol.mon->Next();
    while (!pol.mon->IsFull())
    {
        if (pol.mon->Current()->data > 0)
            out << '+' << pol.mon->Current();
        pol.mon->Next();
    }
    return out;
}