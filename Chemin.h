#ifndef CHEMIN_H
#define CHEMIN_H
/*!
 * \file Chemin.h
 * \brief Fichier pour la classe Chemin
 * \author Clément Collet & Loïc Steunou
 */
#include <Genome.h>
#include <Carte.h>
#include <string>
#include <time.h>
/*! \class Chemin
 *  \brief Classe permettant d'instancier des chemins
 *
 * Les chemin sont individus spécifiques du TSP lors de la résolution de ce dernier par un algorithme génétique
 */
class Chemin : public Genome
{
    public:
        /*! \brief Constructeur 1
         *
         * Constructeur pour des chemins aleatoires a partir d une carte
         *
         * \param carte : pour construire le chemin et fixer sont cout
         */
        Chemin(Carte carte);

        /*! \brief Constructeur 2
         *
         * Constructeur pour des chemins non aleatoire a partir d une carte
         *
         * \param liste d entier
         * \param carte : pour fixer la fitness de ce chemin
         */
        Chemin(std::vector<int> liste,Carte carte);


        /*! \brief Destructeur
         *
         * Destructeur de la classe chemin
         */
        virtual ~Chemin();

        /*! \brief Test d egalite
         *
         * Test si deux chemins sont egaux
         * Ils sont egaux si ils ont le meme code genetique
         *
         * \param chemin
         * \return bool : vrai si les chemins sont egaux
         */
        bool egalite(Chemin chemin);

        /*! \brief Cross Over
         *
         * Permet de "mixer deux chemins"
         * Effectue un cross-over entre 2 chemins
         *
         * \param chemin : celui avec lequel on veut effectuer le cross-over
         * \param carte : la carte est necessaire pour effectuer le crossover
         * \return chemin : l enfant des deux chemins
         */
        Chemin crossOver(Chemin chemin,Carte carte);

        /*! \brief Getter taille
         *
         * Getter sur la taille du chemin
         *
         * \return int : La taille du chemin (= nombre de villes)
         */
        int getTaille();

        /*! \brief Setter Fitness 1
         *
         * Permet de fixer la fitness a partir d une Carte
         * (somme des couts du chemin)
         *
         * \param carte : pour obtenir les couts
         */
        void setFitness(Carte carte);

        /*! \brief Setter Fitness 2
         *
         * Permet de fixer la fitness de son choix
         *
         * \param int : La fitness
         */
        void setFitness(int);

        /*! \brief Getteur Fitness
         *
         * Permet d'obtenir la fitness d'un chemin
         *
         * \return int : Fitness du chemin
         */
        int getFitness();

        /*! \brief Remise dans l'ordre (ville de départ en 1er)
         *
         * Permet de mettre un chemin dans "l'ordre"
         * Avec la ville de départ en premier
         */
        void remiseDansOrdre();

        /*! \brief Mutation
         *
         * Permet d'effectuer une mutation aléatoire
         *
         * \param carte : pour mettre la ville de depart en premier lors de l affichage
         */
        void mutation(Carte carte);

    protected:
    int villeDepart; /**< Ville de départ du voyageur */

    private:
};

#endif // CHEMIN_H
