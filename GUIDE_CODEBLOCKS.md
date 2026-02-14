# 🎯 GUIDE CODE::BLOCKS - Camping La Cerisaie

## 🚀 MÉTHODE RAPIDE (Recommandée)

### Utiliser le fichier projet fourni

1. **Ouvrir Code::Blocks**

2. **File → Open → `Camping_Cerisaie.cbp`**

3. **Build → Rebuild**

4. **Build → Run**

✅ **C'est tout !** Le projet est déjà configuré avec tous les fichiers.

---

## 📋 MÉTHODE MANUELLE (Si nécessaire)

### Étape 1 : Créer un nouveau projet

1. **File → New → Project**
2. Choisir **Console application**
3. Cliquer **Go**
4. Sélectionner **C** (pas C++)
5. Donner un nom : `Camping_Cerisaie`
6. Choisir le dossier où sont vos fichiers
7. **Finish**

### Étape 2 : SUPPRIMER le main.c par défaut

Code::Blocks crée un `main.c` par défaut. Il faut le supprimer :

1. Dans le panneau de gauche (Management)
2. **Clic droit sur `main.c`** (celui créé automatiquement)
3. **Remove file from project**

### Étape 3 : Ajouter TOUS les fichiers .c

**C'est l'étape CRUCIALE !**

1. **Clic droit sur le nom du projet** (dans Management)
2. **Add files...**
3. **Sélectionner ces 5 fichiers** (maintenir CTRL pour sélection multiple) :
   - `main.c`
   - `utils.c`
   - `types.c`
   - `emplacements.c`
   - `sejours.c`
4. Cliquer **Open**
5. Cocher **Debug** et **Release**
6. Cliquer **OK**

### Étape 4 : Ajouter les fichiers .h (optionnel mais recommandé)

1. **Clic droit sur le projet**
2. **Add files...**
3. **Sélectionner tous les .h** :
   - `structures.h`
   - `utils.h`
   - `types.h`
   - `emplacements.h`
   - `sejours.h`
4. Cliquer **OK**

### Étape 5 : Configurer le compilateur

1. **Settings → Compiler**
2. Dans "Compiler settings → Compiler flags"
3. **Cocher** :
   - ☑ Enable all common compiler warnings [-Wall]
   - ☑ Have g++ follow the C++11 ISO C++ language standard

4. Dans "Compiler settings → Other compiler options", ajouter :
   ```
   -std=c99
   ```

### Étape 6 : Compiler

1. **Build → Rebuild**
2. Vérifier qu'il n'y a **aucune erreur**
3. **Build → Run**

---

## ❌ ERREUR : "undefined reference to..."

### Symptôme
```
undefined reference to 'chargerTypes'
undefined reference to 'initialiserFichierEmplacements'
undefined reference to 'pause'
```

### Cause
**Tous les fichiers .c ne sont pas ajoutés au projet !**

### ✅ Solution

#### Vérifier les fichiers du projet

1. Dans le panneau **Management** (à gauche)
2. Développer votre projet
3. Vous devez voir **TOUS ces fichiers** :

```
📁 Camping_Cerisaie
  📄 main.c
  📄 utils.c
  📄 types.c
  📄 emplacements.c
  📄 sejours.c
  📄 structures.h
  📄 utils.h
  📄 types.h
  📄 emplacements.h
  📄 sejours.h
```

#### S'il manque des fichiers

1. **Clic droit sur le projet**
2. **Add files...**
3. **Ajouter les fichiers manquants**
4. **Build → Rebuild**

---

## 🔍 DIAGNOSTIC

### Vérifier que Code::Blocks voit tous les fichiers

**Build → Build log**

Vous devriez voir quelque chose comme :
```
Compiling: main.c
Compiling: utils.c
Compiling: types.c
Compiling: emplacements.c
Compiling: sejours.c
Linking console executable: bin\Debug\camping.exe
```

Si vous ne voyez que :
```
Compiling: main.c
Linking console executable: bin\Debug\camping.exe
```

➡️ **Les autres fichiers ne sont PAS dans le projet !**

---

## 🛠️ CONFIGURATION AVANCÉE

### Ordre de compilation (si nécessaire)

Si vous avez toujours des erreurs de dépendances circulaires :

1. **Project → Build options**
2. Onglet **"Pre/Post build steps"**
3. Dans **"Pre-build steps"**, ajouter :
   ```
   del /Q obj\Debug\*.o
   ```
   (Windows) ou
   ```
   rm -f obj/Debug/*.o
   ```
   (Linux)

### Définir l'ordre des fichiers

1. **Project → Properties**
2. Onglet **"Build targets"**
3. Réorganiser les fichiers dans cet ordre :
   - utils.c
   - types.c
   - sejours.c
   - emplacements.c
   - main.c

---

## 📂 STRUCTURE DU PROJET

Votre dossier doit contenir :

```
camping_modulaire_v2/
├── Camping_Cerisaie.cbp      ← Fichier projet Code::Blocks
├── main.c
├── utils.c
├── utils.h
├── types.c
├── types.h
├── emplacements.c
├── emplacements.h
├── sejours.c
├── sejours.h
├── structures.h
├── Makefile
└── README.md
```

---

## 🎯 CHECKLIST RAPIDE

Avant de compiler, vérifier :

- [ ] Tous les 5 fichiers `.c` sont dans le projet
- [ ] Tous les 5 fichiers `.h` sont dans le projet
- [ ] L'option `-std=c99` est activée
- [ ] Pas de fichier `main.c` en double
- [ ] Build → Clean a été exécuté
- [ ] Build → Rebuild (pas juste Build)

---

## 🐛 PROBLÈMES COURANTS

### Problème 1 : "Multiple definition of main"

**Cause** : Deux fichiers `main.c` dans le projet

**Solution** :
1. Management → Supprimer le main.c par défaut de Code::Blocks
2. Garder seulement votre main.c

### Problème 2 : "Permission denied"

**Cause** : L'exécutable est déjà en cours d'exécution

**Solution** :
1. Fermer la fenêtre console du programme
2. Build → Rebuild

### Problème 3 : "Cannot find -lgdi32" (Windows)

**Cause** : Mauvaise configuration du compilateur

**Solution** :
1. Settings → Compiler → Toolchain executables
2. Vérifier que le chemin vers MinGW est correct

### Problème 4 : Les fichiers .dat ne se créent pas

**Cause** : Problème de permissions ou mauvais répertoire

**Solution** :
1. Exécuter Code::Blocks en tant qu'administrateur
2. Ou changer le répertoire de sortie :
   - Project → Properties → Build targets
   - Execution working dir : `$(PROJECT_DIR)`

---

## 💡 ASTUCES

### Astuce 1 : Raccourcis clavier
- **F9** : Compile et exécute
- **Ctrl+F9** : Compile seulement
- **Ctrl+F10** : Exécute (sans compiler)
- **F11** : Debug

### Astuce 2 : Voir les warnings
Settings → Compiler → Compiler flags → Enable all warnings

### Astuce 3 : Fenêtre console qui se ferme
Settings → Environment → General settings → Cocher "Pause console programs after return"

### Astuce 4 : Coloration syntaxique
Settings → Editor → Syntax highlighting → Choisir un thème

---

## 🆘 SI ÇA NE MARCHE TOUJOURS PAS

### Option 1 : Compiler en ligne de commande

Ouvrir une console dans le dossier du projet :

**Windows (CMD) :**
```cmd
gcc -o camping.exe main.c utils.c types.c emplacements.c sejours.c
camping.exe
```

**Linux / Mac :**
```bash
gcc -o camping main.c utils.c types.c emplacements.c sejours.c
./camping
```

Si ça compile en ligne de commande mais pas dans Code::Blocks, c'est un problème de configuration de Code::Blocks.

### Option 2 : Utiliser le Makefile

Si vous avez MinGW avec make :

```cmd
mingw32-make
camping.exe
```

### Option 3 : Réinstaller Code::Blocks

Télécharger la version avec MinGW inclus :
**codeblocks-XX.XX-mingw-setup.exe**

---

## ✅ VÉRIFICATION FINALE

Après compilation réussie, dans le panneau "Build log", vous devriez voir :

```
-------------- Build: Debug in Camping_Cerisaie (compiler: GNU GCC Compiler)---------------

mingw32-gcc.exe -Wall -std=c99 -g -c main.c -o obj\Debug\main.o
mingw32-gcc.exe -Wall -std=c99 -g -c utils.c -o obj\Debug\utils.o
mingw32-gcc.exe -Wall -std=c99 -g -c types.c -o obj\Debug\types.o
mingw32-gcc.exe -Wall -std=c99 -g -c emplacements.c -o obj\Debug\emplacements.o
mingw32-gcc.exe -Wall -std=c99 -g -c sejours.c -o obj\Debug\sejours.o
mingw32-gcc.exe -o bin\Debug\camping.exe obj\Debug\main.o obj\Debug\utils.o obj\Debug\types.o obj\Debug\emplacements.o obj\Debug\sejours.o

Output file is bin\Debug\camping.exe with size 122.34 KB
Process terminated with status 0 (0 minute(s), 2 second(s))
0 error(s), 0 warning(s) (0 minute(s), 2 second(s))
```

---

**Si vous voyez toujours des erreurs, envoyez-moi une capture d'écran du panneau Management (avec la liste des fichiers du projet) !**
