#include "Genome.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
using std::vector;

void Genome::afficheCodeGenetique()
{
    for(int i=0;i<taille;i++)
    {
        cout << codeGenetique.at(i)<<" ";
    }
    cout << endl;
}
std::vector<int> Genome::getCodeGenetique()
{
    return codeGenetique;
}
