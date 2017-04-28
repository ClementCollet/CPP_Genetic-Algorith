#ifndef FICHIERMAIN_H
#define FICHIERMAIN_H

/**< Informations Generation */
#define TAILLE_GENERATION 500
#define POURCENTAGE_INDIVIDU_PARENTS (float) 60
#define POURCENTAGE_ENFANTS (float) 120
#define POURCENTAGE_INDIVIDU_CONSERVE (float) 5
#define MUTATION_RATE 70

/**< Nombre de Génération */
#define NOMBRE_DE_GENERATION 1000

/**< Choix de la méthode */
/**< 1=Eugénisme  2=Roulette  3=Rang  4=Joute 5=Uniforme */
#define CHOIX_DE_LA_METHODE_SELECTION_REPRODUCTEURS 2

/**< Choix de la méthode */
/**< 1=Mélange parents/enfants 2=Eugenisme complet */
#define CHOIX_DE_LA_METHODE_GENERATION_SUIVANTE 2

/**< Choix pour la carte */
/**< 1=Carte Aléatoire  2=chargement d'un fichier */
#define CHOIX_CARTE 1

/**< Taille carte si creation aleatoire */
#define TAILLE_CARTE 25

/**< Informations Fichiers */
#define NOM_FICHIER_ENTRE "fichiersmatrice/matrice25.txt"
#define NOM_FICHIER_SORTIE "fichierssortie/matrice25/1000_1000"

#endif // FICHIERMAIN_H

