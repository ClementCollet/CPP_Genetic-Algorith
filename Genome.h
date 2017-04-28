#ifndef GENOME_H
#define GENOME_H
/*!
 * \file Genome.h
 * \brief Fichier pour la classe Genome
 * \author Clément Collet & Loïc Steunou
 */
#include <vector>
#include <string>

using namespace std;
using std::vector;

/*! \class Genome
 *  \brief Classe Genome
 *
 * La classe des genomes (nom donne aux individus d une generation pour un algorithme genetique)
 */
class Genome
{
    public:
        /*! \brief Getter Fitness
         *
         * Methode qui sera redefinit dans les classes filles
         *
         * \return int : Fitness d'un genome (depend du probleme)
         */
        virtual int getFitness()=0;

        /*! \brief Affiche Code Genetique
         *
         * Permet d afficher le code genetique
         * sur le terminal
         */

        void afficheCodeGenetique();

        /*! \brief Getter Code genetique
         *
         * Permet d obtenir le code genetique d un genome
         *
         * \return vector<int> : code genetique compose d entier
         */
        std::vector<int> getCodeGenetique();


    protected:
       std::vector<int> codeGenetique; /**< Code genetique du genome, ce qui permet de l identifier */
       int fitness; /**< Fitness du genome, sa fonction d evaluation */
       int taille;  /**< Taille du genome = taille de son code genetique */
};

#endif // GENOME_H
