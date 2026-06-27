# 🚀 Apprentissage du C++ pour Geant4

Bienvenue dans mon parcours d'apprentissage du C++ orienté spécifiquement pour le développement de simulations Monte-Carlo avec **Geant4** !

Ce dépôt contient une série de cours et d'exemples pratiques en C++, structurés de manière progressive, depuis les bases absolues jusqu'aux concepts avancés indispensables pour Geant4.

## 📂 Contenu du cours

Le cours est divisé en plusieurs fichiers `.cpp` exécutables et commentés :

1. **[01_variables_et_types.cpp](01_variables_et_types.cpp)** : Les bases (int, double, string, const, cout).
2. **[02_conditions_et_boucles.cpp](02_conditions_et_boucles.cpp)** : La logique (if/else, switch, for, while, break).
3. **[03_fonctions.cpp](03_fonctions.cpp)** : Création de fonctions, `void`, `return`, et le passage par référence (`&`).
4. **[04_pointeurs_et_memoire.cpp](04_pointeurs_et_memoire.cpp)** : Gestion de la mémoire (`*`, `new`, `delete`, `->`, `nullptr`). **[CRUCIAL POUR GEANT4]**
5. **[05_classes_et_heritage.cpp](05_classes_et_heritage.cpp)** : Programmation Orientée Objet (`class`, `virtual`, `override`, héritage). **[CRUCIAL POUR GEANT4]**
6. **[06_structure_hh_cc.cpp](06_structure_hh_cc.cpp)** : Organisation d'un projet (`.hh`/`.cc`, `::`, `#include`).
7. **[07_specifique_geant4.cpp](07_specifique_geant4.cpp)** : Outils spécifiques (`vector`, `enum`, fonctions mathématiques).

> 💡 **Commencez par lire le fichier [00_README_COMMENCEZ_ICI.cpp](00_README_COMMENCEZ_ICI.cpp)** pour un guide de navigation détaillé.

## 🛠️ Comment utiliser ces fichiers

Ces fichiers sont conçus pour être lus et testés facilement.

### Option 1 : Test en ligne (Rapide et sans installation)
1. Ouvrez un fichier (par exemple `01_variables_et_types.cpp`).
2. Copiez tout le contenu.
3. Collez-le dans un compilateur en ligne comme **[OnlineGDB.com](https://www.onlinegdb.com/online_c++_compiler)**.
4. Cliquez sur **Run** et observez le résultat. Modifiez le code et testez à nouveau !

### Option 2 : Compilation locale (Recommandée pour ce cours)
Dans le cadre de cet apprentissage, j'utilise **Visual Studio Code (VS Code)** sur **Windows** avec les extensions suivantes :
- **C/C++** (pour l'autocomplétion et le débogage)
- **CMake Tools** (pour la gestion du build, essentiel pour Geant4)
- **WSL (Windows Subsystem for Linux)** (pour faire tourner l'environnement Linux indispensable à Geant4 directement sous Windows)

Avec cet environnement configuré, vous pouvez compiler les fichiers depuis le terminal WSL intégré à VS Code :
```bash
g++ -o variables 01_variables_et_types.cpp
./variables
```

## 🎯 Objectif
L'objectif final de cet apprentissage est d'acquérir les bases solides en C++ nécessaires pour comprendre, modifier et créer des applications **Geant4** (comme l'Exemple B1) en toute autonomie.
