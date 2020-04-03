
#ifndef PHR_H_INCLUDED
#define PHR_H_INCLUDED

#include <iostream>
#include<fstream>
#include <sstream>

class Phr
{
    public:
        Phr(std::ifstream *phr);
        Phr(Phr const& clone);
        ~Phr();
        std::string parcours(int nbrOctets);
        std::string hexToString(std::string hexa);
        std::string visibleString(); //lis le fichier phr en suivant les instructions BLAST
    private:
        std::ifstream *m_phr;
        std::string m_preStr;

};

#endif
