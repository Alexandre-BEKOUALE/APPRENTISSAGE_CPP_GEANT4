// ==============================================================================
// COURS 02 : CONDITIONS ET BOUCLES
// ==============================================================================
// Source : LearnCpp.com - Chapitres 4 et 8
//
// Ce cours couvre la "logique" du C++.
// Dans Geant4, les conditions vérifient si une particule est dans le bon volume,
// et les boucles simulent N particules l'une après l'autre.
// ==============================================================================

#include <iostream>
#include <string>

// ==============================================================================
// PARTIE 1 : LES CONDITIONS — if / else if / else
// ==============================================================================
// ANALOGIE : Un agent de sécurité à l'entrée d'un accélérateur.
// Il vérifie l'énergie de la particule et décide quoi faire.

void coursConditions() {
    std::cout << "\n=== COURS : CONDITIONS ===" << std::endl;

    double energieMeV = 150.0; // Énergie de la particule en MeV

    // Structure de base :
    // if (condition) { ... } else if (condition) { ... } else { ... }

    if (energieMeV > 200.0) {
        // Ce bloc s'exécute SI l'énergie est supérieure à 200 MeV
        std::cout << "Particule a haute energie -> Physique hadronique" << std::endl;
    } else if (energieMeV >= 50.0) {
        // CE bloc s'exécute SI la condition du 'if' est fausse ET celle-ci est vraie
        std::cout << "Particule a energie intermediaire -> Physique EM" << std::endl;
    } else {
        // CE bloc s'exécute si AUCUNE condition précédente n'est vraie
        std::cout << "Particule a basse energie -> Physique thermique" << std::endl;
    }

    // --- Les opérateurs de comparaison ---
    // ==  : Égal à          (ATTENTION : pas = qui est l'affectation !)
    // !=  : Différent de
    // >   : Strictement supérieur
    // <   : Strictement inférieur
    // >=  : Supérieur ou égal
    // <=  : Inférieur ou égal
    std::cout << "\nTest des operateurs de comparaison :" << std::endl;
    std::cout << "150 == 150 ? " << (150 == 150) << std::endl; // 1 = vrai
    std::cout << "150 != 200 ? " << (150 != 200) << std::endl; // 1 = vrai
    std::cout << "150 > 200  ? " << (150 > 200)  << std::endl; // 0 = faux

    // --- Les opérateurs logiques ---
    // &&  : ET logique  (les DEUX conditions doivent être vraies)
    // ||  : OU logique  (AU MOINS UNE condition doit être vraie)
    // !   : NON logique (inverse vrai/faux)
    bool dansVolume = true;
    bool particuleChargee = true;

    if (dansVolume && particuleChargee) {
        std::cout << "\nParticule chargee ET dans le volume -> Enregistrement." << std::endl;
    }
    if (!dansVolume) {
        std::cout << "Particule hors du volume." << std::endl;
    }

    // Lien Geant4 :
    // if (aStep->GetTrack()->GetKineticEnergy() > seuil) { ... }
    // if (volume == fDetectorLogic && particule == "gamma") { ... }
}

// ==============================================================================
// PARTIE 2 : LE SWITCH / CASE — Choisir parmi plusieurs options
// ==============================================================================
// Plus lisible qu'une longue chaîne de if/else if quand on compare
// une variable à des valeurs exactes.

void coursSwitch() {
    std::cout << "\n=== COURS : SWITCH/CASE ===" << std::endl;

    int codeParticule = 2; // 1=électron, 2=proton, 3=neutron, 4=photon

    switch (codeParticule) {
        case 1:
            std::cout << "C'est un Electron (charge -1)" << std::endl;
            break; // CRUCIAL : sans break, l'exécution "tombe" dans le case suivant !

        case 2:
            std::cout << "C'est un Proton (charge +1)" << std::endl;
            break;

        case 3:
            std::cout << "C'est un Neutron (charge 0)" << std::endl;
            break;

        case 4:
            std::cout << "C'est un Photon (gamma)" << std::endl;
            break;

        default: // Exécuté si AUCUN case ne correspond
            std::cout << "Particule inconnue !" << std::endl;
            break;
    }
}

// ==============================================================================
// PARTIE 3 : LA BOUCLE FOR — Répéter un nombre CONNU de fois
// ==============================================================================
// C'est la boucle la plus utilisée. Dans Geant4, BeamOn(N) déclenche
// en interne une boucle for qui tire N particules l'une après l'autre.

void coursBoucleFor() {
    std::cout << "\n=== COURS : BOUCLE FOR ===" << std::endl;

    // Syntaxe : for (initialisation ; condition ; increment) { ... }
    //   - initialisation : exécutée UNE FOIS au début (int i = 0)
    //   - condition      : vérifiée AVANT chaque tour (i < 10)
    //   - incrément      : exécuté APRÈS chaque tour (i++)

    std::cout << "Simulation de 5 particules :" << std::endl;
    for (int i = 1; i <= 5; i++) {
        // i++ signifie "augmenter i de 1 après cette ligne"
        // i=1 : 1er tour, i=2 : 2ème tour... jusqu'à i=5
        std::cout << "  -> Particule N°" << i << " simulee." << std::endl;
    }

    // Boucle à rebours
    std::cout << "\nCompte a rebours :" << std::endl;
    for (int compte = 5; compte >= 1; compte--) {
        // compte-- signifie "diminuer compte de 1 après cette ligne"
        std::cout << compte << "... ";
    }
    std::cout << "Lancement !" << std::endl;

    // Calcul de la somme d'énergies
    double energieTotale = 0.0;
    for (int i = 0; i < 5; i++) {
        double energie = 10.0 * (i + 1); // 10, 20, 30, 40, 50 MeV
        energieTotale += energie; // += signifie "ajouter à moi-même"
        std::cout << "Particule " << (i+1) << " : " << energie << " MeV deposee." << std::endl;
    }
    std::cout << "Energie totale deposee : " << energieTotale << " MeV" << std::endl;
}

// ==============================================================================
// PARTIE 4 : LA BOUCLE WHILE — Répéter jusqu'à ce qu'une condition soit fausse
// ==============================================================================
// Utile quand on ne sait pas à l'avance combien de fois on va répéter.
// Ex: simuler une particule jusqu'à ce qu'elle s'arrête.

void coursBoucleWhile() {
    std::cout << "\n=== COURS : BOUCLE WHILE ===" << std::endl;

    // Simulation simplifiée d'une particule qui perd de l'énergie
    double energie = 100.0; // MeV
    double perteParPas = 12.5; // MeV perdus à chaque pas
    int nombreDePas = 0;

    std::cout << "Simulation de freinage d'une particule :" << std::endl;

    // La boucle continue TANT QUE l'énergie est positive
    while (energie > 0) {
        nombreDePas++;
        energie -= perteParPas; // -= signifie "soustraire de moi-même"
        if (energie < 0) energie = 0; // On ne descend pas en dessous de 0

        std::cout << "  Pas " << nombreDePas
                  << " | Energie restante : " << energie << " MeV" << std::endl;
    }
    std::cout << "Particule arretee apres " << nombreDePas << " pas." << std::endl;
    std::cout << "(C'est le Pic de Bragg en version simplifiee !)" << std::endl;
}

// ==============================================================================
// PARTIE 5 : BREAK ET CONTINUE — Contrôler les boucles
// ==============================================================================

void coursBreakContinue() {
    std::cout << "\n=== COURS : BREAK ET CONTINUE ===" << std::endl;

    // BREAK : Sort immédiatement de la boucle
    std::cout << "Test de BREAK (on s'arrete a la particule 3) :" << std::endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 3) {
            std::cout << "  Energie seuil atteinte ! Arret de la boucle." << std::endl;
            break; // On sort de la boucle for
        }
        std::cout << "  Particule " << i << " traitee." << std::endl;
    }

    // CONTINUE : Passe au tour suivant sans exécuter la suite du bloc
    std::cout << "\nTest de CONTINUE (on ignore les particules paires) :" << std::endl;
    for (int i = 1; i <= 8; i++) {
        if (i % 2 == 0) { // % = modulo, donne le reste de la division
            continue; // On passe directement au i++ et à la prochaine vérification
        }
        std::cout << "  Particule impaire " << i << " enregistree." << std::endl;
    }

    // Dans Geant4 : "continue" est utile pour ignorer des particules
    // qui ne nous intéressent pas (ex: neutrons dans un calorimètre EM)
}

// ==============================================================================
// RÉSUMÉ LIEN GEANT4
// ==============================================================================
// La structure typique d'une méthode Geant4 (SteppingAction) ressemble à :
//
// void MySteppingAction::UserSteppingAction(const G4Step* step) {
//
//     // CONDITION : On vérifie que la particule est dans le bon volume
//     if (step->GetPreStepPoint()->GetPhysicalVolume()->GetName() != "Detecteur")
//         return; // Comme un "continue" : on ignore ce pas
//
//     // CONDITION : On filtre les particules qui nous intéressent
//     G4String nomParticule = step->GetTrack()->GetDefinition()->GetParticleName();
//     if (nomParticule == "neutron") return; // On ignore les neutrons
//
//     // CALCUL : On récupère l'énergie déposée pendant CE pas
//     double edep = step->GetTotalEnergyDeposit();
//
//     // CONDITION : On enregistre uniquement si l'énergie déposée est notable
//     if (edep > 0) {
//         fEnergieTotale += edep; // On accumule dans une variable totale
//     }
// }
// ==============================================================================

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  COURS 02 : CONDITIONS ET BOUCLES       " << std::endl;
    std::cout << "==========================================" << std::endl;

    coursConditions();
    coursSwitch();
    coursBoucleFor();
    coursBoucleWhile();
    coursBreakContinue();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "  FIN DU COURS 02 !" << std::endl;
    std::cout << "  Prochain cours : 03_fonctions.cpp" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
