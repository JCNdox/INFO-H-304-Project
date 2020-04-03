#include <iostream>
#include "psq.h"

using namespace std;

Psq::Psq(ifstream *psq) : m_psq(psq), m_start(false)
{
}
Psq::Psq(Psq const& psq)
{
}
Psq::~Psq()
{
}

string Psq::parcours()
{

    char v[28] = {'-','A','B','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','U','*','Q','J'};
    char *ptr(0);
    ptr = new char[1];
    string chaine;
    string fin = "fin"; //permet d'indiquer qu'on a atteint la fin du fichier

    if(!m_start) //Cette condition permet d'ignorer le premier '-'
    {
        (*m_psq).read(ptr, 1);
        m_start = true;
    }
    while((*m_psq).read(ptr, 1))
    {
        if(v[(int)(*ptr)] == '-')
        {
            return chaine;
        }
        else
        {
            chaine += v[(int)(*ptr)];
        }
    }
    return fin;
}
