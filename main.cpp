#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include "file.h"
#include "Blosum.h"
#include "Algo.h"

#include "psq.h"
#include "Pin.h"
#include "Phr.h"

#include <vector>
#include "Result.h"

#define RESULTAFFICHE 5

using namespace std;
int main(int argc, char** argv)
{

    int gapExt, gapOp;
    Blosum *blosum;
    string blosumString;
    
    if(argc == 3)
    {
		gapOp = 10;
        gapExt = 1;
        blosumString = "BLOSUM62";
	}
   
    else if(argc == 4)
    {
        blosumString = argv[3];
    }  
    else if(argc == 5)
    {
		gapOp = *argv[3];
        gapExt = *argv[4];
        blosumString = "BLOSUM62";
    }
    else if(argc == 6)
    {
		gapOp = *argv[3];
        gapExt = *argv[4];
        blosumString = argv[5];
	}
    else
    {
		cout << "Erreur" << endl;
		return 1;
	}
	blosum = new Blosum(blosumString.c_str());


    unsigned char buffer[4];

    string pinString =  string(argv[2]) + string(".pin");
    Pin pin(pinString.c_str());
    
    FILE * fquery;
    string queryname = argv[1]; //Nom de la séquence
    
    cout << "--------------- QUERY INFO ---------------" << endl
        << "Query file name : " << queryname.c_str() << endl;
    fquery = fopen(queryname.c_str(),"r");
    if (fquery == NULL){
        cout << "Erreur." << endl;
        cout << "Pour utiliser ce programme il faut minimum 2 parametres" << endl;
        exit(1);
    }
    
    
    if (queryname.substr(queryname.length()-5,5) == "fasta")
    {
        if ((fgetc(fquery) == '>'))
        {
            char querytitle[1000];
            fscanf(fquery,"%[^\n]",querytitle);
            
            
            cout << "Query descritpion : " << querytitle << endl;
        } else
        {
            cout << "Erreur" << endl;
        }
    }
    cout << endl;
    // Transforme la chaine en un string continu (sans \n nor \r)
    int c;
    string query;
    while ((c = getc(fquery)) != EOF){
        if ((c not_eq '\n' && c not_eq '\r')){
            query += c;
        }
    }
    
    

    string psqString = string(argv[2]) + string(".psq");
    ifstream psq(psqString.c_str(), ios::in | ios::binary);
    Psq lecture(&psq);

    string dbsubstr;

    int proviMax = 0; //Garde en memoire le score de la sequence qui vient d etre traitee

    Result result0(0,"");
    Result tempResult(0,"");
    vector<Result> results(RESULTAFFICHE, result0);

    string phrString= string(argv[2]) + string(".phr");
    ifstream phr(phrString.c_str(), ios::in | ios::binary);
    if(!phr.is_open())
    {
        cout << "Impossible d'ouvrir le fichier .phr" << endl;
        return 1;
    }
    Phr decoder(&phr);
    string phrTemp;
    string phrStop = "BL_ORD_ID";

    auto start = std::chrono::high_resolution_clock::now();
    

    while(dbsubstr != "fin")
    {
        dbsubstr = "";
        dbsubstr =lecture.parcours();
        
        if(dbsubstr == "fin")
        {
			break;
		}
        
        Algo *algo;
        algo = new Algo(&query, &dbsubstr, blosum, gapExt, gapOp);
        proviMax = (*algo).scoreCalcul();

        phrTemp = decoder.parcours(1); //recherche du nom de la sequence
            if(phrTemp == phrStop)
            {
                phrTemp = decoder.parcours(1);
            }

        delete algo;
        
        Result result(proviMax, phrTemp);

        for(int k = 0; k < RESULTAFFICHE; k++) //tri
        {
            if((result).getScore() > results[k].getScore())
            {
                tempResult = results[k];
                results[k] = result;
                result = tempResult;
                for(int m = k + 1; m < RESULTAFFICHE; m++)
                {
                    tempResult = results[m];
                    results[m] = result;
                    result = tempResult;
                }
                break;
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Runtime" << duration.count() << " miliseconds" << endl;

    for(int k = 0; k < RESULTAFFICHE; k++)
    {
        cout << k+1 << ") "  << results[k].getName() << "    " << "score : " << results[k].getScore() << endl;
    }



}
