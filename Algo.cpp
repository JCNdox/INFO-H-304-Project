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
}

void Algo::creaMatrices()
{
    int p, q;
    p = (*m_query).size();
    q = (*m_target).size();

    /*cout << "p " << p << endl;
    cout << "q " << q << endl;*/

    m_matrice = new int*[p + 1];
    for(int i = 0; i < p + 1; i++)
    {
        m_matrice[i] = new int[q + 1];
    }


    //premiere ligne et premiere colonne a zero
    for(int i = 0; i < p+1; i++)
    {
        m_matrice[i][0] = 0;
    }
    for(int j = 0; j < q+1; j++)
    {
        m_matrice[0][j] = 0;
    }

    m_matriceMemory = new int*[p];
    for(int i = 0; i < p; i++)
    {
        m_matriceMemory[i] = new int[q];
    }

}

int Algo::scoreCalcul()
{
    int solution, solution1, solution2, solution3, wi, wj;
    for(int i = 0; i < (*m_query).size(); i++)
    {
        for(int j = 0; j < (*m_target).size(); j++)
        {
            if(i == 0)
            {
                wi = 0;
            }
            else
            {
                wi = m_matriceMemory[i-1][j] + 1;
            }
            if(j == 0)
            {
                wj = 0;

            }
            else
            {
                wj = m_matriceMemory[i][j-1] + 1;
            }

            solution1 = m_matrice[i][j] + (*m_blosum).score((*m_query)[i], (*m_target)[j]);
            solution2 = m_matrice[i+1][j] - (m_gapOp + m_gapExt * wj);
            solution3 = m_matrice[i][j+1] - (m_gapOp + m_gapExt * wj);

            solution = max(max(solution1, solution2), max(solution3, 0));

            m_matrice[i+1][j+1] = solution;

            m_max = max(m_max, solution);

            if(solution == solution1 || solution == 0)
            {
                m_matriceMemory[i][j] = 0;
            }
            else if(solution == solution2)
            {
                m_matriceMemory[i][j] = wj;
            }
            else if(solution == solution3)
            {
                m_matriceMemory[i][j] = wi;
            }
            else
            {
                m_matriceMemory[i][j] = 0;
            }
        }
    }
    return m_max;
}

