
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emplacements.h"
#include "types.h"
#include "utils.h"
#include "sejours.h"

/**
 * Initialise le fichier des emplacements s'il n'existe pas
 */
void initialiserFichierEmplacements() {
    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");

    if (f == NULL) {
        // Créer le fichier
        f = fopen(FICHIER_EMPLACEMENTS, "wb");
        if (f != NULL) {
            fclose(f);
            printf("Fichier emplacements créé.\n");
        }
    } else {
        fclose(f);
    }
}

/**
 * Lit un emplacement à une position donnée
 */
Emplacement lireEmplacement(int position) {
    Emplacement emp;
    emp.actif = 0; // Par défaut, invalide

    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) return emp;

    fseek(f, position * sizeof(Emplacement), SEEK_SET);
    fread(&emp, sizeof(Emplacement), 1, f);
    fclose(f);

    return emp;
}

/**
 * Écrit un emplacement à une position donnée
 */
void ecrireEmplacement(Emplacement emp, int position) {
    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb+");
    if (f == NULL) {
        f = fopen(FICHIER_EMPLACEMENTS, "wb");
    }

    fseek(f, position * sizeof(Emplacement), SEEK_SET);
    fwrite(&emp, sizeof(Emplacement), 1, f);
    fclose(f);
}

/**
 * Trouve le prochain numéro d'emplacement disponible
 */
int trouverProchainNumEmplacement() {
    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) return 1;

    int maxNum = 0;
    Emplacement emp;

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (emp.actif && emp.numEmplacement > maxNum) {
            maxNum = emp.numEmplacement;
        }
    }

    fclose(f);
    return maxNum + 1;
}

/**
 * Recherche un emplacement par son numéro
 * Retourne la position dans le fichier, ou -1 si non trouvé
 */
int rechercherEmplacement(int numEmplacement) {
    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) return -1;

    Emplacement emp;
    int position = 0;

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (emp.actif && emp.numEmplacement == numEmplacement) {
            fclose(f);
            return position;
        }
        position++;
    }

    fclose(f);
    return -1;
}

/**
 * Affiche les détails d'un emplacement
 */
void afficherEmplacement(Emplacement emp) {
    printf("\n--- Emplacement #%d ---\n", emp.numEmplacement);
    printf("Surface         : %.2f m²\n", emp.surface);
    printf("Capacité max    : %d personnes\n", emp.nbMaxPersonnes);
    printf("Type            : %s\n", emp.codeType);
    printf("Statut          : %s\n", statutEmplacementToString(emp.statut));
}

/**
 * F1 : Crée un nouvel emplacement
 */
void creerEmplacement() {
    clearScreen();
    printf("\n========== CRÉER UN EMPLACEMENT ==========\n");

    Emplacement nouveau;

    nouveau.numEmplacement = trouverProchainNumEmplacement();
    printf("Numéro attribué automatiquement : %d\n\n", nouveau.numEmplacement);

    nouveau.surface = saisirFloat("Surface (m²) : ");
    if (nouveau.surface <= 0) {
        printf("Erreur : la surface doit être positive.\n");
        pause();
        return;
    }

    nouveau.nbMaxPersonnes = saisirEntier("Capacité maximale (personnes) : ");
    if (nouveau.nbMaxPersonnes <= 0) {
        printf("Erreur : la capacité doit être positive.\n");
        pause();
        return;
    }

    // Afficher les types disponibles
    printf("\nTypes disponibles :\n");
    afficherTypes();

    saisirChaine("\nCode du type : ", nouveau.codeType, 10);

    // Vérifier que le type existe
    if (rechercherType(nouveau.codeType) == -1) {
        printf("Erreur : type inexistant.\n");
        pause();
        return;
    }

    nouveau.statut = DISPONIBLE;
    nouveau.actif = 1;

    // Trouver la première position libre
    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    int position = 0;

    if (f != NULL) {
        Emplacement temp;
        while (fread(&temp, sizeof(Emplacement), 1, f) == 1) {
            if (!temp.actif) {
                break;
            }
            position++;
        }
        fclose(f);
    }

    ecrireEmplacement(nouveau, position);

    printf("\n✓ Emplacement #%d créé avec succès !\n", nouveau.numEmplacement);
    pause();
}

/**
 * F2 : Modifie un emplacement existant
 */
void modifierEmplacement() {
    clearScreen();
    printf("\n========== MODIFIER UN EMPLACEMENT ==========\n");

    int num = saisirEntier("Numéro de l'emplacement à modifier : ");

    int position = rechercherEmplacement(num);
    if (position == -1) {
        printf("Erreur : emplacement non trouvé.\n");
        pause();
        return;
    }

    Emplacement emp = lireEmplacement(position);

    printf("\nEmplacement actuel :\n");
    afficherEmplacement(emp);

    printf("\n--- Nouvelles valeurs (Entrée pour conserver) ---\n");

    float surface = saisirFloat("Nouvelle surface (m²) : ");
    if (surface > 0) emp.surface = surface;

    int capacite = saisirEntier("Nouvelle capacité : ");
    if (capacite > 0) emp.nbMaxPersonnes = capacite;

    char type[10];
    saisirChaine("Nouveau type (vide pour conserver) : ", type, 10);
    if (strlen(type) > 0) {
        if (rechercherType(type) != -1) {
            strcpy(emp.codeType, type);
        } else {
            printf("Attention : type invalide, non modifié.\n");
        }
    }

    ecrireEmplacement(emp, position);

    printf("\n✓ Emplacement modifié avec succès !\n");
    pause();
}

/**
 * F3 : Supprime un emplacement (suppression logique)
 */
void supprimerEmplacement() {
    clearScreen();
    printf("\n========== SUPPRIMER UN EMPLACEMENT ==========\n");

    int num = saisirEntier("Numéro de l'emplacement à supprimer : ");

    int position = rechercherEmplacement(num);
    if (position == -1) {
        printf("Erreur : emplacement non trouvé.\n");
        pause();
        return;
    }

    Emplacement emp = lireEmplacement(position);

    afficherEmplacement(emp);

    printf("\nÊtes-vous sûr de vouloir supprimer cet emplacement ? (O/N) : ");
    char reponse;
    scanf(" %c", &reponse);

    if (reponse == 'O' || reponse == 'o') {
        emp.actif = 0; // Suppression logique
        ecrireEmplacement(emp, position);
        printf("\n✓ Emplacement supprimé avec succès !\n");
    } else {
        printf("\nSuppression annulée.\n");
    }

    pause();
}

/**
 * F4 : Change le statut d'un emplacement
 */
void changerStatutEmplacement() {
    clearScreen();
    printf("\n========== CHANGER LE STATUT D'UN EMPLACEMENT ==========\n");

    int num = saisirEntier("Numéro de l'emplacement : ");

    int position = rechercherEmplacement(num);
    if (position == -1) {
        printf("Erreur : emplacement non trouvé.\n");
        pause();
        return;
    }

    Emplacement emp = lireEmplacement(position);

    afficherEmplacement(emp);

    printf("\nNouveau statut :\n");
    printf("  0 - Disponible\n");
    printf("  1 - Occupé\n");
    printf("  2 - En maintenance\n");
    printf("  3 - Hors service\n");

    int choix = saisirEntier("Choix : ");

    if (choix < 0 || choix > 3) {
        printf("Erreur : choix invalide.\n");
        pause();
        return;
    }

    emp.statut = (StatutEmplacement)choix;
    ecrireEmplacement(emp, position);

    printf("\n✓ Statut modifié : %s\n", statutEmplacementToString(emp.statut));
    pause();
}

/**
 * F5 : Consulte les emplacements disponibles
 */
void consulterEmplacementsDisponibles() {
    clearScreen();
    printf("\n========== EMPLACEMENTS DISPONIBLES ==========\n");

    printf("\nRechercher pour une période spécifique ? (O/N) : ");
    char reponse;
    scanf(" %c", &reponse);

    Date debut, fin;
    int avecDates = 0;

    if (reponse == 'O' || reponse == 'o') {
        debut = saisirDate("Date de début :");
        fin = saisirDate("Date de fin :");
        avecDates = 1;
    }

    printf("\n%-10s %-10s %-15s %-15s %s\n",
           "Num", "Surface", "Capacité", "Type", "Statut");
    printf("------------------------------------------------------------------\n");

    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) {
        printf("Aucun emplacement.\n");
        pause();
        return;
    }

    Emplacement emp;
    int compteur = 0;

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (!emp.actif) continue;

        int afficher = 0;

        if (avecDates) {
            // Vérifier la disponibilité sur la période
            if (verifierDisponibilite(emp.numEmplacement, debut, fin)) {
                afficher = 1;
            }
        } else {
            // Juste les emplacements avec statut DISPONIBLE
            if (emp.statut == DISPONIBLE) {
                afficher = 1;
            }
        }

        if (afficher) {
            printf("%-10d %-10.2f %-15d %-15s %s\n",
                   emp.numEmplacement,
                   emp.surface,
                   emp.nbMaxPersonnes,
                   emp.codeType,
                   statutEmplacementToString(emp.statut));
            compteur++;
        }
    }

    fclose(f);

    if (compteur == 0) {
        printf("Aucun emplacement disponible.\n");
    } else {
        printf("\nTotal : %d emplacement(s) disponible(s)\n", compteur);
    }

    pause();
}

/**
 * F6 : Consulte les emplacements par type
 */
void consulterEmplacementsParType() {
    clearScreen();
    printf("\n========== EMPLACEMENTS PAR TYPE ==========\n");

    afficherTypes();

    char code[10];
    saisirChaine("\nCode du type recherché : ", code, 10);

    if (rechercherType(code) == -1) {
        printf("Erreur : type inexistant.\n");
        pause();
        return;
    }

    printf("\n%-10s %-10s %-15s %s\n",
           "Num", "Surface", "Capacité", "Statut");
    printf("-----------------------------------------------------\n");

    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) {
        printf("Aucun emplacement.\n");
        pause();
        return;
    }

    Emplacement emp;
    int compteur = 0;

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (emp.actif && strcmp(emp.codeType, code) == 0) {
            printf("%-10d %-10.2f %-15d %s\n",
                   emp.numEmplacement,
                   emp.surface,
                   emp.nbMaxPersonnes,
                   statutEmplacementToString(emp.statut));
            compteur++;
        }
    }

    fclose(f);

    if (compteur == 0) {
        printf("Aucun emplacement de ce type.\n");
    } else {
        printf("\nTotal : %d emplacement(s)\n", compteur);
    }

    pause();
}

/**
 * F7 : Consulte le détail d'un emplacement spécifique
 */
void consulterDetailEmplacement() {
    clearScreen();
    printf("\n========== DÉTAIL D'UN EMPLACEMENT ==========\n");

    int num = saisirEntier("Numéro de l'emplacement : ");

    int position = rechercherEmplacement(num);
    if (position == -1) {
        printf("Erreur : emplacement non trouvé.\n");
        pause();
        return;
    }

    Emplacement emp = lireEmplacement(position);
    afficherEmplacement(emp);

    // Rechercher le prix du type
    int indexType = rechercherType(emp.codeType);
    if (indexType != -1) {
        printf("Prix du type    : %.2f €/jour/personne\n",
               tabTypes[indexType].prixJourParPersonne);
    }

    pause();
}

/**
 * F8 : Visualise le taux d'occupation
 */
void visualiserTauxOccupation() {
    clearScreen();
    printf("\n========== TAUX D'OCCUPATION ==========\n");

    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) {
        printf("Aucun emplacement.\n");
        pause();
        return;
    }

    int total = 0, occupes = 0, disponibles = 0, maintenance = 0;
    Emplacement emp;

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (emp.actif) {
            total++;
            switch (emp.statut) {
                case OCCUPE: occupes++; break;
                case DISPONIBLE: disponibles++; break;
                case EN_MAINTENANCE: maintenance++; break;
                default: break;
            }
        }
    }

    fclose(f);

    if (total == 0) {
        printf("Aucun emplacement dans le système.\n");
    } else {
        printf("Total d'emplacements : %d\n", total);
        printf("Occupés              : %d (%.1f%%)\n",
               occupes, (float)occupes * 100 / total);
        printf("Disponibles          : %d (%.1f%%)\n",
               disponibles, (float)disponibles * 100 / total);
        printf("En maintenance       : %d (%.1f%%)\n",
               maintenance, (float)maintenance * 100 / total);
    }

    pause();
}

