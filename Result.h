#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <string>

class Result
{
    public:
        Result(double score, std::string name);
        Result(Result const& result);
        ~Result();
        double getScore() const;
        std::string getName() const;
    private:
        double m_score;
        std::string m_name;

};


#endif
