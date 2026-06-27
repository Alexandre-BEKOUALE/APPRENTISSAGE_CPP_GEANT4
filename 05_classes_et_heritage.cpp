// ==============================================================================
// COURS 05 : LES CLASSES ET L'HÉRITAGE (PROGRAMMATION ORIENTÉE OBJET)
// ==============================================================================
// Source d'inspiration : LearnCpp.com - Chapitres 14 à 17
//
// C'est le coeur de la programmation C++ et la structure fondamentale de Geant4.
// Toute la bibliothèque Geant4 est construite autour des classes et de l'héritage.
// Maîtrisez ce chapitre et vous pourrez lire le code Geant4 comme un livre !
// ==============================================================================

#include <iostream>
#include <string>

// ==============================================================================
// PARTIE 1 : LA CLASSE COMPLÈTE
// ==============================================================================
// Rappel : Une CLASSE est un "plan de construction" pour créer des objets.
// Elle regroupe dans un seul endroit :
//   - Des DONNÉES (les attributs) : ce que l'objet POSSÈDE
//   - Des COMPORTEMENTS (les méthodes) : ce que l'objet SAIT FAIRE

class Volume {
    // Tout ce qui est écrit ici est la "définition" de la classe Volume
    // C'est le plan de construction d'un volume physique (comme dans Geant4)

// --- Mots-clés de visibilité ---
// "private:" -> accessible UNIQUEMENT depuis l'intérieur de la classe
// "public:"  -> accessible par TOUT LE MONDE depuis l'extérieur
// "protected:" -> accessible depuis la classe ET ses classes enfants (héritage)

private:
    // LES ATTRIBUTS : Les données internes de l'objet
    // On les met en "private" pour les protéger. 
    // On ne veut pas que n'importe qui vienne mettre n'importe quelle valeur directement.
    std::string m_nom;       // Le préfixe "m_" est une convention : m_ = membre de la classe
    double m_longueur;       // En cm (demi-longueur comme dans Geant4)
    double m_largeur;
    double m_hauteur;
    std::string m_materiau;

public:
    // LE CONSTRUCTEUR : La fonction appelée automatiquement à la création de l'objet
    // Il porte le MÊME NOM que la classe. Il n'a PAS de type de retour (même pas void).
    Volume(std::string nom, double lon, double lar, double hau, std::string mat) {
        // La liste d'initialisation : on remplit les attributs avec les valeurs reçues
        m_nom = nom;
        m_longueur = lon;
        m_largeur = lar;
        m_hauteur = hau;
        m_materiau = mat;
        // Un message de confirmation (utile pour le débogage)
        std::cout << "[Constructeur] Volume cree : " << m_nom << std::endl;
    }

    // LE DESTRUCTEUR : Appelé automatiquement quand l'objet est detruit (delete)
    // Il porte le même nom que la classe mais précédé d'un tilde ~
    // On ne le définit pas toujours, mais il est important de savoir qu'il existe
    ~Volume() {
        std::cout << "[Destructeur] Volume detruit : " << m_nom << std::endl;
    }

    // LES GETTERS (Accesseurs) : Des méthodes pour LIRE les attributs privés
    // Par convention, on les nomme "getNom" ou simplement "nom()"
    // Le mot-clé "const" à la fin signifie : "cette méthode ne MODIFIE PAS l'objet"
    std::string getNom() const { return m_nom; }
    double getLongueur() const { return m_longueur; }
    std::string getMateriau() const { return m_materiau; }

    // LES SETTERS (Mutateurs) : Des méthodes pour MODIFIER les attributs privés
    // Ils nous permettent d'ajouter des vérifications avant de modifier
    void setMateriau(std::string nouveauMateriau) {
        // On pourrait vérifier que le matériau est dans la liste de Geant4 par exemple
        m_materiau = nouveauMateriau;
        std::cout << "[Info] Materiau change pour : " << m_materiau << std::endl;
    }

    // UNE MÉTHODE PUBLIQUE : Ce que l'objet sait faire
    double calculerVolume() const {
        return (2*m_longueur) * (2*m_largeur) * (2*m_hauteur); // Geant4 utilise des demi-longueurs
    }

    void afficherInfos() const {
        std::cout << "----------------------------" << std::endl;
        std::cout << "Volume : " << m_nom << std::endl;
        std::cout << "Dimensions (L x l x h): " << 2*m_longueur << " x " 
                  << 2*m_largeur << " x " << 2*m_hauteur << " cm" << std::endl;
        std::cout << "Materiau : " << m_materiau << std::endl;
        std::cout << "Volume total : " << calculerVolume() << " cm3" << std::endl;
    }
};


// ==============================================================================
// PARTIE 2 : L'HÉRITAGE (Le concept le plus important de Geant4)
// ==============================================================================
//
// L'HÉRITAGE permet de créer une nouvelle classe (enfant) qui HÉRITE 
// de tous les attributs et méthodes d'une classe existante (parent),
// tout en pouvant y ajouter ses propres fonctionnalités ou modifier le comportement.
//
// Dans Geant4, TOUT fonctionne par héritage. Geant4 vous donne des classes
// "génériques" et vous créez vos classes "personnalisées" qui en héritent.
//
// Syntaxe : class ClasseEnfant : public ClasseParent { ... };
// Le mot "public" signifie que l'enfant hérite des parties publiques du parent.
//
// ANALOGIE : 
//   Geant4 a une classe "Animal" (avec des méthodes de base comme "respirer").
//   Vous créez "Chien" qui hérite d'Animal et ajoute la méthode "aboyer".
//   Vous créez "Chat" qui hérite d'Animal et ajoute la méthode "miauler".


// --- La classe PARENT (comme une classe abstraite de Geant4) ---
// C'est la classe de base que Geant4 vous fournirait.
class G4VUserDetectorConstruction {
    // Le "V" dans les noms Geant4 signifie "Virtual" (virtuelle/abstraite)
    // Le "User" signifie que c'est une classe que L'UTILISATEUR doit remplir
public:
    G4VUserDetectorConstruction() {
        std::cout << "[Parent] G4VUserDetectorConstruction cree." << std::endl;
    }

    // Méthode VIRTUELLE PURE : C'est la signature que la classe enfant DOIT implémenter
    // "virtual" : cette méthode peut être redéfinie dans les classes enfants
    // "= 0"     : c'est obligatoire, l'enfant DOIT la redéfinir. On appelle ça une méthode abstraite.
    virtual void Construct() = 0; 

    // Méthode virtuelle normale : peut être redéfinie, mais ce n'est pas obligatoire
    virtual void afficherInfoParent() {
        std::cout << "[Parent] Je suis la classe parent du detecteur." << std::endl;
    }
};


// --- La classe ENFANT (votre propre code dans Geant4) ---
// "MonDetecteur" hérite de "G4VUserDetectorConstruction"
class MonDetecteur : public G4VUserDetectorConstruction {
    // MonDetecteur HÉRITE de tout ce qui est "public" dans G4VUserDetectorConstruction

private:
    std::string m_typeDetecteur;

public:
    // Le constructeur de l'enfant appelle D'ABORD le constructeur du parent
    MonDetecteur(std::string type) : m_typeDetecteur(type) {
        // La syntaxe ": m_typeDetecteur(type)" est une "liste d'initialisation de membre"
        // C'est la façon recommandée d'initialiser les membres dans un constructeur
        std::cout << "[Enfant] MonDetecteur cree : " << m_typeDetecteur << std::endl;
    }

    // On IMPLÉMENTE la méthode virtuelle pure Construct() héritée du parent
    // Le mot-clé "override" (en C++11 et plus) confirme qu'on redéfinit bien une méthode parent
    // C'est une bonne pratique car le compilateur vous prévient si vous faites une faute de frappe
    void Construct() override {
        std::cout << "[Enfant] Construct() appelee sur : " << m_typeDetecteur << std::endl;
        std::cout << "[Enfant] -> Je construis la geometrie de mon detecteur..." << std::endl;
    }

    // On peut aussi REDÉFINIR une méthode virtuelle non-pure du parent
    void afficherInfoParent() override {
        std::cout << "[Enfant] Je suis MonDetecteur de type : " << m_typeDetecteur << std::endl;
    }

    // Et on peut ajouter de NOUVELLES méthodes propres à l'enfant
    void afficherTypeDetecteur() {
        std::cout << "Type de detecteur specifique : " << m_typeDetecteur << std::endl;
    }
};


// ==============================================================================
// PARTIE 3 : POLYMORPHISME (la conséquence magique de l'héritage)
// ==============================================================================
// Le Polymorphisme : Un pointeur de type PARENT peut pointer vers un objet ENFANT.
// Quand on appelle une méthode virtuelle via ce pointeur, c'est la version de l'ENFANT
// qui est exécutée. C'est le moteur invisible de Geant4.
//
// Geant4 stocke VOTRE détecteur dans un pointeur de type parent (G4VUserDetectorConstruction*),
// mais c'est bien VOTRE méthode Construct() qui sera appelée. C'est le polymorphisme !
void demontrerPolymorphisme() {
    std::cout << "\n=== DEMONSTRATION DU POLYMORPHISME ===" << std::endl;
    
    // Un pointeur de type PARENT qui pointe vers un objet ENFANT
    // C'est EXACTEMENT ce que fait Geant4 en interne avec vos classes !
    G4VUserDetectorConstruction* ptr = new MonDetecteur("Detecteur_Eau_Plomb");
    
    // On appelle une méthode via le pointeur PARENT
    // Mais c'est la version de l'ENFANT qui s'exécute (grâce à "virtual" et "override")
    ptr->Construct();         // Appelle MonDetecteur::Construct()
    ptr->afficherInfoParent(); // Appelle MonDetecteur::afficherInfoParent()
    
    // SANS virtual, ces appels auraient exécuté la version du PARENT.
    // AVEC virtual, le bon comportement est sélectionné automatiquement.
    
    delete ptr;
}


// ==============================================================================
// RÉSUMÉ : COMMENT GEANT4 UTILISE CES CONCEPTS
// ==============================================================================
//
// 1. Geant4 définit G4VUserDetectorConstruction avec des méthodes virtuelles pures.
// 2. VOUS créez MyDetectorConstruction qui hérite de G4VUserDetectorConstruction.
// 3. VOUS implémentez la méthode Construct() avec votre géométrie.
// 4. VOUS donnez un pointeur vers votre objet au RunManager :
//       runManager->SetUserInitialization(new MyDetectorConstruction());
// 5. Geant4 appelle ptr->Construct() depuis son code interne.
// 6. Grâce au polymorphisme, VOTRE Construct() est appelée automatiquement !
// ==============================================================================


int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 05 : CLASSES ET HÉRITAGE         " << std::endl;
    std::cout << "==========================================" << std::endl;

    // --- Test de la classe Volume ---
    std::cout << "\n--- TEST DE LA CLASSE VOLUME ---" << std::endl;
    Volume* monVolumeEau = new Volume("CubeEau", 10.0, 10.0, 10.0, "G4_WATER");
    monVolumeEau->afficherInfos();
    monVolumeEau->setMateriau("G4_Pb"); // Changement de matériau
    monVolumeEau->afficherInfos();
    delete monVolumeEau;

    // --- Test de l'héritage ---
    std::cout << "\n--- TEST DE L'HÉRITAGE ---" << std::endl;
    MonDetecteur* monDet = new MonDetecteur("CalorimètreScintillateur");
    monDet->Construct();
    monDet->afficherTypeDetecteur();
    delete monDet;

    // --- Test du polymorphisme ---
    demontrerPolymorphisme();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FIN DU COURS - VOUS MAÎTRISEZ LA POO ! " << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
