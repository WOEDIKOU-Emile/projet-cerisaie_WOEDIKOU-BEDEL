
#ifndef EMPLACEMENTS_H
#define EMPLACEMENTS_H

#include "structures.h"

/* ========== PROTOTYPES DES FONCTIONS ========== */

/**
 * Initialise le fichier des emplacements s'il n'existe pas
 */
void initialiserFichierEmplacements();

/**
 * Lit un emplacement � une position donn�e
 */
Emplacement lireEmplacement(int position);

/**
 * �crit un emplacement � une position donn�e
 */
void ecrireEmplacement(Emplacement emp, int position);

/**
 * Trouve le prochain num�ro d'emplacement disponible
 */
int trouverProchainNumEmplacement();

/**
 * Recherche un emplacement par son num�ro
 * Retourne la position dans le fichier, ou -1 si non trouv�
 */
int rechercherEmplacement(int numEmplacement);

/**
 * Affiche les d�tails d'un emplacement
 */
void afficherEmplacement(Emplacement emp);

/**
 * F1 : Cr�e un nouvel emplacement
 */
void creerEmplacement();

/**
 * F2 : Modifie un emplacement existant
 */
void modifierEmplacement();

/**
 * F3 : Supprime un emplacement (suppression logique)
 */
void supprimerEmplacement();

/**
 * F4 : Change le statut d'un emplacement
 */
void changerStatutEmplacement();

/**
 * F5 : Consulte les emplacements disponibles
 */
void consulterEmplacementsDisponibles();

/**
 * F6 : Consulte les emplacements par type
 */
void consulterEmplacementsParType();

/**
 * F7 : Consulte le d�tail d'un emplacement sp�cifique
 */
void consulterDetailEmplacement();

/**
 * F8 : Visualise le taux d'occupation
 */
void visualiserTauxOccupation();

#endif /* EMPLACEMENTS_H */

