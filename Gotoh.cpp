#include "Gotoh.h"

using namespace std;

Gotoh::Gotoh(string *query, string *target, Blosum *blosum, int gapExt, int gapOp) : m_query(query), m_target(target), m_blosum(blosum), m_gapExt(gapExt), m_gapOp(gapOp), m_max(0)
{
    creaMatrices();
}
Gotoh::Gotoh(Gotoh const& gotoh)
{
}
Gotoh::~Gotoh()
{
}

void Gotoh::creaMatrices()
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

int Gotoh::scoreCalcul()
{
    int Q = m_gapExt + m_gapOp;
    int R = m_gapExt;
    int solution, solution1, solution2, solution3, solution4, solution5;
    for(int i = 0; i < (*m_query).size(); i++)
    {
        for(int j = 0; j < (*m_target).size(); j++)
        {
            solution1 = m_matrice[i+1][j] - Q;
            //cout << "solution1 " << solution1 << endl;
            solution2 = m_E[i+1][j] - R;
            //cout << "solution2 " << solution2 << endl;


            m_E[i+1][j+1] = max(solution1, solution2);

            solution3 = m_matrice[i][j+1] - Q;
            //cout << "solution3 " << solution3 << endl;
            solution4 = m_F[i][j+1] - R;
            //cout << "solution4 " << solution4 << endl;

            m_F[i+1][j+1] = max(solution3, solution4);

            solution5 = m_matrice[i][j] + (*m_blosum).score((*m_query)[i], (*m_target)[j]);
            //cout << "solution5 " << solution5 << endl;

            m_matrice[i+1][j+1] = max(max(m_E[i+1][j+1], m_F[i+1][j+1]), max(solution5, 0));
            //cout << "m_matrice[i+1][j+1] " << m_matrice[i+1][j+1] << endl;

            m_max = max(m_matrice[i+1][j+1], m_max);
            //cout << "max " << m_max << endl;
        }
    }
    return m_max;
}
