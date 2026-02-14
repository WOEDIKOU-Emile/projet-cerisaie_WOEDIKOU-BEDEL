#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/**
 * Efface l'�cran de la console
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Met en pause le programme
 */
void pause() {
    printf("\nAppuyez sur Entr�e pour continuer...");
    getchar();
    getchar();
}

/**
 * Saisit un entier avec validation
 */
int saisirEntier(const char *message) {
    int valeur;
    printf("%s", message);
    while (scanf("%d", &valeur) != 1) {
        while (getchar() != '\n'); // Vider le buffer
        printf("Entr�e invalide. %s", message);
    }
    return valeur;
}

/**
 * Saisit un float avec validation
 */
float saisirFloat(const char *message) {
    float valeur;
    printf("%s", message);
    while (scanf("%f", &valeur) != 1) {
        while (getchar() != '\n');
        printf("Entr�e invalide. %s", message);
    }
    return valeur;
}

/**
 * Saisit une cha�ne de caract�res
 */
void saisirChaine(const char *message, char *chaine, int taille) {
    printf("%s", message);
    getchar(); // Consommer le '\n' pr�c�dent
    fgets(chaine, taille, stdin);
    // Enlever le '\n' final
    chaine[strcspn(chaine, "\n")] = '\0';
}

/**
 * Saisit une date avec validation
 */
Date saisirDate(const char *message) {
    Date d;
    do {
        printf("%s\n", message);
        d.jour = saisirEntier("  Jour (1-31) : ");
        d.mois = saisirEntier("  Mois (1-12) : ");
        d.annee = saisirEntier("  Ann�e : ");

        if (!dateValide(d)) {
            printf("Date invalide. Veuillez r�essayer.\n");
        }
    } while (!dateValide(d));

    return d;
}

/**
 * V�rifie si une date est valide
 */
int dateValide(Date d) {
    if (d.annee < 1900 || d.annee > 2100) return 0;
    if (d.mois < 1 || d.mois > 12) return 0;

    int joursParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ann�e bissextile
    if ((d.annee % 4 == 0 && d.annee % 100 != 0) || (d.annee % 400 == 0)) {
        joursParMois[1] = 29;
    }

    if (d.jour < 1 || d.jour > joursParMois[d.mois - 1]) return 0;

    return 1;
}

/**
 * Compare deux dates
 * Retourne : -1 si d1 < d2, 0 si d1 == d2, 1 si d1 > d2
 */
int comparerDates(Date d1, Date d2) {
    if (d1.annee != d2.annee) return (d1.annee < d2.annee) ? -1 : 1;
    if (d1.mois != d2.mois) return (d1.mois < d2.mois) ? -1 : 1;
    if (d1.jour != d2.jour) return (d1.jour < d2.jour) ? -1 : 1;
    return 0;
}

/**
 * Affiche une date au format JJ/MM/AAAA
 */
void afficherDate(Date d) {
    printf("%02d/%02d/%04d", d.jour, d.mois, d.annee);
}

/**
 * Convertit un StatutEmplacement en cha�ne
 */
const char* statutEmplacementToString(StatutEmplacement s) {
    switch (s) {
        case DISPONIBLE: return "Disponible";
        case OCCUPE: return "Occup�";
        case EN_MAINTENANCE: return "En maintenance";
        case HORS_SERVICE: return "Hors service";
        default: return "Inconnu";
    }
}

/**
 * Convertit un StatutSejour en cha�ne
 */
const char* statutSejourToString(StatutSejour s) {
    switch (s) {
        case EN_COURS: return "En cours";
        case TERMINE: return "Termin�";
        case ANNULE: return "Annul�";
        default: return "Inconnu";
    }
}



