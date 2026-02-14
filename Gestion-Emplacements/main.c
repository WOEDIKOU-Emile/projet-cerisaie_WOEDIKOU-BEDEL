#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "types.h"
#include "emplacements.h"
#include "sejours.h"

/**
 * Affiche le menu principal
 */
void afficherMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║         CAMPING LA CERISAIE - GESTION EMPLACEMENTS        ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("│  GESTION DES TYPES ET TARIFS                               │\n");
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│  1.  Consulter les tarifs                                 │\n");
    printf("│  2.  Créer un type d'emplacement                          │\n");
    printf("│  3.  Modifier un tarif                                    │\n");
    printf("└────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("│  GESTION DES EMPLACEMENTS                                  │\n");
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│  4.  Créer un emplacement                                 │\n");
    printf("│  5.  Modifier un emplacement                              │\n");
    printf("│  6.  Supprimer un emplacement                             │\n");
    printf("│  7.  Changer le statut d'un emplacement                   │\n");
    printf("│  8.  Consulter les emplacements disponibles               │\n");
    printf("│  9.  Consulter les emplacements par type                  │\n");
    printf("│  10. Consulter le détail d'un emplacement                 │\n");
    printf("│  11. Visualiser le taux d'occupation                      │\n");
    printf("│  12. Identifier les emplacements sous-utilisés            │\n");
    printf("└────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("│  GESTION DES SÉJOURS                                       │\n");
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("│  13. Attribuer un emplacement (nouveau séjour)            │\n");
    printf("│  14. Libérer un emplacement (fin de séjour)               │\n");
    printf("│  15. Changer l'emplacement d'un séjour                    │\n");
    printf("│  16. Consulter les séjours en cours                       │\n");
    printf("└────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("│  0.  QUITTER (sauvegarde automatique)                     │\n");
    printf("└────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}

/**
 * Fonction principale
 */
int main() {
    int choix;

    // Initialisation au démarrage
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║    CAMPING LA CERISAIE - Système de gestion v1.0          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Initialisation du système...\n");
    printf("─────────────────────────────────────────────────────────────\n");

    // Charger les types en mémoire
    chargerTypes();

    // Initialiser les fichiers random
    initialiserFichierEmplacements();
    initialiserFichierSejours();

    printf("─────────────────────────────────────────────────────────────\n");
    printf("Système prêt !\n");
    pause();

    // Boucle principale
    do {
        clearScreen();
        afficherMenu();

        choix = saisirEntier("Votre choix : ");

        switch (choix) {
            /* GESTION DES TYPES ET TARIFS */
            case 1:
                consulterTarifs();
                break;

            case 2:
                creerType();
                break;

            case 3:
                modifierTarifType();
                break;

            /* GESTION DES EMPLACEMENTS */
            case 4:
                creerEmplacement();
                break;

            case 5:
                modifierEmplacement();
                break;

            case 6:
                supprimerEmplacement();
                break;

            case 7:
                changerStatutEmplacement();
                break;

            case 8:
                consulterEmplacementsDisponibles();
                break;

            case 9:
                consulterEmplacementsParType();
                break;

            case 10:
                consulterDetailEmplacement();
                break;

            case 11:
                visualiserTauxOccupation();
                break;

            case 12:
                identifierEmplacementsSousUtilises();
                break;

            /* GESTION DES SÉJOURS */
            case 13:
                attribuerEmplacement();
                break;

            case 14:
                libererEmplacement();
                break;

            case 15:
                changerEmplacementSejour();
                break;

            case 16:
                consulterSejourEnCours();
                break;

            /* QUITTER */
            case 0:
                clearScreen();
                printf("\n");
                printf("╔════════════════════════════════════════════════════════════╗\n");
                printf("║                    FERMETURE DU SYSTÈME                    ║\n");
                printf("╚════════════════════════════════════════════════════════════╝\n");
                printf("\n");
                printf("Sauvegarde des données...\n");
                printf("─────────────────────────────────────────────────────────────\n");

                // Sauvegarder les types avant de quitter
                sauvegarderTypes();

                printf("─────────────────────────────────────────────────────────────\n");
                printf("\n✓ Au revoir !\n\n");
                break;

            default:
                printf("\nChoix invalide. Veuillez réessayer.\n");
                pause();
                break;
        }

    } while (choix != 0);

    return 0;
}
