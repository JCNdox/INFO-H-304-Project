#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

#include <string>
#include <algorithm>
#include "Blosum.h"

class Algo
{
    public:
        Algo(std::string *query, std::string *target, Blosum *blosum, int gapExt, int gapOp);
        Algo(Algo const& algo);
        ~Algo();

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


#endif // ALGO_H_INCLUDED
