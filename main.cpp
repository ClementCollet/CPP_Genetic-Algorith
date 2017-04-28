/**
 * \file main.cpp
 * \brief Main de notre algorithme g�n�tique
 * \author Cl�ment Collet & Lo�c Steunou
 * \date 08 mai 2016
 *
 * Algorithme g�n�tique pour le probl�me du voyageur de commerce
 */
#include <iostream>
#include<vector>
#include"Carte.h"
#include"Chemin.h"
#include"Generation.h"
#include "fichiermain.h"
#include<fstream>
#include<cstdio>
#include<ctime>



using namespace std;
using std::vector;

int main()
{

    /**< Initialisation des Param�tres : */
    srand(time(0));

    /**< La carte, construction et affichage en fonction du choix de l'utilisateur : */
    int choix=CHOIX_CARTE;
    int nombreVille = TAILLE_CARTE;
    Carte carteTest = Carte(NOM_FICHIER_ENTRE);
    carteTest.afficheCarte();
    cout<<"\n";

    /**< La premi�re g�n�ration, construction et affichage du meilleur g�nome avec a fitness */
    int tailleGen = TAILLE_GENERATION;
    Generation gen0 = Generation(carteTest,tailleGen);
    cout <<"\nMeilleur chemin de la generation 0 : ";
    gen0.getMeilleurChemin()->afficheCodeGenetique();
    cout<<"Fitness de ce genome : " << gen0.getMeilleurChemin()->getFitness()<<endl;

    /**< Initailisation des param�tres choisis par l'utilisateur dans le fichier de donn�es */
    int nbDeBoucles=NOMBRE_DE_GENERATION;
    int nbRepro=(POURCENTAGE_INDIVIDU_PARENTS/100)*tailleGen;
    int nbPopGarde=(POURCENTAGE_INDIVIDU_CONSERVE/100)*tailleGen;
    int nbEnfants=(POURCENTAGE_ENFANTS/100)*tailleGen;
    int nbEnfantsGarde=tailleGen-nbPopGarde ;
    int choixMethode=CHOIX_DE_LA_METHODE_SELECTION_REPRODUCTEURS;
    int mutationRate = MUTATION_RATE;
    int choixNouvelleGeneration=CHOIX_DE_LA_METHODE_GENERATION_SUIVANTE;

    /**< Cr�ation du fichier qui contiendra les r�sultats � analyser (Meilleur fitness par g�n�ration) */
    ofstream file(NOM_FICHIER_SORTIE);
    if (!file.is_open())
    {
        cerr << "Fichier non valide";
        exit(1);
    }


    /**< On effectue une boucle sur le nombre de g�n�ration souhait�  */
    int i=1;
    while (i<nbDeBoucles && gen0.getMeilleurChemin()->getFitness()!=nombreVille)
    {

        int tmp = gen0.getMeilleurChemin()->getFitness();
        /**< Premi�re �tape de chaque boucle, la selection des reproducteurs  */
        switch (choixMethode)
        {
        case 1:
            gen0.selectReproducteurEuge(nbRepro);
            break;
        case 2:
            gen0.selectRoulette(nbRepro,carteTest);
            break;
        case 3:
            gen0.selectRang(nbRepro,carteTest);
            break;
        case 4:
            gen0.selectReproducteurJoute(nbRepro);
            break;
        case 5:
            gen0.selectUniforme(nbRepro);
            break;
        }

        /**< Deuxi�e �tape, la cr�ation des enfants */
        gen0.setEnfants1(nbEnfants,carteTest);

        /**< Troisi�me �tape, la mutation des enfants */
        gen0.mutations(carteTest,mutationRate);


        /**< Derni�re �tape, cr�ation d'une nouvelle g�n�ration */
        switch (choixNouvelleGeneration)
        {
        case 1:
            gen0 = gen0.setGeneSuiv(nbPopGarde,nbEnfantsGarde);
            break;
        case 2:
            gen0 = gen0.setGeneSuiv();
            break;
        }

        /**<Si il y a une am�lioration d'une g�n�ration � l'autre on affiche le meilleur g�nome ainsi que sa fitness */
        if(gen0.getMeilleurChemin()->getFitness()<tmp || i == nbDeBoucles-1)
        {
            //cout<<"\n";
            cout<<"Meilleur chemin de la generation " <<i <<" : ";
            gen0.getMeilleurChemin()->afficheCodeGenetique();
            cout<<"Fitness de ce genome : " << gen0.getMeilleurChemin()->getFitness()<<endl;
        }

        /**<On enregistre meilleure fitness de chaque g�n�ration dans un fichier */
        file << i << " " << gen0.getMeilleurChemin()->getFitness();
        file << "\n";
        i+=1;


    }
    cout<<"\n";
    //gen0.afficherPopulation();

    file.close();
    return 0;
}
