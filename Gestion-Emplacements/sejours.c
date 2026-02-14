
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sejours.h"
#include "emplacements.h"
#include "utils.h"

/**
 * Initialise le fichier des séjours s'il n'existe pas
 */
void initialiserFichierSejours() {
    FILE *f = fopen(FICHIER_SEJOURS, "rb");

    if (f == NULL) {
        f = fopen(FICHIER_SEJOURS, "wb");
        if (f != NULL) {
            fclose(f);
            printf("Fichier séjours créé.\n");
        }
    } else {
        fclose(f);
    }
}

/**
 * Lit un séjour à une position donnée
 */
Sejour lireSejour(int position) {
    Sejour sej;
    sej.actif = 0;

    FILE *f = fopen(FICHIER_SEJOURS, "rb");
    if (f == NULL) return sej;

    fseek(f, position * sizeof(Sejour), SEEK_SET);
    fread(&sej, sizeof(Sejour), 1, f);
    fclose(f);

    return sej;
}

/**
 * Écrit un séjour à une position donnée
 */
void ecrireSejour(Sejour sej, int position) {
    FILE *f = fopen(FICHIER_SEJOURS, "rb+");
    if (f == NULL) {
        f = fopen(FICHIER_SEJOURS, "wb");
    }

    fseek(f, position * sizeof(Sejour), SEEK_SET);
    fwrite(&sej, sizeof(Sejour), 1, f);
    fclose(f);
}

/**
 * Trouve le prochain numéro de séjour disponible
 */
int trouverProchainNumSejour() {
    FILE *f = fopen(FICHIER_SEJOURS, "rb");
    if (f == NULL) return 1;

    int maxNum = 0;
    Sejour sej;

    while (fread(&sej, sizeof(Sejour), 1, f) == 1) {
        if (sej.actif && sej.numSejour > maxNum) {
            maxNum = sej.numSejour;
        }
    }

    fclose(f);
    return maxNum + 1;
}

/**
 * Recherche un séjour par son numéro
 * Retourne la position dans le fichier, ou -1 si non trouvé
 */
int rechercherSejour(int numSejour) {
    FILE *f = fopen(FICHIER_SEJOURS, "rb");
    if (f == NULL) return -1;

    Sejour sej;
    int position = 0;

    while (fread(&sej, sizeof(Sejour), 1, f) == 1) {
        if (sej.actif && sej.numSejour == numSejour) {
            fclose(f);
            return position;
        }
        position++;
    }

    fclose(f);
    return -1;
}

/**
 * Affiche les détails d'un séjour
 */
void afficherSejour(Sejour sej) {
    printf("\n--- Séjour #%d ---\n", sej.numSejour);
    printf("Responsable     : %s\n", sej.nomResponsable);
    printf("Date début      : ");
    afficherDate(sej.dateDebut);
    printf("\nDate fin        : ");
    afficherDate(sej.dateFin);
    printf("\nNb personnes    : %d\n", sej.nbPersonnes);
    printf("Emplacement     : #%d\n", sej.numEmplacement);
    printf("Statut          : %s\n", statutSejourToString(sej.statutSejour));
}

/**
 * F16 : Détecte les conflits de réservation
 */
int detecterConflitReservation(int numEmplacement, Date debut, Date fin, int numSejourExclure) {
    FILE *f = fopen(FICHIER_SEJOURS, "rb");
    if (f == NULL) return 0;

    Sejour sej;

    while (fread(&sej, sizeof(Sejour), 1, f) == 1) {
        if (!sej.actif || sej.statutSejour == ANNULE || sej.statutSejour == TERMINE) {
            continue;
        }

        if (sej.numSejour == numSejourExclure) {
            continue;
        }

        if (sej.numEmplacement != numEmplacement) {
            continue;
        }

        // Vérifier le chevauchement des périodes
        if (comparerDates(debut, sej.dateFin) <= 0 &&
            comparerDates(fin, sej.dateDebut) >= 0) {
            fclose(f);
            return 1; // Conflit détecté
        }
    }

    fclose(f);
    return 0; // Pas de conflit
}

/**
 * F11 : Vérifie si un emplacement est disponible sur une période
 */
int verifierDisponibilite(int numEmplacement, Date debut, Date fin) {
    // Vérifier que l'emplacement existe et est utilisable
    int position = rechercherEmplacement(numEmplacement);
    if (position == -1) return 0;

    Emplacement emp = lireEmplacement(position);
    if (emp.statut == HORS_SERVICE || emp.statut == EN_MAINTENANCE) {
        return 0;
    }

    // Vérifier qu'il n'y a pas de conflit avec un séjour existant
    return !detecterConflitReservation(numEmplacement, debut, fin, -1);
}

/**
 * F17 : Vérifie si la capacité de l'emplacement est suffisante
 */
int verifierCapacite(int numEmplacement, int nbPersonnes) {
    int position = rechercherEmplacement(numEmplacement);
    if (position == -1) return 0;

    Emplacement emp = lireEmplacement(position);
    return (nbPersonnes <= emp.nbMaxPersonnes);
}

/**
 * F9 : Attribue un emplacement à un nouveau séjour
 */
void attribuerEmplacement() {
    clearScreen();
    printf("\n========== ATTRIBUER UN EMPLACEMENT ==========\n");

    Sejour nouveau;

    nouveau.numSejour = trouverProchainNumSejour();
    printf("Numéro de séjour : %d\n\n", nouveau.numSejour);

    saisirChaine("Nom du responsable : ", nouveau.nomResponsable, MAX_NOM);

    nouveau.dateDebut = saisirDate("Date de début du séjour :");
    nouveau.dateFin = saisirDate("Date de fin du séjour :");

    // Vérifier que la date de fin est après la date de début
    if (comparerDates(nouveau.dateFin, nouveau.dateDebut) <= 0) {
        printf("Erreur : la date de fin doit être après la date de début.\n");
        pause();
        return;
    }

    nouveau.nbPersonnes = saisirEntier("Nombre de personnes : ");
    if (nouveau.nbPersonnes <= 0) {
        printf("Erreur : le nombre de personnes doit être positif.\n");
        pause();
        return;
    }

    // Proposer les emplacements disponibles
    printf("\n--- Emplacements disponibles ---\n");

    FILE *f = fopen(FICHIER_EMPLACEMENTS, "rb");
    if (f == NULL) {
        printf("Aucun emplacement disponible.\n");
        pause();
        return;
    }

    Emplacement emp;
    int compteur = 0;

    printf("%-10s %-10s %-15s %-15s\n", "Num", "Surface", "Capacité", "Type");
    printf("-------------------------------------------------------\n");

    while (fread(&emp, sizeof(Emplacement), 1, f) == 1) {
        if (emp.actif &&
            verifierDisponibilite(emp.numEmplacement, nouveau.dateDebut, nouveau.dateFin) &&
            emp.nbMaxPersonnes >= nouveau.nbPersonnes) {
            printf("%-10d %-10.2f %-15d %-15s\n",
                   emp.numEmplacement,
                   emp.surface,
                   emp.nbMaxPersonnes,
                   emp.codeType);
            compteur++;
        }
    }

    fclose(f);

    if (compteur == 0) {
        printf("Aucun emplacement disponible pour ces critères.\n");
        pause();
        return;
    }

    nouveau.numEmplacement = saisirEntier("\nNuméro de l'emplacement à attribuer : ");

    // Vérifier que l'emplacement existe et est disponible
    if (!verifierDisponibilite(nouveau.numEmplacement, nouveau.dateDebut, nouveau.dateFin)) {
        printf("Erreur : emplacement non disponible.\n");
        pause();
        return;
    }

    // Vérifier la capacité
    if (!verifierCapacite(nouveau.numEmplacement, nouveau.nbPersonnes)) {
        printf("Erreur : capacité insuffisante pour cet emplacement.\n");
        pause();
        return;
    }

    nouveau.statutSejour = EN_COURS;
    nouveau.actif = 1;

    // Trouver la première position libre dans le fichier
    FILE *fSej = fopen(FICHIER_SEJOURS, "rb");
    int position = 0;

    if (fSej != NULL) {
        Sejour temp;
        while (fread(&temp, sizeof(Sejour), 1, fSej) == 1) {
            if (!temp.actif) {
                break;
            }
            position++;
        }
        fclose(fSej);
    }

    ecrireSejour(nouveau, position);

    // Mettre à jour le statut de l'emplacement
    int posEmp = rechercherEmplacement(nouveau.numEmplacement);
    Emplacement empModif = lireEmplacement(posEmp);
    empModif.statut = OCCUPE;
    ecrireEmplacement(empModif, posEmp);

    printf("\n✓ Séjour #%d créé et emplacement #%d attribué avec succès !\n",
           nouveau.numSejour, nouveau.numEmplacement);
    pause();
}

/**
 * F10 : Libère un emplacement (fin de séjour)
 */
void libererEmplacement() {
    clearScreen();
    printf("\n========== LIBÉRER UN EMPLACEMENT ==========\n");

    int numSejour = saisirEntier("Numéro du séjour à terminer : ");

    int position = rechercherSejour(numSejour);
    if (position == -1) {
        printf("Erreur : séjour non trouvé.\n");
        pause();
        return;
    }

    Sejour sej = lireSejour(position);

    if (sej.statutSejour == TERMINE) {
        printf("Ce séjour est déjà terminé.\n");
        pause();
        return;
    }

    afficherSejour(sej);

    // Marquer le séjour comme terminé
    sej.statutSejour = TERMINE;
    ecrireSejour(sej, position);

    // Libérer l'emplacement
    int posEmp = rechercherEmplacement(sej.numEmplacement);
    if (posEmp != -1) {
        Emplacement emp = lireEmplacement(posEmp);
        emp.statut = DISPONIBLE;
        ecrireEmplacement(emp, posEmp);
    }

    printf("\n✓ Séjour terminé et emplacement #%d libéré !\n", sej.numEmplacement);
    pause();
}

/**
 * F12 : Change l'emplacement d'un séjour en cours
 */
void changerEmplacementSejour() {
    clearScreen();
    printf("\n========== CHANGER L'EMPLACEMENT D'UN SÉJOUR ==========\n");

    int numSejour = saisirEntier("Numéro du séjour : ");

    int position = rechercherSejour(numSejour);
    if (position == -1) {
        printf("Erreur : séjour non trouvé.\n");
        pause();
        return;
    }

    Sejour sej = lireSejour(position);

    if (sej.statutSejour != EN_COURS) {
        printf("Erreur : seuls les séjours en cours peuvent être modifiés.\n");
        pause();
        return;
    }

    afficherSejour(sej);

    int ancienEmplacement = sej.numEmplacement;

    int nouvelEmplacement = saisirEntier("\nNouveau numéro d'emplacement : ");

    // Vérifier disponibilité (en excluant le séjour actuel)
    if (detecterConflitReservation(nouvelEmplacement, sej.dateDebut, sej.dateFin, sej.numSejour)) {
        printf("Erreur : l'emplacement n'est pas disponible sur cette période.\n");
        pause();
        return;
    }

    if (!verifierCapacite(nouvelEmplacement, sej.nbPersonnes)) {
        printf("Erreur : capacité insuffisante.\n");
        pause();
        return;
    }

    // Mettre à jour le séjour
    sej.numEmplacement = nouvelEmplacement;
    ecrireSejour(sej, position);

    // Libérer l'ancien emplacement
    int posAncien = rechercherEmplacement(ancienEmplacement);
    if (posAncien != -1) {
        Emplacement empAncien = lireEmplacement(posAncien);
        empAncien.statut = DISPONIBLE;
        ecrireEmplacement(empAncien, posAncien);
    }

    // Occuper le nouvel emplacement
    int posNouveau = rechercherEmplacement(nouvelEmplacement);
    if (posNouveau != -1) {
        Emplacement empNouveau = lireEmplacement(posNouveau);
        empNouveau.statut = OCCUPE;
        ecrireEmplacement(empNouveau, posNouveau);
    }

    printf("\n✓ Emplacement changé : #%d → #%d\n", ancienEmplacement, nouvelEmplacement);
    pause();
}

/**
 * Consulte les séjours en cours
 */
void consulterSejourEnCours() {
    clearScreen();
    printf("\n========== SÉJOURS EN COURS ==========\n");

    FILE *f = fopen(FICHIER_SEJOURS, "rb");
    if (f == NULL) {
        printf("Aucun séjour.\n");
        pause();
        return;
    }

    Sejour sej;
    int compteur = 0;

    printf("%-10s %-25s %-12s %-12s %-10s\n",
           "Num", "Responsable", "Début", "Fin", "Emplacement");
    printf("--------------------------------------------------------------------------\n");

    while (fread(&sej, sizeof(Sejour), 1, f) == 1) {
        if (sej.actif && sej.statutSejour == EN_COURS) {
            printf("%-10d %-25s ", sej.numSejour, sej.nomResponsable);
            afficherDate(sej.dateDebut);
            printf("  ");
            afficherDate(sej.dateFin);
            printf("  #%-10d\n", sej.numEmplacement);
            compteur++;
        }
    }

    fclose(f);

    if (compteur == 0) {
        printf("Aucun séjour en cours.\n");
    } else {
        printf("\nTotal : %d séjour(s) en cours\n", compteur);
    }

    pause();
}

/**
 * F18 : Identifie les emplacements sous-utilisés
 */
void identifierEmplacementsSousUtilises() {
    clearScreen();
    printf("\n========== EMPLACEMENTS SOUS-UTILISÉS ==========\n");

    // Compter le nombre de séjours par emplacement
    FILE *fEmp = fopen(FICHIER_EMPLACEMENTS, "rb");
    FILE *fSej = fopen(FICHIER_SEJOURS, "rb");

    if (fEmp == NULL || fSej == NULL) {
        printf("Erreur d'accès aux fichiers.\n");
        pause();
        return;
    }

    Emplacement emp;

    printf("%-10s %-15s %-15s %s\n", "Num", "Type", "Nb séjours", "Statut");
    printf("-------------------------------------------------------\n");

    while (fread(&emp, sizeof(Emplacement), 1, fEmp) == 1) {
        if (!emp.actif) continue;

        // Compter les séjours pour cet emplacement
        int nbSejours = 0;
        Sejour sej;

        fseek(fSej, 0, SEEK_SET);

        while (fread(&sej, sizeof(Sejour), 1, fSej) == 1) {
            if (sej.actif && sej.numEmplacement == emp.numEmplacement) {
                nbSejours++;
            }
        }

        // Afficher si sous-utilisé (critère simple : nombre de séjours)
        if (nbSejours < 3) { // Seuil arbitraire
            printf("%-10d %-15s %-15d %s\n",
                   emp.numEmplacement,
                   emp.codeType,
                   nbSejours,
                   "Sous-utilisé");
        }
    }

    fclose(fEmp);
    fclose(fSej);

    pause();
}

