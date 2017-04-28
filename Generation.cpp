#include "Generation.h"
#include "Carte.h"
#include"Chemin.h"
#include"Genome.h"
#include<vector>
#include"iostream"

using namespace std;
using std::vector;

Generation::Generation(int tailleGen)
{
    reproducteurs.clear();
    enfants.clear();
    population.clear();
    taille = tailleGen;
    meilleurChemin = nullptr;
}

Generation::Generation(Carte carte, int tailleGen)
{
    enfants.clear();
    reproducteurs.clear();
    population.clear();
    taille=tailleGen;
    int i=0;
    while (i<taille)
    {
        auto chem = make_shared<Chemin>(carte);
        population.push_back(chem);
        i+=1;
    }
    meilleurChemin=population.at(getIndMeilleurChemin(population));
}

vector<shared_ptr<Chemin>> Generation::getPopulation()
{
    return this->population;
}

vector<shared_ptr<Chemin>> Generation::getEnfants()
{
    return this->enfants;
}

vector<shared_ptr<Chemin>> Generation::getReproducteurs()
{
    return this->reproducteurs;
}

shared_ptr<Chemin> Generation::getMeilleurChemin()
{
    return this->meilleurChemin;
}

int Generation::getTailleGen()
{
    return taille;
}

int Generation::getIndMeilleurChemin(vector<shared_ptr<Chemin>> ensemble)
{
    if (ensemble.size()>0)
    {int ind = 0;
    auto minChemin = ensemble.at(0);
    int mini = ensemble.at(0)->getFitness();
    for (int i=1; i<ensemble.size(); i++)
    {
        auto tempChem = ensemble.at(i);
        if(mini>tempChem->getFitness())
        {
            mini=tempChem->getFitness();
            minChemin=tempChem;
            ind = i;
        }
    }
    return ind;
    }
    else
        return 10000;
}

bool Generation::existeDeja(shared_ptr<Chemin> chem, vector<shared_ptr<Chemin>> ensemble)
{
    int i=0;
    int siz=ensemble.size();
    bool b = false;
    while(i<siz && b==false)
    {
        bool e = true;
        int j=0;
        while (j<chem->getTaille() && e == true)
        {
            auto tempChem = ensemble.at(i);

            if (chem->getCodeGenetique().at(j) != tempChem->getCodeGenetique().at(j)) e=false;
            j+=1;
        }
        if (e == true) b=true;
        i+=1;
    }
    return b;
}

int Generation::indiceChemin(shared_ptr<Chemin> chem, vector<shared_ptr<Chemin>> ensemble)
{
    bool a = false;
    int i = 0;
    while(a==false && i<ensemble.size())
    {
        auto tempChem = ensemble.at(i);
        Chemin chemi = *tempChem;
        if(chem->egalite(chemi)) a = true;
        i+=1;
    }
    return i-1;
}

void Generation::afficherPopulation()
{
    for (int i=0; i<taille; i++)
    {
        population.at(i)->afficheCodeGenetique();
        cout<< population.at(i)->getFitness();
        cout<<"\n";

    }
}
void Generation::afficherReproducteurs()
{
    for (int i=0; i<reproducteurs.size(); i++)
    {
        reproducteurs.at(i)->afficheCodeGenetique();
        cout<< reproducteurs.at(i)->getFitness();
        cout<<"\n";

    }
}
void Generation::afficherEnfants()
{
    for (int i=0; i<enfants.size(); i++)
    {
        enfants.at(i)->afficheCodeGenetique();
        cout<< enfants.at(i)->getFitness();
        cout<<"\n";
    }
}

void Generation::selectReproducteurEuge(int nbRepros)
{
    reproducteurs.clear();
    vector<shared_ptr<Chemin>> temp;
    temp.clear();
    temp = population;
    while(reproducteurs.size()<nbRepros)
    {
        int ind = getIndMeilleurChemin(temp);
        auto tempChem = temp.at(ind);
        temp.erase(temp.begin()+ind);
        reproducteurs.push_back(tempChem);
    }
    temp.clear();
}

void Generation::selectRoulette(int nbRepros, Carte car)
{
    reproducteurs.clear();
    int maxi = 0;
    for(int i=0;i<taille;i++)
    {
        if (population.at(i)->getFitness() > maxi)
        {
            maxi = population.at(i)->getFitness();
        }
    }
    int s=0;
    for (int i=0;i<taille;i++)
    {
        int tmp = population.at(i)->getFitness();
        int f = maxi-tmp+1;
        population.at(i)->setFitness(f);
        s+=f;
    }
    while (reproducteurs.size()<nbRepros)
    {
        int it = 0;
        int i=0;
        int r = rand()%(s)+1;
        while (it<r)
        {
            it+=population.at(i)->getFitness();
            i+=1;
        }
        reproducteurs.push_back(population.at(i-1));
    }
    for(int i=0;i<taille;i++)
    {
        population.at(i)->setFitness(car);
    }
}

void Generation::selectUniforme(int NbRepros)
{
    reproducteurs.clear();
    while(reproducteurs.size()<NbRepros)
    {
        int s = rand()%(taille);
        reproducteurs.push_back(population.at(s));
    }
}

void Generation::selectRang(int nbRepros,Carte car)
{
    reproducteurs.clear();


    vector<shared_ptr<Chemin>> temp;
    temp.clear();
    temp = population;

    vector<shared_ptr<Chemin>> temp1;
    temp1.clear();
    //On change la fitness et on additionne les fitness
    int s=0;
    int i = taille;
    while (temp1.size()<taille)
    {
        int ind = getIndMeilleurChemin(temp);
        auto tmpvect = temp.at(ind);
        temp1.push_back(tmpvect);
        temp1.at(temp1.size()-1)->setFitness(i);
        s+=temp1.at(temp1.size()-1)->getFitness();
        temp.erase(temp.begin()+ind);
        i-=1;
    }
    while (reproducteurs.size()<nbRepros)
    {
        int it = 0;
        int i=0;
        int r = rand()%(s)+1;
        while (it<r)
        {
            it+=temp1.at(i)->getFitness();
            i+=1;
        }
        reproducteurs.push_back(temp1.at(i-1));
    }
    for(int i=0;i<taille;i++)
    {
        population.at(i)->setFitness(car);
    }
}

void Generation::selectReproducteurJoute(int nbRepros)
{
    reproducteurs.clear();
    int k1;
    int k2=0;

    while (reproducteurs.size()<nbRepros)
    {
        k1 = rand()%(taille);
        do
            k2= rand()%(taille);
        while (k1==k2);
        if (population.at(k1)->getFitness()<population.at(k2)->getFitness())
            reproducteurs.push_back(population.at(k1));
        else
            reproducteurs.push_back(population.at(k2));
    }
}

void Generation::setEnfants1(int nb, Carte carte)
{
    enfants.clear();
    int i;
    int j;
    int a = 0;
    int b = this->reproducteurs.size();
    while(enfants.size()<nb)
    {

        i=rand()%(b-a)+a;
        do
        {
            j=rand()%(b-a)+a;
        }
        while(j==i);

        auto chem1 = reproducteurs.at(i);//a modifier
        auto chem2 = reproducteurs.at(j);
        Chemin chemin1 = *chem1;
        Chemin chemin2 = *chem2;

        auto enfant = make_shared<Chemin> (chemin1.crossOver(chemin2,carte));
        enfants.push_back(enfant);
    }
}

void Generation::mutations(Carte carte, int mutationRate)
{
    int r;
    for(int i=0; i<enfants.size(); i++)
    {
        r = rand()%(100);
        if (r<mutationRate) enfants.at(i)->mutation(carte);
    }
}

Generation Generation::setGeneSuiv(int nbParents,int NbEnfants)
{
    Generation gen = Generation(taille);
    while(gen.population.size()<nbParents)
    {
        int ind1 = getIndMeilleurChemin(population);
        gen.population.push_back(population.at(ind1));
        population.erase(population.begin()+ind1);


    }
    while(gen.population.size()<nbParents+NbEnfants)
    {
        int ind2 = getIndMeilleurChemin(enfants);
        gen.population.push_back(enfants.at(ind2));
        enfants.erase(enfants.begin()+ind2);
    }

    gen.meilleurChemin = gen.population.at(getIndMeilleurChemin(gen.population));
    population.clear();
    reproducteurs.clear();
    enfants.clear();
    return gen;
}

Generation Generation::setGeneSuiv()
{
    Generation gen = Generation(taille);
    while(gen.population.size()<taille)
    {
        int ind1 = getIndMeilleurChemin(population);
        int ind2 = getIndMeilleurChemin(enfants);
        if (population.at(ind1)->getFitness()<enfants.at(ind2)->getFitness())
        {
        gen.population.push_back(population.at(ind1));
        population.erase(population.begin()+ind1);
        }
        else
        {
        gen.population.push_back(enfants.at(ind2));
        enfants.erase(enfants.begin()+ind2);
        }
    }
    gen.meilleurChemin = gen.population.at(getIndMeilleurChemin(gen.population));
    population.clear();
    reproducteurs.clear();
    enfants.clear();
    return gen;
}

void Generation::detruireEnfants()
{
    enfants.clear();
}

void Generation::detruirePopulation()
{

    population.clear();
}

void Generation::detruireReproducteurs()
{
    reproducteurs.clear();
}

Generation::~Generation()
{

}

