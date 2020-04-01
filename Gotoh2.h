#ifndef GOTOH2_H_INCLUDED
#define GOTOH2_H_INCLUDED


#include <string>
#include <algorithm>
#include "Blosum.h"

class Gotoh2
{
    public:
        Gotoh2(std::string *query, std::string *target, Blosum *blosum, int gapExt, int gapOp);
        Gotoh2(Gotoh2 const& gotoh);
        ~Gotoh2();

        int scoreCalcul();
        void creaMatrices();

    private:
        Blosum *m_blosum;
        std::string *m_query;
        std::string *m_target;
        int **m_matrice, **m_E, **m_F;
        int m_gapExt, m_gapOp;
        int m_max;

};


#endif

