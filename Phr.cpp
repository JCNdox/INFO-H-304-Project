#include "Phr.h"

using namespace std;

Phr::Phr(ifstream *phr) : m_phr(phr), m_preStr("0")
{
}
Phr::Phr(Phr const& clone)
{
}
Phr::~Phr()
{
}
string Phr::parcours(int nbrOctets)
{
    char *ptr(0);
    ptr = new char[nbrOctets];
    (*m_phr).read(ptr, nbrOctets);
    string str(ptr, nbrOctets);
    if(str == hexToString("1A") && m_preStr == hexToString("80"))
    {
        str = visibleString();
    }
    else
    {
        m_preStr = str;
        str = parcours(1);
    }
    return str;
}
string Phr::hexToString(string hexa)
{
    int y;
    istringstream iss( hexa );
    iss >> hex >> y;

    char *z = new char;
    *z = y;
    string q(z, 1);
    delete z;
    return q;
}
string Phr::visibleString()
{
    char *ptr(0);
    ptr = new char;
    (*m_phr).read(ptr, 1);
    int x = *ptr;
    delete ptr;
    char *ptr2(0);
    string resultat;
    if(x <= 127 && x >= 0)
    {
        ptr2 = new char[x];

        for(int i = 0; i < x; i++)
        {
            (*m_phr).read(ptr2+i, 1);
        }
        string result(ptr2, x);
        delete ptr2;
        resultat = result;
    }
    else
    {
        int y = x + 128;
        ptr2 = new char;
        (*m_phr).read(ptr2, y);
        int z = *ptr2;
        delete ptr2;

        char *ptr3(0);
        int zz = z + 256;
        ptr3 = new char[zz];
        for(int i = 0; i < zz; i++)
        {
            (*m_phr).read(ptr3+i, 1);
        }
        string result(ptr3, zz);
        delete ptr3;
        resultat = result;

    }
    return resultat;
}


