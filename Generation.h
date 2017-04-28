#ifndef GENERATION_H
#define GENERATION_H
/*!
 * \file Generation.h
 * \brief Fichier pour la classe Generation
 * \author Clément Collet & Loïc Steunou
 */
#include"Carte.h"
#include"Genome.h"
#include"Chemin.h"

#include<tr1/memory>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <time.h>
#include <ctime>
#include <cstdlib>
/*! \class Generation
 *  \brief Classe permettant d instancier des Generation de chemin
 *
 *
 */
using namespace std;
using std::vector;

class Generation
{
public:
    /*! \brief Constructeur 1
     *
     * Permet de créer une generation ou les vectors sont vides
     * mais possedant une taille.
     * Constructeur utile pour generer les futures generations
     *
     * \param int : taille de generation souhaitee
     */
    Generation(int tailleGen);

    /*! \brief Constructeur 2
     *
     * Permet de creer un generation ou les vectors enfants et reproducteurs
     * sont vides et ou le vector population est rempli de Chemins aleatoires
     *
     * \param Carte : Pour créer les genomes aleatoires
     */
    Generation(Carte carte, int tailleGen);

    /*! \brief Getter sur Meilleur Chemin
     *
     * Renvoi le meilleur chemin d'une generation (un shared_ptr sur ce chemin)
     * = Le meilleur chemin du vector generation
     *
     * \return shared_ptr<Chemin> : Le meilleur chemin
     */
    shared_ptr<Chemin> getMeilleurChemin();

    /*! \brief Getter sur population
     *
     * \return shared_ptr<Chemin> : Le vector Population
     */
    vector<shared_ptr<Chemin>> getPopulation();

    /*! \brief Getter sur Reproducteurs
     *
     * \return shared_ptr<Chemin> : Le vector Reproducteurs
     */
    vector<shared_ptr<Chemin>> getReproducteurs();

    /*! \brief Getter sur Enfants
     *
     * \return shared_ptr<Chemin> : Le vector Enfants
     */
    vector<shared_ptr<Chemin>> getEnfants();

    /*! \brief Affiche Population
     *
     * Permet d afficher chaque chemin du vector population de generation, ainsi que leur fitness
     */
    void afficherPopulation();

    /*! \brief Affiche Reproducteurs
     *
     * Methode permettant d afficher chaque chemin du vector Reproducteurs de generation, ainsi que leur fitness
     */
    void afficherReproducteurs();

    /*! \brief Affiche Reproducteurs
     *
     * Methode permettant d afficher chaque chemin du vector enfants de generation, ainsi que leur fitness
     */
    void afficherEnfants();

    /*! \brief Selection des Reproducteurs (Eugenisme)
     *
     * Rempli un le vector Reproducteurs en selectionnant des individus
     * de population par la methode de l'eugenisme
     *
     * \param int : Nombre de reproducteurs souhaites
     */
    void selectReproducteurEuge(int nbRepros);

    /*! \brief Selection des Reproducteurs (Joute)
     *
     * Rempli un le vector Reproducteurs en selectionnant des individus
     * de population par la methode joute
     *
     * \param int : Nombre de reproducteurs souhaites
     */
    void selectReproducteurJoute(int nbRepros);

    /*! \brief Selection des Reproducteurs (Roulette)
     *
     * Rempli un le vector Reproducteurs en selectionnant des individus
     * de population par la methode de la roulette
     *
     * \param int : Nombre de reproducteurs souhaites
     */
    void selectRoulette(int nbRepros, Carte carte);

    /*! \brief Selection des Reproducteurs (Rang)
     *
     * Rempli un le vector Reproducteurs en selectionnant des individus
     * de population par la methode du rang
     *
     * \param int : Nombre de reproducteurs souhaites
     */
    void selectRang(int nbRepros,Carte);

    /*! \brief Selection des Reproducteurs (Uniforme)
     *
     * Rempli un le vector Reproducteurs en selectionnant des individus
     * de population par la methode uniforme
     *
     * \param int : Nombre de reproducteurs souhaites
     */
    void selectUniforme(int nbRepros);

    /*! \brief Setter Enfants
     *
     * Permet de generer les enfants a partir des reproducteurs
     *
     * \param int : nombre d enfants souhaite
     * \param carte : pour effectuer les cross over avec les reproducteurs
     */
    void setEnfants1(int nb, Carte carte);

    /*! \brief Generateur de generation suivante
     *
     * Permet de creer la generation suivante a la generation en cours
     *
     * \param int : Nombre d individus de la population précédente conservés
     * \param int : Nombre d enfants
     * \return Generation : la generation suivante
     */
    Generation setGeneSuiv(int nbPop,int nbEnfants);

    /*! \brief Generateur de generation suivante
     *
     * Permet de creer la generation suivante a la generation en cours, les meilleurs seront choisis indépendament de leur caractères enfants ou issus de la génération précedente
     *
     * \return Generation : la generation suivante
     */

    Generation setGeneSuiv();

    /*! \brief Destructeur de Population
     *
     * Clear le vector population
     */
    void detruirePopulation();

    /*! \brief Destructeur de Reproducteurs
     *
     * Clear le vector Reproducteurs
     */
    void detruireReproducteurs();

    /*! \brief Destructeur enfants
     *
     * Clear le vector enfants
     */
    void detruireEnfants();

    /*! \brief Methode mutations
     *
     * Methode permettant d effectuer les mutations sur le vector enfants
     *
     * \param Carte : pour effectuer chaque mutation
     * \param int : Le taux de mutation
     */
    void mutations(Carte carte,int mutationRate);

    /*! \brief Methode indice du meilleur chemin
     *
     * Permet d obtenir l indice du meilleur chemin d un des vector d une generation
     *
     * \param vector<shared_ptr<Chemin>>
     * \return int : indice du meilleur chemin
     */
    int getIndMeilleurChemin(std::vector<shared_ptr<Chemin>> ensemble);

    /*! \brief Methode Existe Deja
     *
     * Permet de savoir si un chemin appartient a un ensemble
     *
     * \param shared_ptr<Chemin> : Le chemin que l on veut tester
     * \param vector<shared_ptr<Chemin>> : l ensemble que l on veut tester
     *
     * \return bool : vrai si le chemin appartient a l'ensemble
     */
    bool existeDeja(shared_ptr<Chemin> chem, vector<shared_ptr<Chemin>> ensemble);

    /*! \brief Methode indice Chemin
     *
     * Retourne l indice du chemin dans l ensemble
     *
     * \param shared_ptr<Chemin> : Le chemin que l on veut tester
     * \param vector<shared_ptr<Chemin>> : l ensemble que l on veut tester
     *
     * \return int : l indice du chemin dans l ensemble
     */
    int indiceChemin(shared_ptr<Chemin> chem, vector<shared_ptr<Chemin>> ensemble);

    /*! \brief Getter sur la taille de la generation
     *
     * \return int : taille generation
     */
    int getTailleGen();

    /*! \brief Destructeur
     *
     * Destructeur de la classe chemin
     */
    virtual ~Generation();

protected:
    vector<shared_ptr<Chemin>> population; /**< Le vector population : contient des pointeurs sur les individus (Chemins) de la population */
    vector<shared_ptr<Chemin>> reproducteurs; /**< Le vector reproducteur : contient des pointeurs sur les reproducteurs de la generation */
    vector<shared_ptr<Chemin>> enfants; /**< Le vector enfants : contient des pointeurs les enfants des reproducteurs */
    shared_ptr<Chemin> meilleurChemin; /**<  pointeur sur le meilleur chemin */
    int taille; /**< Taille de la generation (et donc du vector population) */
};

#endif // GENERATION_H
