#  CAMPING LA CERISAIE - Version Modulaire

##  Description

Implémentation en **programmation modulaire stricte** du système de gestion des emplacements pour le camping "La Cerisaie".

Cette version respecte les principes de la programmation modulaire avec :
- Séparation complète des fichiers `.h` (en-têtes) et `.c` (implémentation)
- Un fichier `main.c` séparé contenant uniquement le programme principal
- Chaque module avec son propre `.h` et `.c`
- Dépendances clairement définies

##  Architecture Modulaire

### Structure du projet

```
modulaire/
├── structures.h       # Définitions des structures de données
├── utils.h           # Prototypes des fonctions utilitaires
├── utils.c           # Implémentation des utilitaires
├── types.h           # Prototypes du module types
├── types.c           # Implémentation du module types
├── emplacements.h    # Prototypes du module emplacements
├── emplacements.c    # Implémentation du module emplacements
├── sejours.h         # Prototypes du module séjours
├── sejours.c         # Implémentation du module séjours
├── main.c            # Programme principal (SÉPARÉ)
└── Makefile          # Fichier de compilation
```

### Organisation des modules

####  Module STRUCTURES (structures.h)
**Responsabilité** : Définitions des types de données

Contient :
- Énumérations : `StatutEmplacement`, `StatutSejour`
- Structures : `Date`, `TypeEmplacement`, `Emplacement`, `Sejour`
- Constantes globales

**Dépendances** : Aucune

---

####  Module UTILS (utils.h + utils.c)
**Responsabilité** : Fonctions utilitaires génériques

Fonctions :
- Gestion de l'interface : `clearScreen()`, `pause()`, `afficherMenu()`
- Saisie validée : `saisirEntier()`, `saisirFloat()`, `saisirChaine()`
- Gestion des dates : `saisirDate()`, `dateValide()`, `comparerDates()`, `afficherDate()`
- Conversions : `statutEmplacementToString()`, `statutSejourToString()`

**Dépendances** : `structures.h`

---

####  Module TYPES (types.h + types.c)
**Responsabilité** : Gestion des types d'emplacements

Variables globales :
- `TypeEmplacement tabTypes[MAX_TYPES]` - Tableau en mémoire
- `int nbTypes` - Nombre de types chargés

Fonctions :
- `chargerTypes()` - Charge au démarrage (fichier → mémoire)
- `sauvegarderTypes()` - Sauvegarde à la fermeture (mémoire → fichier)
- `afficherTypes()` - Affiche tous les types actifs
- `rechercherType()` - Recherche par code
- `creerType()` - F13 : Créer un type
- `modifierTarifType()` - F14 : Modifier un tarif
- `consulterTarifs()` - F15 : Consulter les tarifs

**Dépendances** : `structures.h`, `utils.h`

---

####  Module EMPLACEMENTS (emplacements.h + emplacements.c)
**Responsabilité** : Gestion des emplacements (fichier random)

Fonctions bas niveau :
- `initialiserFichierEmplacements()`
- `lireEmplacement(position)`
- `ecrireEmplacement(emp, position)`
- `trouverProchainNumEmplacement()`
- `rechercherEmplacement(numEmplacement)`
- `afficherEmplacement(emp)`

Fonctionnalités métier :
- `creerEmplacement()` - F1
- `modifierEmplacement()` - F2
- `supprimerEmplacement()` - F3
- `changerStatutEmplacement()` - F4
- `consulterEmplacementsDisponibles()` - F5
- `consulterEmplacementsParType()` - F6
- `consulterDetailEmplacement()` - F7
- `visualiserTauxOccupation()` - F8

**Dépendances** : `structures.h`, `utils.h`, `types.h`, `sejours.h`

---

####  Module SEJOURS (sejours.h + sejours.c)
**Responsabilité** : Gestion des séjours (fichier random)

Fonctions bas niveau :
- `initialiserFichierSejours()`
- `lireSejour(position)`
- `ecrireSejour(sej, position)`
- `trouverProchainNumSejour()`
- `rechercherSejour(numSejour)`
- `afficherSejour(sej)`

Fonctionnalités métier :
- `attribuerEmplacement()` - F9
- `libererEmplacement()` - F10
- `verifierDisponibilite()` - F11
- `changerEmplacementSejour()` - F12
- `consulterSejourEnCours()`
- `detecterConflitReservation()` - F16
- `verifierCapacite()` - F17
- `identifierEmplacementsSousUtilises()` - F18

**Dépendances** : `structures.h`, `utils.h`, `emplacements.h`

---

####  Programme Principal (main.c)
**Responsabilité** : Point d'entrée et menu principal

Contient uniquement :
- Fonction `main()`
- Fonction `afficherMenu()`
- Boucle de gestion du menu
- Initialisation et fermeture du système

**Dépendances** : TOUS les modules

---

##  Graphe des dépendances

```
                    structures.h
                         ↑
        ┌────────────────┼────────────────┐
        │                │                │
     utils.h          types.h             │
        ↑                ↑                │
        │                │                │
        │                └────┐           │
        │                     │           │
   emplacements.h ←──────── sejours.h    │
        ↑                     ↑           │
        │                     │           │
        └──────────┬──────────┘           │
                   │                      │
                main.c ←──────────────────┘
```

##  Compilation et exécution

### Compilation simple
```bash
make
```

### Compilation et exécution
```bash
make run
```

### Recompilation complète
```bash
make rebuild
```

### Afficher la structure
```bash
make structure
```

### Nettoyage
```bash
make clean      # Supprime fichiers compilés
make cleanall   # Supprime tout
```

### Aide
```bash
make help
```

##  Avantages de cette architecture

### ✅ Modularité
- Chaque module a une responsabilité unique et bien définie
- Facile à comprendre et à maintenir
- Code réutilisable

### ✅ Compilation séparée
- Modification d'un module → recompilation uniquement de ce module
- Gain de temps sur les gros projets
- Détection précoce des erreurs

### ✅ Encapsulation
- Les `.h` exposent l'interface publique
- Les `.c` cachent l'implémentation
- Protection des données

### ✅ Dépendances claires
- Le Makefile gère automatiquement les dépendances
- Évite les inclusions circulaires
- Ordre de compilation garanti

### ✅ Testabilité
- Chaque module peut être testé indépendamment
- Facilite le débogage
- Permet les tests unitaires

### ✅ Travail en équipe
- Plusieurs développeurs peuvent travailler sur différents modules
- Moins de conflits
- Intégration facilitée

##  Fonctionnalités implémentées

**18 fonctionnalités complètes** réparties sur les modules :

### Module TYPES (3 fonctions)
- F13 : Créer un type d'emplacement
- F14 : Modifier un tarif
- F15 : Consulter les tarifs

### Module EMPLACEMENTS (8 fonctions)
- F1 : Créer un emplacement
- F2 : Modifier un emplacement
- F3 : Supprimer un emplacement
- F4 : Changer le statut
- F5 : Consulter disponibilités
- F6 : Consulter par type
- F7 : Détail d'un emplacement
- F8 : Taux d'occupation

### Module SEJOURS (7 fonctions)
- F9 : Attribuer un emplacement
- F10 : Libérer un emplacement
- F11 : Vérifier disponibilité
- F12 : Changer emplacement séjour
- F16 : Détecter conflits
- F17 : Vérifier capacité
- F18 : Emplacements sous-utilisés

##  Exemple d'utilisation d'un module

### Utiliser le module TYPES dans un autre fichier

```c
// Dans mon_fichier.c
#include "types.h"

void maFonction() {
    // Charger les types au démarrage
    chargerTypes();
    
    // Afficher les types
    afficherTypes();
    
    // Rechercher un type
    int index = rechercherType("CAR");
    if (index != -1) {
        printf("Type trouvé : %s\n", tabTypes[index].libelle);
    }
    
    // Sauvegarder à la fin
    sauvegarderTypes();
}
```

##  Ajouter un nouveau module

### Étape 1 : Créer le fichier .h
```c
// mon_module.h
#ifndef MON_MODULE_H
#define MON_MODULE_H

#include "structures.h"

// Prototypes des fonctions
void maFonction();

#endif
```

### Étape 2 : Créer le fichier .c
```c
// mon_module.c
#include "mon_module.h"

void maFonction() {
    // Implémentation
}
```

### Étape 3 : Ajouter au Makefile
```makefile
SOURCES = main.c utils.c types.c emplacements.c sejours.c mon_module.c
```

### Étape 4 : Inclure dans main.c
```c
#include "mon_module.h"
```

##  Ressources pédagogiques

Cette architecture illustre :
- **Séparation interface/implémentation** : `.h` vs `.c`
- **Compilation séparée** : Chaque `.c` compile indépendamment
- **Liaison** : Le linker assemble tous les `.o`
- **Protection d'inclusion** : `#ifndef`, `#define`, `#endif`
- **Variables globales** : `extern` dans `.h`, définition dans `.c`
- **Dépendances** : Gérées par le Makefile

##  Développeur

Projet développé dans le cadre de la méthode MERISE avec architecture modulaire stricte.

##  Licence

Projet éducatif - Usage pédagogique
