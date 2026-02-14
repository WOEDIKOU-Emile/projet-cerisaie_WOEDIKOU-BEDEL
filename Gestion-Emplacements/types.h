#ifndef TYPES_H
#define TYPES_H

#include "structures.h"

/* ========== VARIABLES GLOBALES ========== */
extern TypeEmplacement tabTypes[MAX_TYPES];  // Tableau des types en m�moire
extern int nbTypes;                          // Nombre de types charg�s

/* ========== PROTOTYPES DES FONCTIONS ========== */

/**
 * Charge les types d'emplacements depuis le fichier au d�marrage
 */
void chargerTypes();

/**
 * Sauvegarde les types d'emplacements dans le fichier � la fermeture
 */
void sauvegarderTypes();

/**
 * Affiche tous les types d'emplacements actifs
 */
void afficherTypes();

/**
 * Recherche un type par son code
 * Retourne l'index dans le tableau, ou -1 si non trouv�
 */
int rechercherType(const char *code);

/**
 * F13 : Cr�e un nouveau type d'emplacement
 */
void creerType();

/**
 * F14 : Modifie le tarif d'un type d'emplacement
 */
void modifierTarifType();

/**
 * F15 : Consulte tous les tarifs
 */
void consulterTarifs();

#endif /* TYPES_H */

