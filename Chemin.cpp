#include "Chemin.h"

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <time.h>
#include <ctime>
#include <cstdlib>



using namespace std;
using std::vector;

Chemin::Chemin(Carte carte)
{
    this->taille=carte.getTaille();
    std::vector<int> temp;
    int j;
    for (int i=0;i<taille;i++)
    {
        temp.push_back(i);
    }
    std::random_shuffle (temp.begin(),temp.end());
    codeGenetique=temp;
    villeDepart=carte.getVilleDepart();
    remiseDansOrdre();
    setFitness(carte);
}

Chemin::Chemin(vector<int> liste,Carte carte)
{
    codeGenetique=liste;
    taille=codeGenetique.size();
    setFitness(carte);
    villeDepart=carte.getVilleDepart();
    remiseDansOrdre();
}

Chemin::~Chemin()
{
    //dtor
}

Chemin Chemin::crossOver(Chemin chemin,Carte carte)
{
    std::vector<int> res1;
    int k = rand()%(taille-2)+1;
    for (int i=0;i<k;i++)
    {
        res1.push_back(codeGenetique.at(i));
    }
    for(int i=0;i<taille;i++)
    {
        if (find(res1.begin(), res1.end(), chemin.codeGenetique.at(i))== res1.end()) res1.push_back(chemin.codeGenetique.at(i));
    }
    Chemin enfant= Chemin(res1,carte);
    enfant.remiseDansOrdre();
    return enfant;
}

void Chemin::setFitness(Carte carte)
{
    int res=0;
    for (int i=0;i<taille-1;i++)
    {
        res=res+carte.getValeur(codeGenetique.at(i),codeGenetique.at(i+1));
    }
    res=res+carte.getValeur(codeGenetique.at(taille-1),codeGenetique.at(0));
    fitness=res;
}

void Chemin::setFitness(int fit)
{
    fitness=fit;
}

int Chemin::getFitness()
{
    return fitness;
}

bool Chemin::egalite(Chemin chemin)
{
    bool test=false;
    int i=1;
    while ((i<taille)&&!(test))
    {
        if (codeGenetique.at(i)==chemin.codeGenetique.at(i))
        {
            test=true;
        }
        i=i+1;
    }
    return test;
}

void Chemin::remiseDansOrdre()
{
    bool test = false;
    std::vector<int> temp;
    std::vector<int> res;
    int i=0;
    while (!(test))
    {
        if (codeGenetique.at(i)==villeDepart) test=true;
        else
        {
                temp.push_back(codeGenetique.at(i));
                i=i+1;
        }
    }
    for (int j=i;j<taille;j++)
    {
           res.push_back(codeGenetique.at(j));
    }
    for (int k=0;k<temp.size();k++)
    {
           res.push_back(temp.at(k));
    }
    codeGenetique=res;
}

int Chemin::getTaille()
{
    return taille;
}

void Chemin::mutation(Carte carte)
{
    int k1 = rand()%taille;
    int k2 = rand()%taille;
    int temp=codeGenetique.at(k1);
    codeGenetique.at(k1)=codeGenetique.at(k2);
    codeGenetique.at(k2)=temp;
    setFitness(carte);
    remiseDansOrdre();
}
