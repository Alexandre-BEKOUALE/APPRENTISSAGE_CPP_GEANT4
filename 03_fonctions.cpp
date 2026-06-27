// ==============================================================================
// COURS 03 : LES FONCTIONS
// ==============================================================================
// Source : LearnCpp.com - Chapitres 2 et 12
//
// Une fonction est un bloc de code réutilisable qui porte un nom.
// Dans Geant4, TOUT est organisé en fonctions :
//   SetParticleEnergy(), Construct(), BeamOn(), Initialize()...
// Ce cours vous apprend à les créer et les comprendre.
// ==============================================================================

#include <iostream>
#include <string>
#include <cmath> // Pour sqrt(), pow(), sin(), cos()

// ==============================================================================
// PARTIE 1 : ANATOMIE D'UNE FONCTION
// ==============================================================================
// ANALOGIE : Une recette de cuisine.
//   - Nom de la recette    = Nom de la fonction
//   - Ingrédients          = Paramètres (les entrées)
//   - Ce qu'elle produit   = Le type de retour (la sortie)
//   - Les étapes           = Le code dans le corps { }

// --- Syntaxe générale ---
// typeDeRetour nomDeLaFonction(typeParam1 nomParam1, typeParam2 nomParam2) {
//     // corps de la fonction
//     return valeurDuBonType;
// }

// EXEMPLE 1 : Fonction qui retourne un double
// "Donne-moi une énergie en joules, je te retourne en MeV"
double jouleVersMMeV(double energieJoule) {
    // 1 MeV = 1.602 × 10^-13 Joule
    double energieMeV = energieJoule / 1.602e-13;
    return energieMeV; // "return" envoie le résultat à celui qui a appelé la fonction
}

// EXEMPLE 2 : Fonction void (elle fait une action mais ne retourne rien)
// "void" = "vide" = rien à retourner
void afficherParticule(std::string nom, double charge, double masse_MeV) {
    std::cout << "--- Particule ---" << std::endl;
    std::cout << "  Nom    : " << nom << std::endl;
    std::cout << "  Charge : " << charge << " e" << std::endl;
    std::cout << "  Masse  : " << masse_MeV << " MeV/c2" << std::endl;
}

// EXEMPLE 3 : Fonction avec valeur de retour booléenne
bool estDansVolume(double x, double y, double z, double taille) {
    // Vérifie si le point (x,y,z) est dans un cube centré en (0,0,0)
    if (x >= -taille && x <= taille &&
        y >= -taille && y <= taille &&
        z >= -taille && z <= taille) {
        return true;  // La particule EST dans le volume
    }
    return false; // La particule n'est PAS dans le volume
}

void coursAnatomie() {
    std::cout << "\n=== COURS : ANATOMIE D'UNE FONCTION ===" << std::endl;

    // Appel des fonctions
    double energie_J = 2.5e-12; // 2.5 pico-joules
    double energie_MeV = jouleVersMMeV(energie_J);
    std::cout << energie_J << " J = " << energie_MeV << " MeV" << std::endl;

    afficherParticule("Proton", +1.0, 938.272);
    afficherParticule("Electron", -1.0, 0.511);
    afficherParticule("Neutron", 0.0, 939.565);

    bool resultat = estDansVolume(5.0, 3.0, 8.0, 10.0);
    std::cout << "Point (5,3,8) dans cube 20cm ? " << (resultat ? "OUI" : "NON") << std::endl;
}


// ==============================================================================
// PARTIE 2 : LES PROTOTYPES DE FONCTIONS (Déclaration avant Définition)
// ==============================================================================
// En C++, vous devez DÉCLARER une fonction AVANT de l'utiliser.
// Sinon le compilateur ne la connaît pas encore quand il lit l'appel.
//
// Solution 1 : Définir la fonction AVANT le main() (ce qu'on fait dans ce cours)
// Solution 2 : Écrire juste le "prototype" (la signature) avant le main(),
//              et mettre le code complet après.
//
// Syntaxe du prototype : typeRetour nomFonction(typeParam1, typeParam2);
//                        (On peut omettre les noms des paramètres)

// PROTOTYPE (déclaration)
double calculerPicBragg(double energieMeV, double masseMeV);

// Le CODE complet de la fonction peut être écrit bien plus loin dans le fichier
double calculerPicBragg(double energieMeV, double masseMeV) {
    // Formule simplifiée pour la profondeur du pic de Bragg (Bethe-Bloch simplifiée)
    // profondeur ≈ E^1.77 / (1000 * masse)   (en cm, approximation)
    double profondeur = pow(energieMeV, 1.77) / (1000.0 * masseMeV / 938.0);
    return profondeur;
}

void coursPrototypes() {
    std::cout << "\n=== COURS : PROTOTYPES ===" << std::endl;

    // On peut appeler calculerPicBragg() ici grâce au prototype déclaré plus haut
    double prof_proton  = calculerPicBragg(200.0, 938.272);
    double prof_carbone = calculerPicBragg(4200.0, 11178.0); // 12C à 350 MeV/u

    std::cout << "Pic de Bragg (proton 200 MeV)   : " << prof_proton << " cm" << std::endl;
    std::cout << "Pic de Bragg (carbone 4200 MeV) : " << prof_carbone << " cm" << std::endl;
}


// ==============================================================================
// PARTIE 3 : PASSAGE PAR VALEUR vs PAR RÉFÉRENCE (& — CRUCIAL pour Geant4)
// ==============================================================================
//
// Quand on appelle une fonction avec une variable, il y a deux façons :
//
// PAR VALEUR   : La fonction reçoit une COPIE. L'original n'est pas modifié.
//   -> Sûr mais lent si l'objet est grand (on copie tout).
//
// PAR RÉFÉRENCE (avec &) : La fonction reçoit l'ORIGINAL.
//   -> Plus rapide (pas de copie) et peut modifier l'original.
//   -> Pour protéger l'original sans le copier, on ajoute "const" devant.

// Passage PAR VALEUR (copie)
void doublerParValeur(double energie) {
    energie = energie * 2; // On modifie la COPIE, pas l'original
    std::cout << "  [ParValeur] valeur locale : " << energie << std::endl;
}

// Passage PAR RÉFÉRENCE (l'original peut être modifié)
void doublerParReference(double& energie) {
    // Le & dans le TYPE signifie "référence" (alias vers l'original)
    energie = energie * 2; // On modifie DIRECTEMENT l'original !
    std::cout << "  [ParRef] valeur modifiee : " << energie << std::endl;
}

// Passage PAR RÉFÉRENCE CONSTANTE (lecture seule, sans copie)
// Très utilisé dans Geant4 pour passer des objets lourds en lecture seule
void afficherEnergie(const double& energie) {
    // const& = "je veux lire l'original sans le copier, et je promets de ne pas le modifier"
    std::cout << "  [ConstRef] Energie = " << energie << " MeV" << std::endl;
    // energie = 999; // INTERDIT par "const" -> le compilateur refuserait !
}

void coursPassage() {
    std::cout << "\n=== COURS : PASSAGE PAR VALEUR vs REFERENCE ===" << std::endl;

    double monEnergie = 50.0;
    std::cout << "Avant tout appel : " << monEnergie << " MeV" << std::endl;

    doublerParValeur(monEnergie);
    std::cout << "Apres parValeur  : " << monEnergie << " MeV (INCHANGE)" << std::endl;

    doublerParReference(monEnergie);
    std::cout << "Apres parRef     : " << monEnergie << " MeV (MODIFIE !)" << std::endl;

    afficherEnergie(monEnergie);

    // Lien Geant4 : Les méthodes Geant4 utilisent const& partout :
    // void UserSteppingAction(const G4Step* aStep)
    // const G4String& GetParticleName() const
}


// ==============================================================================
// PARTIE 4 : SURCHARGE DE FONCTIONS (Overloading)
// ==============================================================================
// Même nom de fonction, paramètres différents.
// Le compilateur choisit automatiquement la bonne version selon les arguments.
// Dans Geant4, c'est utilisé par exemple pour SetParticlePosition()
// qui peut accepter un G4ThreeVector ou 3 doubles séparés.

void afficherInfos(std::string nomParticule) {
    std::cout << "[version 1] Particule : " << nomParticule << std::endl;
}

void afficherInfos(std::string nomParticule, double energieMeV) {
    std::cout << "[version 2] Particule : " << nomParticule
              << " | Energie : " << energieMeV << " MeV" << std::endl;
}

void afficherInfos(std::string nomParticule, double energieMeV, int charge) {
    std::cout << "[version 3] Particule : " << nomParticule
              << " | Energie : " << energieMeV << " MeV"
              << " | Charge : " << charge << std::endl;
}

void coursSurcharge() {
    std::cout << "\n=== COURS : SURCHARGE DE FONCTIONS ===" << std::endl;
    // Le compilateur choisit la bonne version selon les arguments
    afficherInfos("Gamma");
    afficherInfos("Proton", 160.0);
    afficherInfos("Alpha", 5600.0, +2);
}


// ==============================================================================
// PARTIE 5 : FONCTIONS RÉCURSIVES (Une fonction qui s'appelle elle-même)
// ==============================================================================
// Utile pour des calculs en cascade. Exemple : la factorielle.

long long factorielle(int n) {
    // CAS DE BASE (condition d'arrêt - OBLIGATOIRE sinon boucle infinie !)
    if (n <= 1) {
        return 1;
    }
    // CAS RÉCURSIF : La fonction s'appelle elle-même avec n-1
    return n * factorielle(n - 1);
    // factorielle(5) = 5 * factorielle(4)
    //                = 5 * 4 * factorielle(3)
    //                = 5 * 4 * 3 * factorielle(2)
    //                = 5 * 4 * 3 * 2 * factorielle(1)
    //                = 5 * 4 * 3 * 2 * 1 = 120
}

void coursRecursivite() {
    std::cout << "\n=== COURS : RÉCURSIVITÉ ===" << std::endl;
    for (int i = 1; i <= 8; i++) {
        std::cout << i << "! = " << factorielle(i) << std::endl;
    }
}


// ==============================================================================
// RÉSUMÉ LIEN GEANT4
// ==============================================================================
// Dans Geant4, vous allez créer et appeler des fonctions tout le temps.
// Les plus importantes que vous écrirez :
//
// Dans MyDetectorConstruction.cc :
//   G4VPhysicalVolume* MyDetectorConstruction::Construct() { ... }
//   -> Type de retour : G4VPhysicalVolume* (un pointeur)
//   -> Pas de paramètre
//   -> Elle construit et retourne le volume principal du monde
//
// Dans MyPrimaryGeneratorAction.cc :
//   void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) { ... }
//   -> Type de retour : void (elle ne retourne rien)
//   -> Paramètre : G4Event* (un pointeur vers l'événement en cours)
//   -> Elle tire les particules dans cet événement
//
// Dans MySteppingAction.cc :
//   void MySteppingAction::UserSteppingAction(const G4Step* aStep) { ... }
//   -> Type de retour : void
//   -> Paramètre : const G4Step* (un pointeur constant = lecture seule)
//   -> Elle est appelée à CHAQUE PAS de chaque particule !
// ==============================================================================

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 03 : LES FONCTIONS               " << std::endl;
    std::cout << "==========================================" << std::endl;

    coursAnatomie();
    coursPrototypes();
    coursPassage();
    coursSurcharge();
    coursRecursivite();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FIN DU COURS 03 !" << std::endl;
    std::cout << "  Prochain : 04_pointeurs_et_memoire.cpp (LE PLUS IMPORTANT)" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
