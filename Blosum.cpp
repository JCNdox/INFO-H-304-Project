#include "Blosum.h"
#define TAILLE 24

using namespace std;

Blosum::Blosum(string fileName) : m_fileName(fileName)
{
    init(fileName);
}

Blosum::Blosum(Blosum const& original) : m_fileName(original.m_fileName)
{
}

Blosum::~Blosum()
{
}

int Blosum::score(char a, char b) const
{
    int p = preScore(a);
    int q = preScore(b);
    return m_matrice[p][q];
}

void Blosum::init(string fileName)
{
    string line("");

    int position(0);
    int pre_position(0);
    int delta = 0;

    vector<int> temp;

    int p(0);
    int q(0);
    bool neg = false;
    bool start(false);

    ifstream file(fileName.c_str());
    if(file)
    {
        while(getline(file, line) && p < TAILLE)
        {
            position = file.tellg(); //position dans le fichier
            if(line[0] != '#')
            {
                delta = position - pre_position;
                pre_position = file.tellg();
                if(!start)
                {
                    for(int k = 0; k < delta; k++)
                    {
                        if(isdigit(line[k]))
                        {
                            start = true;
                        }
                    }
                }
                if(start)
                {
                    temp = lecture(line);
                    for(int i = 0; i < TAILLE; i++)
                    {
                        m_matrice[p][i] = temp[i];
                    }
                    p++;
                }
            }
            else
            {
                p = 0;
            }
            pre_position = position;
        }
    }
}

int Blosum::preScore(char c) const
{
    int position = 23;
    switch(c)
    {
        case 'A':
            position = 0;
            break;
        case 'R' :
            position = 1;
            break;
        case 'N':
            position = 2;
            break;
        case 'D':
            position = 3;
            break;
        case 'C':
            position = 4;
            break;
        case 'Q':
            position = 5;
            break;
        case 'E':
            position = 6;
            break;
        case 'G':
            position = 7;
            break;
        case 'H':
            position = 8;
            break;
        case 'I':
            position = 9;
            break;
        case 'L' :
            position = 10;
            break;
        case 'K':
            position = 11;
            break;
        case 'M':
            position = 12;
            break;
        case 'F':
            position = 13;
            break;
        case 'P':
            position = 14;
            break;
        case 'S':
            position = 15;
            break;
        case 'T':
            position = 16;
            break;
        case 'W':
            position = 17;
            break;
        case 'Y':
            position = 18;
            break;
        case 'V' :
            position = 19;
            break;
        case 'B':
            position = 20;
            break;
        case 'Z':
            position = 21;
            break;
        case 'X':
            position = 22;
            break;
        case '*':
            position = 23;
            break;
        default:
            //cout << "il y a un probleme    " << (int)c << endl;
            position = 23; //ATTENTION
            break;
    }
    return position;
}
vector<int> Blosum::lecture(string ligne) //, ifstream *file)
{
    vector<int> liste;
    int temp1(111), temp2(0), temp3(0);
    bool neg(false), nombre(false);
    stringstream sstream;
    string result;
    for(string::iterator it = ligne.begin(); it!=ligne.end(); ++it)
    {
        if(isdigit(*it))
        {
            nombre = true;
            if(temp1 != 111)
            {
                temp2 = (int)(*it) - 48;
                sstream<<temp1<<temp2;
                result = sstream.str();
                cout << "result " << result << endl;
                temp3 = stoi(result); //string to int
            }
            else
            {
                temp1 = (int)(*it) - 48;
                temp3 = temp1;
            }
        }
        else if(*it == '-')
        {
            neg = true;
        }
        else if(*it == ' ' && nombre)
        {
            if(neg)
            {
                temp3*= -1;
            }
            neg = false;
            temp1 = 111;
            liste.push_back(temp3);
            nombre = false;
        }
    }
    return liste;
}
