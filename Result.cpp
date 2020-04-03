#include "Result.h"


using namespace std;

Result::Result(double score, string name) : m_score(score), m_name(name)
{
}
Result::Result(Result const& result)
{
}
Result::~Result()
{
}

double Result::getScore() const
{
    return m_score;
}

string Result::getName() const
{
    return m_name;
}
