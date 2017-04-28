#include "Carte.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include<fstream>

using namespace std;

Carte::Carte(int entre)
{
    vector<int> ligne;
    tailleCarte=entre;
    for(int i=0; i<tailleCarte; i++)
    {
        for(int j=0; j<tailleCarte; j++)
        {
            if (i==j) ligne.push_back(-1);
            else if (j==i+1) ligne.push_back(1);
            else if ((j==0)&&(i==tailleCarte-1)) ligne.push_back(1);
            else ligne.push_back(rand()%(20-1)+1);
        }
        matrice.push_back(ligne);
        ligne.clear();
    }
    villeDepart=0;
}

Carte::Carte(string adresse)
{
    vector<int> ligne;
    int tmp;
    ifstream file(adresse);
    if (!file.is_open())
    {
        cerr << "Fichier non valide";
        exit(1);
    }
    file>>tmp;
    tailleCarte=tmp;
    int tmp1;
    for (int i = 0 ; i < tailleCarte ; i++)
    {
        for (int j = 0 ; j < tailleCarte; j++)
        {
            file >> tmp1;
            ligne.push_back(tmp1);
        }
        matrice.push_back(ligne);
        ligne.clear();
    }
    file.close();
    villeDepart = 0;
}

Carte::~Carte()
{
    //dtor
}

void Carte::afficheCarte()
{
    for(int i=0; i<this->getTaille(); i++)
    {
        for(int j=0; j<this->getTaille(); j++)
        {
            if (j==this->getTaille()-1)
            {
                if (getValeur(i,j)<10 && getValeur(i,j)>-1)
                {
                    cout<< " "<<this->getValeur(i,j) << "  " ;
                    cout<< "\n";
                }
                else
                {
                    cout<< this->getValeur(i,j) << "  " ;
                    cout<< "\n";
                }
            }
            else
            {
                if (getValeur(i,j)<10 && getValeur(i,j)>-1)
                {
                    cout<<" "<< this->getValeur(i,j) << "  ";
                }
                else
                {
                    cout<< this->getValeur(i,j) << "  ";
                }
            }
        }
    }
    cout<<endl;
}

int Carte::getValeur(int i,int j)
{
    vector<int> ligne;
    ligne = matrice.at(i);
    return ligne.at(j);
}

int Carte::getTaille()
{
    return tailleCarte;
}

int Carte::getVilleDepart()
{
    return villeDepart;
}

void Carte::setVilleDepart(int i)
{
    villeDepart=i;
}
