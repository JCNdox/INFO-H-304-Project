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

using namespace std;
int main(int argc, char** argv)
{

    int gapExt(1), gapOp(10);

    unsigned char buffer[4];
    //char sob = sizeof(buffer);

    string pinString =  string(argv[2]) + string(".pin"); //string("uniprot_sprot.fasta")+string(".pin");
    Pin pin(pinString.c_str());//string("uniprot_sprot.fasta")+string(".pin"));
    //pin.dataData();
    FILE * fquery;
     // Extracting query sequence
    string queryname = argv[1]; //"P00533.fasta";//"Q9Y6V0.fasta";////"testproty.fasta"; //"P07327.fasta";
    //string queryname = "P00533.fasta";
    cout << "--------------- QUERY INFO ---------------" << endl
        << "Query file name : " << queryname.c_str() << endl;
    fquery = fopen(queryname.c_str(),"r");
    if (fquery == NULL){
        cout << "Opening of 'query' file impossible." << endl;
        exit(1);
    }
    string stopString; //à virer
    if (queryname.substr(queryname.length()-5,5) == "fasta")
    {
        if ((fgetc(fquery) == '>'))
        {
            char querytitle[1000];
            fscanf(fquery,"%[^\n]",querytitle);
            stopString = querytitle; //WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
            cout << "Query descritpion : " << querytitle << endl;
        } else
        {
            cout << "Fake or corrupted FASTA file ..." << endl;
        }
    }
    cout << endl;

    // Transforming it into pure continued string (without \n nor \r)
    int c;
    string query;
    while ((c = getc(fquery)) != EOF){
        if ((c not_eq '\n' && c not_eq '\r')){
            query += c;
        }
    }
    ///////////////////////////////////////////////////
    Blosum *blosum;
    string blosumString;
    if(argc == 4) //rendre ça plus flexible
    {
        blosumString = argv[3];
    }
    else
    {
        blosumString = "BLOSUM62";
    }
    blosum = new Blosum(blosumString.c_str());

    string psqString = string(argv[2]) + string(".psq");//"wesh.psq"; //"uniprot_sprot.fasta.psq";
    ifstream psq(psqString.c_str(), ios::in | ios::binary);
    Psq lecture(&psq);
    //Psq psq(psqString.c_str()); //"uniprot_sprot.fasta.psq"


    string dbsubstr;

    int proviMax = 0;
    vector<int> ranking(5,0);
    vector<int> tracking(5,0);

    Result result0(0,"");
    Result tempResult(0,"");
    vector<Result> results(5, result0); //POUVOIR MODIFIER CE 5

    string phrString= string(argv[2]) + string(".phr"); //"uniprot_sprot.fasta.phr";//
    ifstream phr(phrString.c_str(), ios::in | ios::binary);
    if(!phr.is_open())
    {
        cout << "Impossible d'ouvrir le fichier .phr" << endl;
        //Fermer le programme
    }
    Phr decoder(&phr);
    string phrTemp;
    string phrStop = "BL_ORD_ID";

    auto start = std::chrono::high_resolution_clock::now();
    int nbr = 0;



    int abcd = 0;

    string stooop;
    //string fin = "";
    while(dbsubstr != "fin")// && stopString != stooop && abcd < 10000)
    {
        dbsubstr = "";
        dbsubstr =lecture.parcours();
        Algo *algo;
        algo = new Algo(&query, &dbsubstr, blosum, gapExt, gapOp);
        nbr++;

        proviMax = (*algo).scoreCalcul();
        //cout << proviMax << endl;
        phrTemp = decoder.parcours(1);
            if(phrTemp == phrStop)
            {
                phrTemp = decoder.parcours(1);
            }

        delete algo;

        stooop = phrTemp;
        Result result(proviMax, phrTemp);

        dbsubstr = "";

        for(int k = 0; k < 5; k++)
        {
            if((result).getScore() > results[k].getScore())
            {
                tempResult = results[k];
                results[k] = result;
                result = tempResult;
                for(int m = k + 1; m < 5; m++)
                {
                    tempResult = results[m];
                    results[m] = result;
                    result = tempResult;
                }
                break;
            }
        }
        abcd++;
    }
    cout << "abcd " << abcd << endl;


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Sequence found in database in " << duration.count() << " miliseconds" << endl;

    for(int k = 0; k < 5; k++)
    {
        cout << k+1 << ") "  << results[k].getName() << "    " << "score : " << results[k].getScore() << endl;
    }



}
