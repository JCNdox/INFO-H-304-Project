#include "Gotoh2.h"

using namespace std;

Gotoh2::Gotoh2(string *query, string *target, Blosum *blosum, int gapExt, int gapOp) : m_query(query), m_target(target), m_blosum(blosum), m_gapExt(gapExt), m_gapOp(gapOp), m_max(0)
{
    creaMatrices();
}
Gotoh2::Gotoh2(Gotoh2 const& gotoh2)
{
}
Gotoh2::~Gotoh2()
{
}

void Gotoh2::creaMatrices()
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

int Gotoh2::scoreCalcul()
{
    int Q = m_gapExt + m_gapOp;
    int R = m_gapExt;
    int solution, solution1, solution2, solution3, solution4, solution5;
    for(int i = 0; i < (*m_query).size() + 1; i++)
    {
        for(int j = 0; j < (*m_target).size() + 1; j++)
        {
            if(j == 0)
            {
                m_E[i][j] = 0;
            }
            else
            {
                solution1 = m_matrice[i][j-1] - Q;
                solution2 = m_E[i][j-1] - R;
                m_E[i][j] = max(solution1, solution2);
            }

            if(i == 0)
            {
                m_F[i][j] = 0;
            }
            else
            {
                solution3 = m_matrice[i-1][j] - Q;
                solution4 = m_F[i-1][j] - R;
                m_F[i][j] = max(solution3, solution4);
            }



            if(i == 0 || j == 0)
            {
                m_matrice[i][j] = 0;
            }
            else
            {
                solution5 = m_matrice[i-1][j-1] + (*m_blosum).score((*m_query)[i-1], (*m_target)[j-1]);
                m_matrice[i][j] = max(max(m_E[i][j], m_F[i][j]), max(solution5, 0));
            }

            m_max = max(m_matrice[i][j], m_max);
            //cout << "max " << m_max << endl;
        }
    }
    return m_max;
}
