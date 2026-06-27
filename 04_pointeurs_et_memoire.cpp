// ==============================================================================
// COURS 04 : LES POINTEURS ET LA MÉMOIRE  (LE COEUR DE GEANT4)
// ==============================================================================
// Source d'inspiration : LearnCpp.com - Chapitres 9 et 12
//
// C'est LE chapitre le plus important pour comprendre Geant4.
// CHAQUE objet Geant4 est créé et manipulé avec des pointeurs.
// Prenez le temps de bien comprendre chaque exemple.
// ==============================================================================

#include <iostream>
#include <string>

// ==============================================================================
// PARTIE 1 : C'EST QUOI LA MÉMOIRE ? L'ANALOGIE DE LA RUE
// ==============================================================================
//
// Imaginez que la mémoire RAM de votre ordinateur est une longue rue avec des
// milliers de maisons. Chaque maison a :
//   - Une ADRESSE unique (ex: "127 Rue de la Mémoire")
//   - Un CONTENU (une valeur stockée à l'intérieur : ex: le nombre 42)
//
// Quand vous déclarez une variable normale :
//   int nombreDeParticules = 1000;
// L'ordinateur choisit une maison libre (disons l'adresse 0x7fff5), 
// y stocke la valeur 1000, et "nombreDeParticules" devient le surnom de cette maison.
//
// Un POINTEUR, c'est une variable spéciale qui ne stocke pas 1000 dans sa maison,
// mais qui stocke l'ADRESSE d'une autre maison (ex: 0x7fff5).
// Le pointeur "pointe" vers une autre adresse mémoire. D'où son nom !
// ==============================================================================


// ==============================================================================
// PARTIE 2 : DÉCLARER ET UTILISER UN POINTEUR
// ==============================================================================
void expliquerPointeurSimple() {
    std::cout << "\n=== DEMO POINTEURS SIMPLES ===" << std::endl;

    // --- Variable normale ---
    int energie = 150;  // La maison à l'adresse X contient la valeur 150

    // --- L'opérateur & (esperluette) : Donne l'ADRESSE d'une variable ---
    // "&energie" signifie : "Donne moi l'adresse GPS de la variable 'energie'"
    // Chaque fois que vous voyez & devant un nom de variable, lisez "adresse de"
    std::cout << "La valeur de 'energie' est : " << energie << std::endl;
    std::cout << "L'adresse de 'energie' en memoire est : " << &energie << std::endl;
    // (L'adresse affichée ressemble à : 0x7ffeefbff4ac — un nombre hexadécimal)


    // --- Déclaration d'un POINTEUR ---
    // Syntaxe : TypeCible* nomDuPointeur = &variableCible;
    // L'étoile * DANS LA DÉCLARATION signifie "c'est un pointeur"
    int* ptrEnergie = &energie;
    //  ^^^^                    ^^^^^^^^^^^
    //  Type : "pointeur vers un int"      L'adresse de 'energie'

    std::cout << "\nptrEnergie contient (l'adresse) : " << ptrEnergie << std::endl;
    
    // --- L'opérateur * (déréférencement) ---
    // Quand l'étoile est utilisée SUR un pointeur EXISTANT (pas dans une déclaration),
    // elle signifie "Va à cette adresse et donne moi CE QUI EST DEDANS".
    // On appelle ça "déréférencer" le pointeur.
    std::cout << "*ptrEnergie (valeur a cette adresse) : " << *ptrEnergie << std::endl;
    // Ceci affiche bien 150, car on est allé lire le contenu de l'adresse de 'energie'

    // --- MODIFIER via un pointeur ---
    *ptrEnergie = 200; // "Va à l'adresse de 'energie', et mets-y 200"
    std::cout << "\nApres *ptrEnergie = 200 :" << std::endl;
    std::cout << "energie vaut maintenant : " << energie << std::endl; // Affiche 200 !
    // La variable originale 'energie' a bien été modifiée via le pointeur !

    // --- RÉSUMÉ des deux rôles de l'étoile * ---
    // 1. Dans une DÉCLARATION : int* ptr;    -> déclare ptr comme un POINTEUR
    // 2. Sur un POINTEUR EXISTANT : *ptr = 5 -> ACCÈDE au contenu pointé
}


// ==============================================================================
// PARTIE 3 : LE MOT-CLÉ "new" ET L'ALLOCATION DYNAMIQUE
// ==============================================================================
// C'est LE mécanisme que Geant4 utilise pour TOUT créer.
//
// Sans "new" : La variable est créée dans la PILE (Stack). Elle est détruite
// automatiquement quand la fonction se termine. Utile pour les petites choses.
//
// Avec "new" : L'objet est créé dans le TAS (Heap). Il vit AUSSI LONGTEMPS
// QUE VOUS LE VOULEZ, même après la fin de la fonction. Geant4 crée ses 
// détecteurs dans le tas pour qu'ils persistent pendant toute la simulation.
void expliquerNew() {
    std::cout << "\n=== DEMO DU MOT-CLE 'new' ===" << std::endl;

    // Sans new : 'energieLocale' est détruite quand cette fonction se termine
    double energieLocale = 10.5;

    // Avec new : l'objet double est créé dans le TAS et persiste.
    // "new double(50.0)" fait deux choses :
    //   1. Il réserve une zone mémoire dans le TAS pour stocker un double
    //   2. Il y met la valeur 50.0
    //   3. Il retourne l'ADRESSE de cette zone mémoire
    // On stocke cette adresse dans un pointeur.
    double* ptrDansTas = new double(50.0);

    std::cout << "Valeur dans le tas : " << *ptrDansTas << std::endl;
    *ptrDansTas = 75.5; // On peut modifier la valeur
    std::cout << "Valeur modifiee : " << *ptrDansTas << std::endl;

    // TRÈS IMPORTANT : Quand on utilise "new", on doit utiliser "delete" à la fin !
    // Si on oublie, la mémoire reste occupée pour rien : c'est une "fuite mémoire".
    // (Dans Geant4, c'est le RunManager qui s'occupe de delete pour vous)
    delete ptrDansTas;
    std::cout << "Memoire liberee avec delete." << std::endl;

    // Note Geant4 : Dans Geant4, vous écrirez souvent :
    //   G4Box* maBoite = new G4Box("nom", 10, 10, 10);
    // C'est exactement le même principe : on crée un objet G4Box dans le tas
    // et on stocke son adresse dans le pointeur 'maBoite'.
}


// ==============================================================================
// PARTIE 4 : LA FLÈCHE -> (L'OPÉRATEUR D'ACCÈS VIA POINTEUR)
// ==============================================================================
// Quand on a un pointeur vers un OBJET (une structure ou une classe),
// on ne peut pas utiliser le point "." pour accéder à ses membres.
// On doit utiliser la flèche "->".
//
// RÈGLE :
//   - Si ma variable EST l'objet directement  : j'utilise le POINT "."
//   - Si ma variable EST un POINTEUR vers l'objet : j'utilise la FLÈCHE "->"

struct Particule { // "struct" est une version simplifiée de "class"
    std::string nom;
    double energie;
    int charge;

    void afficher() {
        std::cout << "Particule: " << nom 
                  << " | Energie: " << energie << " MeV"
                  << " | Charge: " << charge << std::endl;
    }
};

void expliquerFleche() {
    std::cout << "\n=== DEMO DE LA FLECHE -> ===" << std::endl;

    // --- Cas 1 : Objet direct (utilisation du POINT) ---
    Particule electron; // Objet direct, pas de new
    electron.nom = "Electron"; // POINT pour accéder
    electron.energie = 0.511;
    electron.charge = -1;
    electron.afficher(); // POINT pour appeler une méthode

    // --- Cas 2 : Pointeur vers un objet (utilisation de la FLÈCHE) ---
    Particule* ptrProton = new Particule(); // Pointeur, avec new
    ptrProton->nom = "Proton"; // FLÈCHE pour accéder (car c'est un pointeur)
    ptrProton->energie = 938.3;
    ptrProton->charge = +1;
    ptrProton->afficher(); // FLÈCHE pour appeler une méthode

    // ptrProton->afficher() est EXACTEMENT équivalent à (*ptrProton).afficher()
    // La flèche est juste un raccourci plus lisible.

    delete ptrProton;

    // Dans Geant4, vous écrirez TOUJOURS avec la flèche car TOUT est des pointeurs :
    // canon->SetParticleEnergy(10 * MeV);
    // runManager->Initialize();
    // nist->FindOrBuildMaterial("G4_WATER");
}


// ==============================================================================
// PARTIE 5 : NULLPTR (Le pointeur "vide")
// ==============================================================================
void expliquerNullptr() {
    std::cout << "\n=== DEMO DE NULLPTR ===" << std::endl;
    
    // Un pointeur non initialisé pointe vers une adresse ALÉATOIRE.
    // L'utiliser sans initialisation = CATASTROPHE (crash ou corruption mémoire)
    // int* dangereux;  // NE JAMAIS FAIRE ÇA
    // *dangereux = 5;  // CATASTROPHE ASSURÉE

    // La bonne pratique : toujours initialiser un pointeur.
    // Si vous n'avez pas encore l'objet, mettez-le à "nullptr" (pointeur nul).
    // nullptr signifie "ce pointeur ne pointe vers rien pour l'instant".
    int* ptrSur = nullptr; // Pointeur nul, sans danger

    // On peut vérifier si un pointeur est nul avant de l'utiliser :
    if (ptrSur == nullptr) {
        std::cout << "Le pointeur est nul, pas d'objet pour l'instant." << std::endl;
    }

    // On lui donne ensuite une vraie valeur
    int valeur = 42;
    ptrSur = &valeur;
    
    if (ptrSur != nullptr) { // On vérifie qu'il n'est plus nul
        std::cout << "Le pointeur pointe maintenant vers : " << *ptrSur << std::endl;
    }
}


// ==============================================================================
// RÉSUMÉ FINAL : LA TRADUCTION GEANT4
// ==============================================================================
// Ligne Geant4 réelle :
//   G4RunManager* runManager = new G4RunManager();
//
// Traduction mot par mot :
//   G4RunManager* -> "Je crée une variable qui sera un POINTEUR vers un objet de type G4RunManager"
//   runManager    -> "Le nom de cette variable (notre étiquette GPS)"
//   =             -> "Reçoit comme valeur..."
//   new           -> "...l'adresse d'un nouvel objet créé dans le TAS..."
//   G4RunManager()-> "...de type G4RunManager, construit avec son constructeur par défaut"
//   ;             -> Fin de l'instruction.
//
// Ligne Geant4 réelle :
//   runManager->SetUserInitialization(new MyDetectorConstruction());
//
// Traduction :
//   runManager->  -> "Va à l'adresse de runManager et..."
//   SetUserInit...-> "...appelle la méthode SetUserInitialization"
//   (new MyDetector...) -> "...en lui passant en argument UN NOUVEAU POINTEUR vers
//                           un objet MyDetectorConstruction créé dans le tas"
// ==============================================================================


int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 04 : POINTEURS ET MEMOIRE        " << std::endl;
    std::cout << "==========================================" << std::endl;

    expliquerPointeurSimple();
    expliquerNew();
    expliquerFleche();
    expliquerNullptr();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FIN DU COURS - VOUS MAÎTRISEZ LES POINTEURS !" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
