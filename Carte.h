#ifndef CARTE_H
#define CARTE_H
/*!
 * \file Carte.h
 * \brief Fichier pour la classe Carte
 * \author Clement Collet & Loic Steunou
 */
#include <string>
#include<vector>

using namespace std;
using std::vector;

/*! \class Carte
 *  \brief Classe permettant d instancier des matrices/cartes
 *
 * Les matrices et les cartes sont les donnees du TSP
 */
class Carte
{
    public:
        /*! \brief  Constructeur 1
         *
         * Constructeur 1 de la classe carte,
         * Celui qui permet de creer des matrices aleatoires
         *
         * \param int : Nombre de villes
         */
        Carte(int entre);

        /*! \brief  Constructeur 2
         *
         * Constructeur 2 de la classe carte,
         * Celui qui permet de charger des matrices a partir d un fichier .txt
         *
         * \param string : l adresse du fichier
         */
        Carte(string adresse);

        /*! \brief  Destructeur
         *
         * Destructeur de la classe carte
         */
        virtual ~Carte();

        /*! \brief  Getter taille
         *
         * Getteur sur la taille de la matrice
         *
         * \return int : taille de la matrice
         */
        int getTaille();

        /*! \brief  Getter valeur
         *
         * Getteur sur les valeurs de la matrice
         * Les valeurs sont les coût de passage d une ville a l autre
         *
         * \param int : indice de la ligne
         * \param int : indice de la colonne
         * \return int : la valeur se trouvant en (i,j) dans la matrice
         */
        int getValeur(int i,int j);

        /*! \brief Getter ville de depart
         *
         * Getteur sur la ville de depart du voyageur.
         * On a definit une ville de depart pour rendre
         * l affichage et le travail plus simple
         *
         * \return int : la ville de depart
         */
        int getVilleDepart();

        /*! \brief  Setter ville de depart
         *
         * Setter sur la ville de depart
         *
         * \param int : indice de la ville de depart
         */
        void setVilleDepart(int i);

        /*! \brief  Affichage de la carte/matrice
         *
         * Methode permettant d'afficher la carte/matrice
         * sur le terminal
         */
        void afficheCarte();

    protected:
        int tailleCarte; /**< Taille de la matrice/carte */
        vector<vector<int>> matrice; /**< Le tableau dynamique contenant les cout de passage d'une ville à l'autre */
        int villeDepart ; /**< La ville de depart du voyageur */
    private:

};

#endif // CARTE_H

