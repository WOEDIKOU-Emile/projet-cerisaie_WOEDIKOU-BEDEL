
#ifndef SEJOURS_H
#define SEJOURS_H

#include "structures.h"

/* ========== PROTOTYPES DES FONCTIONS ========== */

/**
 * Initialise le fichier des s�jours s'il n'existe pas
 */
void initialiserFichierSejours();

/**
 * Lit un s�jour � une position donn�e
 */
Sejour lireSejour(int position);

/**
 * �crit un s�jour � une position donn�e
 */
void ecrireSejour(Sejour sej, int position);

/**
 * Trouve le prochain num�ro de s�jour disponible
 */
int trouverProchainNumSejour();

/**
 * Recherche un s�jour par son num�ro
 * Retourne la position dans le fichier, ou -1 si non trouv�
 */
int rechercherSejour(int numSejour);

/**
 * Affiche les d�tails d'un s�jour
 */
void afficherSejour(Sejour sej);

/**
 * F11 : V�rifie si un emplacement est disponible sur une p�riode
 * Retourne 1 si disponible, 0 sinon
 */
int verifierDisponibilite(int numEmplacement, Date debut, Date fin);

/**
 * F16 : D�tecte les conflits de r�servation
 * Retourne 1 s'il y a conflit, 0 sinon
 */
int detecterConflitReservation(int numEmplacement, Date debut, Date fin, int numSejourExclure);

/**
 * F17 : V�rifie si la capacit� de l'emplacement est suffisante
 * Retourne 1 si OK, 0 si d�passement
 */
int verifierCapacite(int numEmplacement, int nbPersonnes);

/**
 * F9 : Attribue un emplacement � un nouveau s�jour
 */
void attribuerEmplacement();

/**
 * F10 : Lib�re un emplacement (fin de s�jour)
 */
void libererEmplacement();

/**
 * F12 : Change l'emplacement d'un s�jour en cours
 */
void changerEmplacementSejour();

/**
 * Consulte les s�jours en cours
 */
void consulterSejourEnCours();

/**
 * F18 : Identifie les emplacements sous-utilis�s
 */
void identifierEmplacementsSousUtilises();

#endif /* SEJOURS_H */

