// ==============================================================================
// COURS 07 : SPÉCIFIQUE GEANT4 — TOUT CE QUI VOUS SERA UTILE
// ==============================================================================
// Source : LearnCpp.com + Geant4 Book for Application Developers
//
// Ce fichier est le pont final entre le C++ pur et Geant4.
// On y voit les constructions C++ spécifiques que Geant4 utilise massivement.
// ==============================================================================

#include <iostream>
#include <string>
#include <vector>    // Les tableaux dynamiques (utilisés dans Geant4 pour les listes)
#include <cmath>     // Pour les fonctions mathématiques (sin, cos, sqrt, etc.)

// ==============================================================================
// PARTIE 1 : LES VECTEURS std::vector (Les tableaux dynamiques)
// ==============================================================================
// Dans Geant4, on manipule souvent des LISTES : liste de matériaux, de volumes,
// de particules secondaires, etc. On utilise pour ça std::vector.
// Un vector, c'est un tableau dont la taille peut changer pendant l'exécution.

void coursSurVector() {
    std::cout << "\n=== COURS : std::vector ===" << std::endl;

    // Déclaration : std::vector<TypeContenu> nomVariable;
    std::vector<double> energiesParticules; // Un tableau vide de doubles

    // Ajouter des éléments à la fin avec .push_back()
    energiesParticules.push_back(10.5);  // 1ère particule : 10.5 MeV
    energiesParticules.push_back(22.3);  // 2ème particule : 22.3 MeV
    energiesParticules.push_back(8.1);   // 3ème particule :  8.1 MeV
    energiesParticules.push_back(45.0);  // 4ème particule : 45.0 MeV

    // Taille du vector avec .size()
    std::cout << "Nombre de particules : " << energiesParticules.size() << std::endl;

    // Accéder à un élément avec [] (comme un tableau normal)
    // ATTENTION : Les indices commencent à 0 (pas à 1) !
    std::cout << "Energie de la 1ere particule : " << energiesParticules[0] << " MeV" << std::endl;
    std::cout << "Energie de la 3eme particule : " << energiesParticules[2] << " MeV" << std::endl;

    // Parcourir tout le vector avec une boucle for "range-based" (C++11)
    // C'est la syntaxe moderne, très utilisée dans Geant4 moderne
    std::cout << "Toutes les energies :" << std::endl;
    for (double energie : energiesParticules) {
        // Pour chaque 'energie' dans 'energiesParticules', exécuter ce bloc
        std::cout << "  -> " << energie << " MeV" << std::endl;
    }

    // Parcourir avec un indice classique (for classique)
    double somme = 0.0;
    for (int i = 0; i < energiesParticules.size(); i++) {
        somme += energiesParticules[i]; // += signifie "ajouter à soi-même"
    }
    std::cout << "Energie totale deposee : " << somme << " MeV" << std::endl;

    // Lien Geant4 : Quand une particule crée des secondaires, Geant4 utilise un
    // vector de pointeurs : std::vector<G4Track*> secondaires;
}


// ==============================================================================
// PARTIE 2 : LES ÉNUMÉRATIONS (enum class) — Les "codes" dans Geant4
// ==============================================================================
// Geant4 utilise des énumérations pour représenter des états ou des types.
// Ex: l'état d'une particule (Alive, Fading, StopAndKill...), le type de processus physique.

enum class EtatParticule {
    Vivante,        // La particule est en train de se propager
    Arretee,        // La particule s'est arrêtée
    Detruite,       // La particule a été absorbée
    HorsFrontiere   // La particule est sortie du monde
};

void coursEnumeration() {
    std::cout << "\n=== COURS : enum class ===" << std::endl;

    EtatParticule etat = EtatParticule::Vivante;

    // Utilisation dans un switch/case pour un comportement différent selon l'état
    switch(etat) {
        case EtatParticule::Vivante:
            std::cout << "Particule toujours en vol, propagation continue." << std::endl;
            break;
        case EtatParticule::Arretee:
            std::cout << "Particule arretee (Bragg peak atteint)." << std::endl;
            break;
        case EtatParticule::Detruite:
            std::cout << "Particule absorbee par la matiere." << std::endl;
            break;
        case EtatParticule::HorsFrontiere:
            std::cout << "Particule sortie du monde, simulation terminee pour elle." << std::endl;
            break;
    }
    // Dans Geant4 réel : G4TrackStatus est une enum (StepStatus, TrackStatus, etc.)
}


// ==============================================================================
// PARTIE 3 : LES MATHÉMATIQUES — Fonctions courantes dans Geant4
// ==============================================================================
// Geant4 fait beaucoup de calculs vectoriels, trigonométriques et statistiques.

void coursMathematiques() {
    std::cout << "\n=== COURS : Mathematiques C++ ===" << std::endl;

    // Constante Pi
    const double PI = 3.14159265358979323846;
    std::cout << "Pi = " << PI << std::endl;

    // Fonctions trigonométriques (les angles sont en RADIANS dans C++, pas en degrés)
    double angle_degres = 45.0;
    double angle_radians = angle_degres * PI / 180.0;
    std::cout << "\n45 degres = " << angle_radians << " radians" << std::endl;
    std::cout << "sin(45 deg) = " << std::sin(angle_radians) << std::endl;
    std::cout << "cos(45 deg) = " << std::cos(angle_radians) << std::endl;
    std::cout << "tan(45 deg) = " << std::tan(angle_radians) << std::endl;

    // Racine carrée
    std::cout << "\nsqrt(2) = " << std::sqrt(2.0) << std::endl;
    std::cout << "sqrt(144) = " << std::sqrt(144.0) << std::endl;

    // Puissance : x^n
    std::cout << "2 puissance 10 = " << std::pow(2.0, 10.0) << std::endl;

    // Valeur absolue
    std::cout << "abs(-7.5) = " << std::abs(-7.5) << std::endl;

    // Lien Geant4 : Ces fonctions sont utilisées pour calculer les angles des
    // particules, les directions de trajectoire, les distances, etc.
    // Exemple réel Geant4 :
    // G4ThreeVector direction(std::sin(theta)*std::cos(phi), 
    //                         std::sin(theta)*std::sin(phi), 
    //                         std::cos(theta));
}


// ==============================================================================
// PARTIE 4 : LES RÉFÉRENCES (& dans les paramètres de fonctions)
// ==============================================================================
// Dans Geant4, vous verrez souvent des fonctions avec & dans leurs paramètres.
// Une référence n'est PAS un pointeur, mais elle est liée à un seul objet.
// Elle permet de modifier l'original sans copier l'objet entier.

void modifierParValeur(double energie) {
    // Reçoit une COPIE de la variable. La modification n'affecte pas l'original.
    energie = 999.0;
    std::cout << "  [ParValeur] Energie locale (copie) : " << energie << std::endl;
}

void modifierParReference(double& energie) {
    // Reçoit une RÉFÉRENCE (un alias) vers l'original. 
    // La modification affecte l'original !
    // Le & dans le TYPE (pas dans l'appel) signifie "référence"
    energie = 999.0;
    std::cout << "  [ParReference] Energie modifiee : " << energie << std::endl;
}

void modifierParPointeur(double* ptrEnergie) {
    // Reçoit un POINTEUR vers l'original. Modification via déréférencement.
    *ptrEnergie = 888.0;
    std::cout << "  [ParPointeur] Energie modifiee : " << *ptrEnergie << std::endl;
}

void coursReferences() {
    std::cout << "\n=== COURS : VALEUR vs REFERENCE vs POINTEUR ===" << std::endl;
    
    double monEnergie = 50.0;
    
    std::cout << "Avant : monEnergie = " << monEnergie << std::endl;
    
    modifierParValeur(monEnergie);
    std::cout << "Apres parValeur : monEnergie = " << monEnergie << " (inchange!)" << std::endl;
    
    modifierParReference(monEnergie);
    std::cout << "Apres parReference : monEnergie = " << monEnergie << " (modifie!)" << std::endl;
    
    modifierParPointeur(&monEnergie); // On passe l'adresse avec &
    std::cout << "Apres parPointeur : monEnergie = " << monEnergie << " (modifie!)" << std::endl;

    // Dans Geant4, vous verrez des paramètres const double& energie
    // "const" = on ne peut pas modifier, "&" = pas de copie (pour la performance)
    // C'est la façon optimale de passer un grand objet en lecture seule.
}


// ==============================================================================
// PARTIE 5 : LES OPÉRATEURS DE FLUX (Très utiles pour déboguer Geant4)
// ==============================================================================
// G4cout et G4cerr sont les versions Geant4 de std::cout et std::cerr.
// Ils fonctionnent exactement pareil mais sont gérés par Geant4 
// (pour la journalisation, le mode verbose, etc.).
// Si vous comprenez std::cout, vous comprenez G4cout.

void coursFluxSortie() {
    std::cout << "\n=== COURS : FLUX DE SORTIE ET DÉBOGAGE ===" << std::endl;
    
    // std::cout : Sortie standard (ce que l'utilisateur voit)
    std::cout << "Message normal (comme G4cout dans Geant4)" << std::endl;
    
    // std::cerr : Sortie d'erreur standard (ne passe pas par le buffer)
    // Utilisé pour les messages d'erreur critiques
    std::cerr << "ATTENTION : Message d erreur critique (comme G4Exception)" << std::endl;
    
    // Formatage des nombres
    std::cout << std::fixed;          // Notation décimale fixe (pas scientifique)
    std::cout.precision(3);           // 3 chiffres après la virgule
    std::cout << "Pi formate : " << 3.14159265 << std::endl;
    
    // Dans Geant4, on utilise G4cout et G4endl :
    // G4cout << "Energie deposee : " << eDep/MeV << " MeV" << G4endl;
    // C'est IDENTIQUE à std::cout, juste renommé par Geant4.
}


// ==============================================================================
// RÉSUMÉ FINAL : GLOSSAIRE DES SYMBOLES GEANT4
// ==============================================================================
void afficherGlossaire() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "GLOSSAIRE DES SYMBOLES QUE VOUS VERREZ DANS GEANT4" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "G4Box*    -> Pointeur vers un objet G4Box" << std::endl;
    std::cout << "new G4Box -> Creer un objet dans le tas (Heap)" << std::endl;
    std::cout << "ptr->     -> Acceder a l'objet pointe (via pointeur)" << std::endl;
    std::cout << "obj.      -> Acceder a l'objet direct (sans pointeur)" << std::endl;
    std::cout << "::        -> Appartient a la classe (MyClass::MyMethod)" << std::endl;
    std::cout << "&var      -> Adresse de la variable (dans un appel de fonction)" << std::endl;
    std::cout << "Type&     -> Reference (dans une declaration de parametre)" << std::endl;
    std::cout << "override  -> Redefini une methode virtuelle du parent" << std::endl;
    std::cout << "virtual   -> Methode qui peut etre redefinie dans les enfants" << std::endl;
    std::cout << "const     -> La valeur/l'objet ne peut pas etre modifie(e)" << std::endl;
    std::cout << "#include  -> Copie-colle le contenu d'un autre fichier" << std::endl;
    std::cout << "#ifndef   -> Garde-fou pour eviter les inclusions multiples" << std::endl;
    std::cout << "nullptr   -> Pointeur ne pointant vers rien" << std::endl;
    std::cout << "delete    -> Liberer la memoire allouee avec new" << std::endl;
}


int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 07 : C++ SPECIFIQUE GEANT4       " << std::endl;
    std::cout << "==========================================" << std::endl;

    coursSurVector();
    coursEnumeration();
    coursMathematiques();
    coursReferences();
    coursFluxSortie();
    afficherGlossaire();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FÉLICITATIONS ! VOUS ÊTES PRÊT POUR GEANT4 !" << std::endl;
    std::cout << "  Prochaine étape : Installer Geant4 et bidouiller l'Exemple B1 !" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
