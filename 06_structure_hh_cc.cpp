// ==============================================================================
// COURS 06 : LES FICHIERS .HH ET .CC — LA STRUCTURE D'UN PROJET GEANT4
// ==============================================================================
// Source d'inspiration : LearnCpp.com - Chapitres 2 et 8
//
// Dans les cours précédents, tout était dans UN seul fichier .cpp.
// En réalité, Geant4 utilise des DIZAINES de fichiers séparés.
// Ce cours explique comment un vrai projet C++ (et Geant4) est organisé.
// ==============================================================================
//
// STRUCTURE D'UN VRAI PROJET GEANT4 :
//
//  MonProjetGeant4/
//  ├── CMakeLists.txt          (Le fichier de configuration pour compiler)
//  ├── main.cc                 (Le point d'entrée du programme)
//  ├── include/                (Dossier pour les fichiers .hh = les PLANS)
//  │   ├── MyDetectorConstruction.hh
//  │   ├── MyPhysicsList.hh
//  │   └── MyPrimaryGenerator.hh
//  └── src/                    (Dossier pour les fichiers .cc = le CODE)
//      ├── MyDetectorConstruction.cc
//      ├── MyPhysicsList.cc
//      └── MyPrimaryGenerator.cc
//
// Chaque "module" (ex: le Détecteur) est donc séparé en DEUX fichiers :
//   - Un fichier .hh (Header) dans include/ : le PLAN, les DÉCLARATIONS
//   - Un fichier .cc dans src/             : le CODE, les DÉFINITIONS
//
// ==============================================================================

#include <iostream>
#include <string>


// ==============================================================================
// PARTIE 1 : LE FICHIER .hh (Header / En-tête)
// ==============================================================================
// Dans un vrai projet, ceci serait dans : include/MyDetectorConstruction.hh
//
// Le RÔLE du fichier .hh :
//   - DÉCLARER l'existence d'une classe (son "contrat" ou son "menu")
//   - Lister les attributs et les méthodes, mais sans écrire le code dedans
//   - C'est la "TABLE DES MATIÈRES" du fichier .cc correspondant
//   - Il est inclus (#include) par tous les fichiers qui ont besoin d'utiliser
//     cette classe, sans avoir à recopier le code entier.
//
// LES GARDE-FOUS (#ifndef / #define / #endif) :
//   Imaginez que 10 fichiers différents incluent le même .hh.
//   Sans protection, la classe serait déclarée 10 fois -> ERREUR de compilation.
//   Les "include guards" assurent que le fichier n'est inclus QU'UNE SEULE FOIS.

// Début du "garde-fou" (Include Guard)
// Convention : nom du fichier en MAJUSCULES avec les points remplacés par _
#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

// --- Ce serait le contenu du fichier .hh ---

// Inclusion des headers Geant4 nécessaires
// (Dans un vrai projet, ces lignes referencent les vrais fichiers de Geant4)
// #include "G4VUserDetectorConstruction.hh"
// #include "G4Box.hh"

class MyDetectorConstruction {
    // On utilise "G4VUserDetectorConstruction" comme parent dans un vrai projet
    // class MyDetectorConstruction : public G4VUserDetectorConstruction {

public:
    // Déclaration du constructeur (le PLAN, pas le code)
    MyDetectorConstruction();
    
    // Déclaration du destructeur
    ~MyDetectorConstruction();

    // Déclaration de la méthode principale - le code sera dans le .cc
    // "virtual" et "override" signalent que c'est une redéfinition d'une méthode parent
    // virtual G4VPhysicalVolume* Construct() override; // version Geant4 réelle
    void Construct(); // Version simplifiée pour ce cours

private:
    // Déclaration des attributs (les données que l'objet possèdera)
    // Le code d'initialisation sera dans le constructeur du .cc
    std::string m_worldMaterial;
    std::string m_detectorMaterial;
    double m_worldSize;
};

// Fin du garde-fou
#endif // MYDETECTORCONSTRUCTION_HH


// ==============================================================================
// PARTIE 2 : LE FICHIER .cc (Source / Corps)
// ==============================================================================
// Dans un vrai projet, ceci serait dans : src/MyDetectorConstruction.cc
//
// Le RÔLE du fichier .cc :
//   - DÉFINIR le code réel de chaque méthode déclarée dans le .hh
//   - Il commence toujours par inclure son propre .hh
//   - C'est ici qu'on écrit la vraie logique du programme

// Première chose à faire dans un .cc : inclure son propre .hh
// #include "MyDetectorConstruction.hh"
// #include "G4NistManager.hh"   // Pour accéder au catalogue de matériaux
// #include "G4Box.hh"           // Pour créer des boîtes
// #include <iostream>           // Déjà inclus en haut de CE fichier de cours

// --- Définition du Constructeur ---
// Syntaxe : NomDeLaClasse::NomDeLaMethode()
// Le double "::" s'appelle l'OPÉRATEUR DE PORTÉE (scope operator)
// Il dit : "La méthode NomDeLaMethode appartient à la classe NomDeLaClasse"
MyDetectorConstruction::MyDetectorConstruction() {
    // Initialisation des attributs
    m_worldMaterial = "G4_AIR";
    m_detectorMaterial = "G4_WATER";
    m_worldSize = 100.0; // 100 cm

    std::cout << "[MyDetectorConstruction] Constructeur appele." << std::endl;
    std::cout << "   Monde     : " << m_worldMaterial << std::endl;
    std::cout << "   Detecteur : " << m_detectorMaterial << std::endl;
}

// --- Définition du Destructeur ---
MyDetectorConstruction::~MyDetectorConstruction() {
    std::cout << "[MyDetectorConstruction] Destructeur appele." << std::endl;
}

// --- Définition de la méthode Construct() ---
void MyDetectorConstruction::Construct() {
    std::cout << "[MyDetectorConstruction] Construct() appelee !" << std::endl;
    std::cout << "  -> Construction du monde en " << m_worldMaterial << std::endl;
    std::cout << "  -> Placement du detecteur en " << m_detectorMaterial << std::endl;
    std::cout << "  -> Taille du monde : " << m_worldSize << " cm" << std::endl;
}


// ==============================================================================
// PARTIE 3 : L'OPÉRATEUR DE PORTÉE "::" ET LES NAMESPACES
// ==============================================================================
// L'opérateur :: a deux usages importants :
//
// 1. Lier une méthode à sa classe (comme vu ci-dessus)
//    -> MyDetectorConstruction::Construct()
//
// 2. Les NAMESPACES (espaces de noms) :
//    Un namespace est un "groupe de noms" pour éviter les conflits.
//    Exemple : "std::cout" signifie "le cout qui est DANS le groupe std"
//    Geant4 aurait pu mettre G4Box dans un namespace "Geant4::"
//    mais par convention, il préfère le préfixe "G4"

// Déclaration d'un namespace
namespace MonExperience {
    // Tout ce qui est ici appartient au namespace "MonExperience"
    
    int nombreDePasses = 5;
    
    void afficherConfig() {
        std::cout << "Experience :: Nombre de passes : " << nombreDePasses << std::endl;
    }
}

// Dans Geant4, vous verrez souvent "using namespace std;" en haut des fichiers
// Cela permet d'écrire "cout" au lieu de "std::cout".
// ATTENTION : C'est une mauvaise pratique dans les fichiers .hh car ça "pollue"
// le namespace global. Mais dans les fichiers .cc c'est toléré.


// ==============================================================================
// PARTIE 4 : LE PRÉPROCESSEUR ET LES DIRECTIVES #
// ==============================================================================
// Les lignes qui commencent par # sont des instructions pour le PRÉPROCESSEUR.
// Le préprocesseur est un programme qui modifie le texte de votre code AVANT
// que le compilateur le lise.
//
// Directives importantes :
//   #include  -> Copie-colle le contenu d'un autre fichier ici
//   #define   -> Crée un alias de texte (une substitution globale)
//   #ifndef   -> "If Not Defined" (si pas encore défini) - pour les garde-fous
//   #endif    -> Marque la fin d'un bloc #if / #ifndef
//   #pragma once -> Une alternative moderne aux garde-fous (plus simple)

// Exemple de #define : (Geant4 les utilise pour les unités physiques)
#define MeV 1.0      // 1 MeV est l'unité de base
#define GeV 1000.0   // 1 GeV = 1000 MeV
#define keV 0.001    // 1 keV = 0.001 MeV

void demontrerDefine() {
    double energieProton = 938.3 * MeV; // Le préprocesseur remplace MeV par 1.0
    double energieFaisceau = 7.0 * GeV; // Remplace GeV par 1000.0
    
    std::cout << "\n=== DEMO #define UNITES ===" << std::endl;
    std::cout << "Energie proton : " << energieProton << " MeV" << std::endl;
    std::cout << "Energie faisceau LHC : " << energieFaisceau << " MeV" << std::endl;
}


// ==============================================================================
// RÉSUMÉ : LIRE UN VRAI FICHIER GEANT4
// ==============================================================================
// Quand vous ouvrez MyDetectorConstruction.hh dans Geant4, vous verrez :
//
//   #ifndef MyDetectorConstruction_h    <- Garde-fou (début)
//   #define MyDetectorConstruction_h
//
//   #include "G4VUserDetectorConstruction.hh"  <- Inclusion du parent
//
//   class MyDetectorConstruction : public G4VUserDetectorConstruction {
//   public:
//     MyDetectorConstruction();          <- Déclaration du constructeur
//     virtual ~MyDetectorConstruction(); <- Déclaration du destructeur
//     virtual G4VPhysicalVolume* Construct() override; <- Déclaration méthode
//   
//   private:
//     G4Box* fSolidWorld;               <- Attribut privé
//     G4Material* fWorldMaterial;       <- Attribut privé
//   };
//
//   #endif // MyDetectorConstruction_h  <- Garde-fou (fin)
//
// Maintenant vous pouvez lire ça ! C'est simplement :
//   - Un garde-fou
//   - Une classe enfant qui hérite d'une classe Geant4
//   - Des déclarations de méthodes (sans le code)
//   - Des attributs privés
// ==============================================================================


int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 06 : STRUCTURE .HH / .CC         " << std::endl;
    std::cout << "==========================================" << std::endl;

    // Test de la classe MyDetectorConstruction
    std::cout << "\n--- TEST MyDetectorConstruction ---" << std::endl;
    MyDetectorConstruction* det = new MyDetectorConstruction();
    det->Construct();
    delete det;

    // Test du namespace
    std::cout << "\n--- TEST NAMESPACE ---" << std::endl;
    MonExperience::afficherConfig();
    std::cout << "Valeur directe : " << MonExperience::nombreDePasses << std::endl;

    // Test des defines
    demontrerDefine();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FIN DU COURS - VOUS MAÎTRISEZ LA STRUCTURE DE PROJET !" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
