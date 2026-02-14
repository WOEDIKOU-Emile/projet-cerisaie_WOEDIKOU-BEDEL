#ifndef STRUCTURES_H
#define STRUCTURES_H

/* ========== CONSTANTES ========== */
#define MAX_TYPES 10
#define MAX_NOM 50
#define FICHIER_TYPES "types_emplacement.dat"
#define FICHIER_EMPLACEMENTS "emplacements.dat"
#define FICHIER_SEJOURS "sejours.dat"

/* ========== �NUM�RATIONS ========== */

/**
 * Statut d'un emplacement
 */
typedef enum {
    DISPONIBLE,
    OCCUPE,
    EN_MAINTENANCE,
    HORS_SERVICE
} StatutEmplacement;

/**
 * Statut d'un s�jour
 */
typedef enum {
    EN_COURS,
    TERMINE,
    ANNULE
} StatutSejour;

/* ========== STRUCTURES ========== */

/**
 * Structure repr�sentant une date
 */
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

/**
 * Structure TYPE_EMPLACEMENT
 * Stock�e en m�moire (tableau) et dans un fichier
 */
typedef struct {
    char code[10];              // Code du type (ex: "CAR", "TEN")
    char libelle[50];           // Libell� (ex: "Caravane")
    float prixJourParPersonne;  // Prix par jour et par personne
    int actif;                  // 1 = actif, 0 = supprim� logiquement
} TypeEmplacement;

/**
 * Structure EMPLACEMENT
 * Stock�e dans un fichier random
 */
typedef struct {
    int numEmplacement;         // Num�ro unique (cl�)
    float surface;              // Surface en m�
    int nbMaxPersonnes;         // Capacit� maximale
    char codeType[10];          // R�f�rence vers TypeEmplacement
    StatutEmplacement statut;   // �tat actuel
    int actif;                  // 1 = actif, 0 = supprim� logiquement
} Emplacement;

/**
 * Structure SEJOUR
 * Stock�e dans un fichier random
 */
typedef struct {
    int numSejour;              // Num�ro unique (cl�)
    char nomResponsable[MAX_NOM]; // Nom du client
    Date dateDebut;             // Date d'arriv�e
    Date dateFin;               // Date de d�part
    int nbPersonnes;            // Nombre de personnes
    int numEmplacement;         // R�f�rence vers Emplacement
    StatutSejour statutSejour;  // �tat du s�jour
    int actif;                  // 1 = actif, 0 = supprim� logiquement
} Sejour;

#endif /* STRUCTURES_H */

