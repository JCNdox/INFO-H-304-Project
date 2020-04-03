#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include <string>
#include <fstream>

class Psq
{
    public:
        Psq(std::ifstream *psq);
        Psq(Psq const& psq);
        ~Psq();

        std::string parcours();
    private:
        std::ifstream *m_psq;
        bool m_start;

};
#endif
