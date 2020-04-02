#include "Algo.h"

using namespace std;

Algo::Algo(string *query, string *target, Blosum *blosum, int gapExt, int gapOp) : m_query(query), m_target(target), m_blosum(blosum), m_gapExt(gapExt), m_gapOp(gapOp), m_max(0)
{
    creaMatrices();
}
Algo::Algo(Algo const& algo)
{
}
Algo::~Algo()
{
    for (int i = 0; i < ((*m_query).size() + 1); i++)
    {
         delete[] m_matrice[i];
         delete[] m_E[i];
         delete[] m_F[i];
    }
    delete[] m_matrice;
    delete[] m_E;
    delete[] m_F;
}

void Algo::creaMatrices()
{
    int p, q;
    p = (*m_query).size();
    q = (*m_target).size();

    m_matrice = new int*[p + 1];
    m_E = new int*[p + 1];
    m_F = new int*[p + 1];
    for(int i = 0; i < p + 1; i++)
    {
        m_matrice[i] = new int[q + 1];
        m_E[i] = new int[q + 1];
        m_F[i] = new int[q + 1];
    }

    for(int i = 0; i < p+1; i++)
    {
        m_matrice[i][0] = 0;
        m_E[i][0] = 0;
        //m_F[i][0] = 0;
    }
    for(int j = 0; j < q+1; j++)
    {
        m_matrice[0][j] = 0;
        //m_E[0][j] = 0;
        m_F[0][j] = 0;
    }
}

int Algo::scoreCalcul()
{
    int Q = m_gapExt + m_gapOp;
    int R = m_gapExt;
    int solution, solution1, solution2, solution3, solution4, solution5;
    for(int i = 0; i < (*m_query).size(); i++)
    {
        for(int j = 0; j < (*m_target).size(); j++)
        {
            solution1 = m_matrice[i+1][j] - Q;
            solution2 = m_E[i+1][j] - R;
            m_E[i+1][j+1] = max(solution1, solution2);
            solution3 = m_matrice[i][j+1] - Q;
            solution4 = m_F[i][j+1] - R;
            m_F[i+1][j+1] = max(solution3, solution4);
            solution5 = m_matrice[i][j] + (*m_blosum).score((*m_query)[i], (*m_target)[j]);
            m_matrice[i+1][j+1] = max(max(m_E[i+1][j+1], m_F[i+1][j+1]), max(solution5, 0));
            m_max = max(m_matrice[i+1][j+1], m_max);
        }
    }
    return m_max;
}
