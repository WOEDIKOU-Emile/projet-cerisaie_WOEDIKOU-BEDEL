
#ifndef UTILS_H
#define UTILS_H

#include "structures.h"

/* ========== PROTOTYPES DES FONCTIONS UTILITAIRES ========== */

/**
 * Efface l'ecran de la console
 */
void clearScreen();

/**
 * Met en pause le programme
 */
void pause();

/**
 * Saisit un entier avec validation
 */
int saisirEntier(const char *message);

/**
 * Saisit un float avec validation
 */
float saisirFloat(const char *message);

/**
 * Saisit une cha�ne de caract�res
 */
void saisirChaine(const char *message, char *chaine, int taille);

/**
 * Saisit une date avec validation
 */
Date saisirDate(const char *message);

/**
 * V�rifie si une date est valide
 */
int dateValide(Date d);

/**
 * Compare deux dates
 * Retourne : -1 si d1 < d2, 0 si d1 == d2, 1 si d1 > d2
 */
int comparerDates(Date d1, Date d2);

/**
 * Affiche une date au format JJ/MM/AAAA
 */
void afficherDate(Date d);

/**
 * Convertit un StatutEmplacement en chaine
 */
const char* statutEmplacementToString(StatutEmplacement s);

/**
 * Convertit un StatutSejour en chaine
 */
const char* statutSejourToString(StatutSejour s);

#endif /* UTILS_H */

