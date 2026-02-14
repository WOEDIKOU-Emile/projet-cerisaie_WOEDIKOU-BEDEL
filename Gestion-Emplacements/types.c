
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

/* Variables globales pour les types */
TypeEmplacement tabTypes[MAX_TYPES];
int nbTypes = 0;

/**
 * Charge les types d'emplacements depuis le fichier au démarrage
 */
void chargerTypes() {
    FILE *f = fopen(FICHIER_TYPES, "rb");

    if (f == NULL) {
        // Fichier n'existe pas, initialiser avec des valeurs par défaut
        printf("Initialisation des types d'emplacements par défaut...\n");

        strcpy(tabTypes[0].code, "TEN");
        strcpy(tabTypes[0].libelle, "Tente");
        tabTypes[0].prixJourParPersonne = 11.00;
        tabTypes[0].actif = 1;

        strcpy(tabTypes[1].code, "CAR");
        strcpy(tabTypes[1].libelle, "Caravane");
        tabTypes[1].prixJourParPersonne = 13.50;
        tabTypes[1].actif = 1;

        strcpy(tabTypes[2].code, "CCR");
        strcpy(tabTypes[2].libelle, "Camping-car");
        tabTypes[2].prixJourParPersonne = 14.00;
        tabTypes[2].actif = 1;

        strcpy(tabTypes[3].code, "BUN");
        strcpy(tabTypes[3].libelle, "Bungalow");
        tabTypes[3].prixJourParPersonne = 17.50;
        tabTypes[3].actif = 1;

        nbTypes = 4;

        // Sauvegarder immédiatement
        sauvegarderTypes();
    } else {
        // Charger depuis le fichier
        fread(&nbTypes, sizeof(int), 1, f);
        fread(tabTypes, sizeof(TypeEmplacement), nbTypes, f);
        fclose(f);
        printf("Types d'emplacements chargés : %d type(s)\n", nbTypes);
    }
}

/**
 * Sauvegarde les types d'emplacements dans le fichier à la fermeture
 */
void sauvegarderTypes() {
    FILE *f = fopen(FICHIER_TYPES, "wb");

    if (f == NULL) {
        printf("Erreur : impossible de sauvegarder les types d'emplacements.\n");
        return;
    }

    fwrite(&nbTypes, sizeof(int), 1, f);
    fwrite(tabTypes, sizeof(TypeEmplacement), nbTypes, f);
    fclose(f);

    printf("Types d'emplacements sauvegardés avec succès.\n");
}

/**
 * Affiche tous les types d'emplacements actifs
 */
void afficherTypes() {
    printf("\n========== TYPES D'EMPLACEMENTS ==========\n");
    printf("%-10s %-20s %15s\n", "Code", "Libellé", "Prix/jour/pers");
    printf("---------------------------------------------------\n");

    int trouve = 0;
    for (int i = 0; i < nbTypes; i++) {
        if (tabTypes[i].actif) {
            printf("%-10s %-20s %12.2f €\n",
                   tabTypes[i].code,
                   tabTypes[i].libelle,
                   tabTypes[i].prixJourParPersonne);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun type d'emplacement disponible.\n");
    }
    printf("==========================================\n");
}

/**
 * Recherche un type par son code
 * Retourne l'index dans le tableau, ou -1 si non trouvé
 */
int rechercherType(const char *code) {
    for (int i = 0; i < nbTypes; i++) {
        if (tabTypes[i].actif && strcmp(tabTypes[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * F13 : Crée un nouveau type d'emplacement
 */
void creerType() {
    clearScreen();
    printf("\n========== CRÉER UN TYPE D'EMPLACEMENT ==========\n");

    if (nbTypes >= MAX_TYPES) {
        printf("Erreur : nombre maximum de types atteint (%d).\n", MAX_TYPES);
        pause();
        return;
    }

    TypeEmplacement nouveau;

    // Saisie du code
    saisirChaine("Code du type (ex: TEN, CAR) : ", nouveau.code, 10);

    // Vérifier que le code n'existe pas déjà
    if (rechercherType(nouveau.code) != -1) {
        printf("Erreur : ce code existe déjà.\n");
        pause();
        return;
    }

    // Saisie du libellé
    saisirChaine("Libellé (ex: Tente) : ", nouveau.libelle, 50);

    // Saisie du prix
    nouveau.prixJourParPersonne = saisirFloat("Prix par jour par personne (€) : ");

    if (nouveau.prixJourParPersonne <= 0) {
        printf("Erreur : le prix doit être positif.\n");
        pause();
        return;
    }

    nouveau.actif = 1;

    // Ajouter au tableau
    tabTypes[nbTypes] = nouveau;
    nbTypes++;

    printf("\n✓ Type créé avec succès !\n");
    pause();
}

/**
 * F14 : Modifie le tarif d'un type d'emplacement
 */
void modifierTarifType() {
    clearScreen();
    printf("\n========== MODIFIER UN TARIF ==========\n");

    afficherTypes();

    char code[10];
    saisirChaine("\nCode du type à modifier : ", code, 10);

    int index = rechercherType(code);

    if (index == -1) {
        printf("Erreur : type non trouvé.\n");
        pause();
        return;
    }

    printf("\nType actuel : %s - %.2f €/jour/personne\n",
           tabTypes[index].libelle,
           tabTypes[index].prixJourParPersonne);

    float nouveauPrix = saisirFloat("Nouveau prix (€/jour/personne) : ");

    if (nouveauPrix <= 0) {
        printf("Erreur : le prix doit être positif.\n");
        pause();
        return;
    }

    tabTypes[index].prixJourParPersonne = nouveauPrix;

    printf("\n✓ Tarif modifié avec succès !\n");
    pause();
}

/**
 * F15 : Consulte tous les tarifs
 */
void consulterTarifs() {
    clearScreen();
    afficherTypes();
    pause();
}

