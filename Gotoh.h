#ifndef GOTOH_H_INCLUDED
#define GOTOH_H_INCLUDED


#include <string>
#include <algorithm>
#include "Blosum.h"

class Gotoh
{
    public:
        Gotoh(std::string *query, std::string *target, Blosum *blosum, int gapExt, int gapOp);
        Gotoh(Gotoh const& gotoh);
        ~Gotoh();

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
