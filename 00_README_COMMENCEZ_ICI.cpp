// ==============================================================================
// README.cpp — GUIDE DE NAVIGATION DE VOTRE COURS C++ POUR GEANT4
// ==============================================================================
// Lisez ce fichier EN PREMIER avant de commencer les cours.
// Il vous explique comment utiliser ces fichiers et dans quel ordre les lire.
// ==============================================================================

// COMMENT TESTER UN FICHIER SUR ONLINEGDB.COM :
// -----------------------------------------------
// 1. Allez sur https://www.onlinegdb.com/online_c++_compiler
// 2. Copiez-collez le contenu d'un fichier .cpp dans la zone de texte
// 3. Cliquez sur le bouton vert "Run"
// 4. Observez le résultat en bas dans la zone "Output"
// 5. Modifiez une valeur et observez comment le résultat change
// Ce test "Modifier/Observer" est la MEILLEURE façon d'apprendre !

// ORDRE DE LECTURE RECOMMANDÉ :
// -----------------------------------------------
// [PHASE 1 - LES BASES ABSOLUES]
//   01_variables_et_types.cpp     -> Les données (int, double, string...)
//   02_conditions_et_boucles.cpp  -> La logique (if, for, while...)
//   03_fonctions.cpp              -> Les blocs de code réutilisables
//
// [PHASE 2 - LA MÉMOIRE (COEUR DE GEANT4)]
//   04_pointeurs_et_memoire.cpp   -> *, new, delete, ->  (LE PLUS IMPORTANT)
//
// [PHASE 3 - PROGRAMMATION ORIENTÉE OBJET]
//   05_classes_et_heritage.cpp    -> class, public, private, virtual, override
//   06_structure_hh_cc.cpp        -> Comment un vrai projet est organisé
//
// [PHASE 4 - OUTILS SPÉCIFIQUES GEANT4]
//   07_specifique_geant4.cpp      -> vector, enum, maths, références

// PROGRESSION SUGGÉRÉE PAR SEMAINE :
// -----------------------------------------------
// Semaine 1 : Fichiers 01, 02, 03 (les bases solides)
// Semaine 2 : Fichier 04 (les pointeurs, relisez-le plusieurs fois !)
// Semaine 3 : Fichiers 05, 06 (la POO)
// Semaine 4 : Fichier 07 + Lancer l'Exemple B1 de Geant4

// EXERCICES SUGGÉRÉS APRÈS CHAQUE COURS :
// -----------------------------------------------
// Après 01 : Créer des variables pour une particule (nom, énergie, charge)
//            et les afficher.
//
// Après 02 : Écrire une boucle qui affiche "Particule N déposée X MeV"
//            pour 100 particules avec une énergie aléatoire.
//
// Après 03 : Créer une fonction calculerPicBragg(double energie, double longueur)
//            qui retourne la profondeur du pic.
//
// Après 04 : Créer un pointeur vers un double, modifier sa valeur via le pointeur,
//            puis libérer la mémoire. Vérifier qu'aucune fuite mémoire n'a lieu.
//
// Après 05 : Créer une classe "Particule" avec nom, énergie, charge comme attributs,
//            un constructeur, et une méthode afficher().
//            Puis créer une classe "Photon" qui hérite de "Particule".
//
// Après 06 : Réorganiser votre classe "Particule" en deux fichiers séparés :
//            Particule.hh et Particule.cc
//
// Après 07 : Créer un std::vector de 10 "Particule*" et les afficher en boucle.

// RESSOURCES COMPLÉMENTAIRES :
// -----------------------------------------------
// - LearnCpp.com         : Le site de référence (en anglais)
// - OnlineGDB.com        : Pour tester sans installer de compilateur
// - cppreference.com     : La documentation technique complète
// - forum.geant4.org     : Le forum officiel de Geant4 pour les questions

#include <iostream>
int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  GUIDE DES COURS C++ POUR GEANT4        " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "  Fichier 01 : Variables et Types         " << std::endl;
    std::cout << "  Fichier 02 : Conditions et Boucles      " << std::endl;
    std::cout << "  Fichier 03 : Fonctions                  " << std::endl;
    std::cout << "  Fichier 04 : Pointeurs et Memoire [!]   " << std::endl;
    std::cout << "  Fichier 05 : Classes et Heritage        " << std::endl;
    std::cout << "  Fichier 06 : Structure .hh / .cc        " << std::endl;
    std::cout << "  Fichier 07 : C++ Specifique Geant4      " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "  Commencez par le fichier 01 !           " << std::endl;
    return 0;
}
