// =============================================================================
//  COURS C++ POUR GEANT4 — FICHIER 01
//  Sujet : Les Variables et les Types en C++
//  Auteur : Cours pédagogique C++/Geant4
//  Niveau : Débutant absolu
// =============================================================================
//
//  Ce fichier est un cours complet et autonome.
//  Tu peux le compiler et l'exécuter directement :
//
//    g++ -o 01_variables_et_types 01_variables_et_types.cpp
//    ./01_variables_et_types          (Linux/Mac)
//    01_variables_et_types.exe        (Windows)
//
// =============================================================================

// --- Les directives #include ---
// On "inclut" des bibliothèques pour avoir accès à des fonctionnalités
// supplémentaires. C'est comme dire : "j'ai besoin de cet outil".

#include <iostream>  // Pour std::cout (affichage) et std::cin (lecture clavier)
#include <string>    // Pour le type std::string (chaîne de caractères)

// =============================================================================
//  SECTION 1 : QU'EST-CE QU'UNE VARIABLE ?
// =============================================================================
//
//  ANALOGIE AVEC UNE BOÎTE :
//  --------------------------
//  Imagine une boîte physique dans ta chambre.
//  Cette boîte a :
//    - Un ÉTIQUETTE (le nom de la variable)
//    - Un CONTENU   (la valeur stockée)
//    - Une TAILLE   (le type de données qu'elle peut contenir)
//
//  Exemple concret :
//    Une boîte étiquetée "energie_particule" ne peut contenir que des
//    nombres décimaux (pas des textes, pas des photos).
//
//  En C++, une variable = un espace mémoire réservé dans la RAM
//  auquel on donne un nom pour y accéder facilement.
//
//  RÈGLES DE NOMMAGE (très importantes !) :
//    ✓ Noms valides   : energie, nb_particules, position_x, myVar
//    ✗ Noms invalides : 1energie (commence par un chiffre)
//    ✗                  energie particule (espace interdit -> utiliser _)
//    ✗                  class (mot réservé par C++)
//    -> Convention en Geant4 : souvent camelCase (energieParticule)
//       ou avec underscore (energie_particule)
//
// =============================================================================

// =============================================================================
//  SECTION 2 : LES TYPES DE BASE EN C++
// =============================================================================
//
//  Le TYPE d'une variable détermine :
//    1. Combien d'octets en mémoire sont réservés
//    2. Quelles valeurs peuvent être stockées
//    3. Quelles opérations sont autorisées
//
//  TYPE        | TAILLE    | DESCRIPTION & EXEMPLE
//  ------------|-----------|----------------------------------------------------
//  int         | 4 octets  | Entier : -2 147 483 648 a +2 147 483 647
//              |           | Ex : nombre de particules = 1000
//  ------------|-----------|----------------------------------------------------
//  double      | 8 octets  | Décimal double précision (15-16 chiffres)
//              |           | Ex : énergie = 1.234567890123456 MeV
//  ------------|-----------|----------------------------------------------------
//  float       | 4 octets  | Décimal simple précision (6-7 chiffres)
//              |           | Ex : valeur approchée = 3.14f
//  ------------|-----------|----------------------------------------------------
//  char        | 1 octet   | Un seul caractère entre apostrophes
//              |           | Ex : 'A', 'e', '3', '!'
//  ------------|-----------|----------------------------------------------------
//  bool        | 1 octet   | Vrai (true) ou Faux (false) uniquement
//              |           | Ex : simulation_active = true
//  ------------|-----------|----------------------------------------------------
//  std::string | variable  | Chaîne de caractères entre guillemets
//              |           | Ex : nom_particule = "proton"
//  ------------|-----------|----------------------------------------------------
//
//  ATTENTION : En physique (et en Geant4), on utilise PRESQUE TOUJOURS
//  'double' plutôt que 'float' pour les calculs numériques, car la précision
//  de float (6-7 chiffres) est insuffisante pour les simulations de particules.
//
// =============================================================================

// =============================================================================
//  SECTION 3 : DÉCLARATION ET INITIALISATION
// =============================================================================
//
//  DÉCLARATION = dire au compilateur qu'une variable existe
//    Syntaxe :  TYPE nom_variable ;
//    Exemple :  int nombreDeParticules ;
//
//  INITIALISATION = donner une valeur de départ à la variable
//    Syntaxe :  TYPE nom_variable = valeur_initiale ;
//    Exemple :  int nombreDeParticules = 100 ;
//
//  BONNE PRATIQUE : Toujours initialiser ses variables !
//  Une variable non initialisée contient une valeur ALÉATOIRE
//  (ce qui reste en mémoire = "garbage value"). C'est une source
//  classique de bugs très difficiles à trouver.
//
//  ERREUR COURANTE :
//    int x ;       // x contient une valeur inconnue ("garbage")
//    int y = x ;   // DANGER : y reçoit une valeur non définie !
//
//  BONNE PRATIQUE :
//    int x = 0 ;   // x est explicitement initialisé à zéro
//
// =============================================================================

// =============================================================================
//  SECTION 4 : LE MOT-CLÉ 'const'
// =============================================================================
//
//  'const' signifie "constant" -> la valeur NE PEUT PAS CHANGER après
//  l'initialisation. Si tu essaies de la modifier, le compilateur te donne
//  une ERREUR (pas un avertissement, une vraie erreur -> code ne compile pas).
//
//  ANALOGIE : Une boîte soudée. Tu peux lire son contenu, mais impossible
//  de l'ouvrir pour changer ce qu'il y a dedans.
//
//  RÈGLE IMPORTANTE : Une 'const' DOIT être initialisée à sa déclaration.
//  Tu ne peux pas écrire :  const double PI ;  // ERREUR !
//  Tu dois écrire :         const double PI = 3.14159265358979 ;
//
//  UTILISATION EN GEANT4 :
//  Les constantes physiques (vitesse de la lumière, masse du proton, etc.)
//  sont des 'const'. On ne veut surtout pas les modifier par accident
//  pendant une simulation !
//
//  Convention de nommage pour les constantes :
//    -> Souvent en MAJUSCULES : PI, MASSE_PROTON, VITESSE_LUMIERE
//    -> Ou en camelCase avec un préfixe : kVitesseLumiere (style Geant4)
//
// =============================================================================

// =============================================================================
//  SECTION 5 : LES OPÉRATEURS DE BASE
// =============================================================================
//
//  Operateur   | Symbole | Exemple       | Resultat
//  ------------|---------|---------------|---------------------------
//  Addition    |    +    | 5 + 3         | 8
//  Soustract.  |    -    | 10 - 4        | 6
//  Multiplic.  |    *    | 6 * 7         | 42
//  Division    |    /    | 15 / 4        | 3  (entier!) <- PIEGE !
//  Modulo      |    %    | 15 % 4        | 3  (reste de la division)
//
//  LE GRAND PIÈGE DE LA DIVISION ENTIÈRE :
//  ----------------------------------------
//  En C++, si on divise deux 'int', le résultat est un 'int'
//  -> La partie décimale est TRONQUÉE (pas arrondie, tronquée !)
//
//  Exemple :
//    int a = 7 ;
//    int b = 2 ;
//    int resultat = a / b ;  // resultat = 3  (pas 3.5 !)
//
//  Pour obtenir 3.5, il faut utiliser des 'double' :
//    double a = 7.0 ;
//    double b = 2.0 ;
//    double resultat = a / b ;  // resultat = 3.5  OK
//
//  Ou forcer la conversion (cast) :
//    int a = 7 ;
//    int b = 2 ;
//    double resultat = (double)a / (double)b ;  // = 3.5 OK
//
//  LE MODULO (%) :
//  ---------------
//  Le modulo donne le RESTE de la division entière.
//  Analogie : si tu distribues 17 bonbons à 5 enfants, chacun reçoit 3
//  bonbons (17 / 5 = 3) et il en reste 2 (17 % 5 = 2).
//
//  Utilisation en programmation : vérifier si un nombre est pair ou impair
//    Si (n % 2 == 0) -> n est pair
//    Si (n % 2 != 0) -> n est impair
//
// =============================================================================

// =============================================================================
//  SECTION 6 : LIEN AVEC GEANT4
// =============================================================================
//
//  En Geant4, les mêmes types C++ sont utilisés partout !
//  Voici quelques exemples réels tirés du code source de Geant4 :
//
//  TYPE 'double' (ou G4double qui est un alias de double) :
//  ---------------------------------------------------------
//    G4double energie       = 100.0 * MeV ;  // Énergie d'un proton
//    G4double position_x    = 0.5 * cm ;     // Position en X
//    G4double masse_proton  = 938.272 * MeV; // Masse du proton
//    G4double angle_theta   = 45.0 * deg ;   // Angle en degrés
//    G4double longueur_step = 0.1 * mm ;     // Longueur d'un pas de calcul
//
//  TYPE 'int' (ou G4int) :
//  -----------------------
//    G4int nb_evenements    = 1000 ;     // Nombre d'événements à simuler
//    G4int nb_particules    = 50 ;       // Nombre de particules secondaires
//    G4int numero_run       = 1 ;        // Numéro du Run
//    G4int z_proton         = 1 ;        // Numéro atomique Z du proton
//    G4int a_carbone        = 12 ;       // Nombre de masse A du carbone
//
//  TYPE 'bool' (ou G4bool) :
//  -------------------------
//    G4bool visualisation_active = true ;  // Afficher ou non la géométrie
//    G4bool particule_chargee    = true ;  // La particule est-elle chargée ?
//    G4bool sortie_du_monde      = false ; // La particule est-elle sortie ?
//
//  TYPE 'std::string' (ou G4String) :
//  -----------------------------------
//    G4String nom_particule  = "proton" ;
//    G4String nom_materiau   = "G4_WATER" ;
//    G4String nom_volume     = "DetecteurPrincipal" ;
//    G4String nom_processus  = "phot" ;  // Effet photoélectrique
//
//  CONCLUSION :
//  Maîtriser ces types C++ de base, c'est maîtriser les fondations de Geant4 !
//  Chaque simulation commence par déclarer des variables avec ces types.
//
// =============================================================================


// =============================================================================
//  PROGRAMME PRINCIPAL : main()
//  La fonction main() est le point d'entrée de tout programme C++.
//  L'ordinateur commence TOUJOURS par exécuter ce qui est dans main().
// =============================================================================

int main()
{
    // =========================================================================
    //  AFFICHAGE D'UN EN-TÊTE pour rendre la sortie lisible
    // =========================================================================

    // std::cout = "standard character output" = affichage dans le terminal
    // <<  = l'opérateur d'insertion, envoie des données vers cout
    // std::endl = fin de ligne (comme appuyer sur Entrée) + vide le tampon
    // "\n" est une alternative plus rapide à std::endl (sans vider le tampon)

    std::cout << "======================================================" << std::endl;
    std::cout << "  COURS C++ - 01 : VARIABLES ET TYPES" << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << std::endl; // Ligne vide pour aérer l'affichage


    // =========================================================================
    //  DÉMONSTRATION 1 : Déclaration et initialisation des types de base
    // =========================================================================

    std::cout << "--- SECTION 1 : Les types de base ---" << std::endl;

    // --- Type 'int' (entier) ---
    // Syntaxe : int nom = valeur ;
    int nombreDeParticules = 1000;      // Un entier positif
    int temperature_celsius = -273;     // Les entiers peuvent être négatifs
    int code_retour = 0;                // Souvent utilisé pour les codes d'erreur

    std::cout << "int nombreDeParticules = " << nombreDeParticules << std::endl;
    std::cout << "int temperature_celsius = " << temperature_celsius << std::endl;
    std::cout << "int code_retour = " << code_retour << std::endl;
    std::cout << std::endl;

    // --- Type 'double' (décimal haute précision) ---
    // Le suffixe de valeur n'est PAS nécessaire (3.14 est déjà un double par défaut)
    // Notez la notation scientifique possible : 1.6e-19 = 1.6 x 10^(-19)
    double energie_MeV = 100.0;            // Énergie d'un proton en MeV
    double charge_electron = -1.602e-19;   // Charge de l'électron en Coulombs
    double pi = 3.14159265358979;          // Approximation de Pi
    double position_x_mm = 0.5;           // Position en millimètres

    std::cout << "double energie_MeV = " << energie_MeV << " MeV" << std::endl;
    std::cout << "double charge_electron = " << charge_electron << " C" << std::endl;
    std::cout << "double pi = " << pi << std::endl;
    std::cout << "double position_x_mm = " << position_x_mm << " mm" << std::endl;
    std::cout << std::endl;

    // --- Type 'float' (décimal simple précision) ---
    // ATTENTION : Le suffixe 'f' est recommandé pour les littéraux float !
    // Sans 'f', la valeur 3.14 serait d'abord un 'double', puis convertie
    // en float avec une possible perte de précision.
    float valeur_approchee = 3.14f;       // Le 'f' final indique que c'est un float
    float longueur_cm = 10.5f;

    std::cout << "float valeur_approchee = " << valeur_approchee << std::endl;
    std::cout << "float longueur_cm = " << longueur_cm << " cm" << std::endl;
    std::cout << std::endl;

    // --- Type 'char' (un seul caractère) ---
    // ATTENTION : Toujours entre APOSTROPHES simples '' (et non guillemets "")
    // Les guillemets "" sont réservés aux std::string !
    char premiere_lettre = 'G';    // La lettre G (comme Geant4 !)
    char chiffre_char = '4';       // Le chiffre 4 en tant que caractère
    char symbole = '+';            // Un symbole

    std::cout << "char premiere_lettre = " << premiere_lettre << std::endl;
    std::cout << "char chiffre_char = " << chiffre_char << std::endl;
    std::cout << "char symbole = " << symbole << std::endl;
    std::cout << std::endl;

    // --- Type 'bool' (booléen : vrai ou faux) ---
    // Un bool ne peut avoir QUE deux valeurs : true (1) ou false (0)
    // En mémoire, true = 1 et false = 0
    // std::cout affiche 1 pour true et 0 pour false par défaut
    bool simulation_active = true;
    bool erreur_detectee = false;
    bool particule_chargee = true;    // Un proton est chargé positivement

    std::cout << "bool simulation_active = " << simulation_active
              << "  (true = 1, false = 0)" << std::endl;
    std::cout << "bool erreur_detectee = " << erreur_detectee << std::endl;
    std::cout << "bool particule_chargee = " << particule_chargee << std::endl;

    // Pour afficher "true"/"false" au lieu de "1"/"0", utiliser std::boolalpha
    std::cout << std::boolalpha; // Active l'affichage textuel des booléens
    std::cout << "bool erreur_detectee (avec boolalpha) = "
              << erreur_detectee << std::endl;
    std::cout << std::noboolalpha; // Désactiver pour revenir au mode normal
    std::cout << std::endl;

    // --- Type 'std::string' (chaîne de caractères) ---
    // ATTENTION : Toujours entre GUILLEMETS DOUBLES ""
    // std::string nécessite #include <string>
    std::string nom_particule = "proton";
    std::string nom_materiau = "G4_WATER";    // Style Geant4 pour les matériaux
    std::string message = "Bonjour Geant4 !";

    std::cout << "std::string nom_particule = " << nom_particule << std::endl;
    std::cout << "std::string nom_materiau = " << nom_materiau << std::endl;
    std::cout << "std::string message = " << message << std::endl;
    std::cout << std::endl;


    // =========================================================================
    //  DÉMONSTRATION 2 : Le mot-clé 'const'
    // =========================================================================

    std::cout << "--- SECTION 2 : Le mot-cle 'const' ---" << std::endl;

    // Les constantes physiques fondamentales -> parfaites pour 'const' !
    // Une fois définies, elles ne changeront JAMAIS pendant l'exécution.
    const double PI = 3.14159265358979323846;
    const double VITESSE_LUMIERE_M_S = 2.99792458e8;   // En mètres par seconde
    const double MASSE_PROTON_MEV = 938.272046;         // En MeV/c²
    const double MASSE_ELECTRON_MEV = 0.510998950;      // En MeV/c²
    const int    NOMBRE_AVOGADRO_EXP = 23;              // L'exposant de 6.022x10^23
    const std::string NOM_SIMULATION = "SimulationProton_v1";

    std::cout << "const double PI = " << PI << std::endl;
    std::cout << "const double VITESSE_LUMIERE = "
              << VITESSE_LUMIERE_M_S << " m/s" << std::endl;
    std::cout << "const double MASSE_PROTON = "
              << MASSE_PROTON_MEV << " MeV/c2" << std::endl;
    std::cout << "const double MASSE_ELECTRON = "
              << MASSE_ELECTRON_MEV << " MeV/c2" << std::endl;
    std::cout << "const int NOMBRE_AVOGADRO_EXP = "
              << NOMBRE_AVOGADRO_EXP << std::endl;
    std::cout << "const std::string NOM_SIMULATION = "
              << NOM_SIMULATION << std::endl;
    std::cout << std::endl;

    // Les lignes suivantes provoqueraient une ERREUR DE COMPILATION :
    // PI = 3.14 ;                  // ERREUR : assignment of read-only variable
    // MASSE_PROTON_MEV = 999.0 ;   // ERREUR : assignment of read-only variable

    std::cout << "  -> Les constantes protegent vos valeurs physiques" << std::endl;
    std::cout << "     contre les modifications accidentelles !" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    //  DÉMONSTRATION 3 : Les opérateurs de base
    // =========================================================================

    std::cout << "--- SECTION 3 : Les operateurs arithmetiques ---" << std::endl;

    int a = 17;
    int b = 5;

    // Opérateurs sur entiers (int)
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "Addition       : a + b = " << (a + b) << std::endl;
    std::cout << "Soustraction   : a - b = " << (a - b) << std::endl;
    std::cout << "Multiplication : a * b = " << (a * b) << std::endl;

    // LE GRAND PIÈGE : la division entière !
    // int / int donne un int -> la partie décimale disparaît silencieusement
    std::cout << "Division (int) : a / b = " << (a / b)
              << "  <- tronquee (pas 3.4) !" << std::endl;

    // Le modulo : reste de la division entière
    // 17 = 5 * 3 + 2, donc 17 % 5 = 2
    std::cout << "Modulo         : a % b = " << (a % b)
              << "  <- reste de 17 divise par 5" << std::endl;
    std::cout << "  Verification : 5 * 3 + 2 = " << (5*3 + 2)
              << " = 17 (OK)" << std::endl;
    std::cout << std::endl;

    // Application du modulo : vérifier si un nombre est pair ou impair
    std::cout << "Application du modulo (pair/impair) :" << std::endl;
    int test_nombre = 42;
    std::cout << "  " << test_nombre << " % 2 = " << (test_nombre % 2)
              << " -> " << test_nombre << " est pair" << std::endl;
    test_nombre = 37;
    std::cout << "  " << test_nombre << " % 2 = " << (test_nombre % 2)
              << " -> " << test_nombre << " est impair" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    //  DÉMONSTRATION 4 : Division entière vs division décimale
    // =========================================================================

    std::cout << "--- SECTION 4 : Division entiere vs decimale ---" << std::endl;

    // CAS 1 : int / int -> résultat int (partie décimale perdue !)
    int total_evenements = 7;
    int nb_lots = 2;
    int evenements_par_lot_entier = total_evenements / nb_lots;
    std::cout << "int/int : " << total_evenements << " / " << nb_lots
              << " = " << evenements_par_lot_entier
              << "  (on a perdu 0.5 !)" << std::endl;

    // CAS 2 : double / double -> résultat double (correct)
    double energie_totale = 7.0;
    double nb_particules_d = 2.0;
    double energie_par_particule = energie_totale / nb_particules_d;
    std::cout << "dbl/dbl : " << energie_totale << " / " << nb_particules_d
              << " = " << energie_par_particule
              << "  (OK)" << std::endl;

    // CAS 3 : Forcer la conversion (cast) d'int en double
    // (double)variable -> convertit temporairement la variable en double
    // La variable originale n'est PAS modifiée (elle reste un int)
    int numerateur = 7;
    int denominateur = 2;
    double resultat_force = (double)numerateur / (double)denominateur;
    std::cout << "(double)int/(double)int : (double)" << numerateur
              << " / (double)" << denominateur
              << " = " << resultat_force
              << "  (OK grace au cast)" << std::endl;

    // CAS 4 : Suffisant de caster un seul opérande
    // Quand un double est impliqué, l'autre opérande est automatiquement converti
    double resultat_semi_cast = (double)numerateur / denominateur;
    std::cout << "(double)int/int : = " << resultat_semi_cast
              << "  (OK, un seul cast suffit)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    //  DÉMONSTRATION 5 : Lien concret avec Geant4
    // =========================================================================

    std::cout << "--- SECTION 5 : Variables style Geant4 ---" << std::endl;
    std::cout << "  (En Geant4 : G4double=double, G4int=int, G4bool=bool)" << std::endl;
    std::cout << std::endl;

    // Simulation d'un faisceau de protons pour l'hadronthérapie
    // Ces variables sont typiques de ce qu'on trouve dans :
    //   - PrimaryGeneratorAction.cc  (faisceau)
    //   - DetectorConstruction.cc    (géométrie)
    //   - RunAction.cc               (gestion des runs)

    // Configuration du faisceau (données d'entrée typiques)
    int    nb_evenements_a_simuler = 10000;   // G4int en Geant4
    double energie_faisceau_MeV   = 160.0;    // G4double : 160 MeV (hadronthérapie)
    double longueur_detecteur_cm  = 30.0;     // G4double : 30 cm de longueur
    double rayon_detecteur_cm     = 5.0;      // G4double : rayon 5 cm
    bool   visualisation_on       = false;    // G4bool : pas de visu (mode batch)
    std::string nom_fichier_sortie = "resultats_proton160MeV.root"; // G4String

    // Calculs dérivés (typiques dans DetectorConstruction)
    double volume_detecteur_cm3 = PI * rayon_detecteur_cm * rayon_detecteur_cm
                                  * longueur_detecteur_cm;

    // Énergie totale maximale possible si toute l'énergie est déposée
    double energie_totale_deposee_MeV = energie_faisceau_MeV * nb_evenements_a_simuler;

    // Affichage du récapitulatif de la simulation (style log Geant4)
    std::cout << "  === CONFIGURATION DE LA SIMULATION ===" << std::endl;
    std::cout << "  Particule       : proton" << std::endl;
    std::cout << "  Energie faisceau: " << energie_faisceau_MeV << " MeV" << std::endl;
    std::cout << "  Nb evenements   : " << nb_evenements_a_simuler << std::endl;
    std::cout << "  Detecteur L     : " << longueur_detecteur_cm << " cm" << std::endl;
    std::cout << "  Detecteur R     : " << rayon_detecteur_cm << " cm" << std::endl;
    std::cout << "  Volume          : " << volume_detecteur_cm3 << " cm3" << std::endl;
    std::cout << "  Visualisation   : ";
    std::cout << std::boolalpha << visualisation_on << std::noboolalpha << std::endl;
    std::cout << "  Fichier sortie  : " << nom_fichier_sortie << std::endl;
    std::cout << "  Energie max tot : " << energie_totale_deposee_MeV
              << " MeV" << std::endl;
    std::cout << std::endl;

    // Utilisation des constantes physiques définies plus haut
    // Rapport de masse proton / électron : un résultat célèbre en physique !
    double rapport_masse = MASSE_PROTON_MEV / MASSE_ELECTRON_MEV;
    std::cout << "  Rapport masse proton/electron = " << rapport_masse << std::endl;
    std::cout << "  -> Un proton est ~" << (int)rapport_masse
              << " fois plus lourd qu'un electron" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    //  DÉMONSTRATION 6 : std::cin — Lecture d'une valeur au clavier
    // =========================================================================

    std::cout << "--- SECTION 6 : Lire une valeur avec std::cin ---" << std::endl;
    std::cout << std::endl;

    // std::cin = "standard character input" = lecture depuis le clavier
    // >> = l'opérateur d'extraction, récupère les données depuis cin
    // Le programme se met EN PAUSE et attend que l'utilisateur appuie sur Entrée

    std::cout << "  Entrez une energie en MeV pour votre simulation : ";

    double energie_utilisateur = 0.0; // Initialisation à 0 avant lecture !
    std::cin >> energie_utilisateur;  // Attend que l'utilisateur entre un nombre

    // Affichage de ce que l'utilisateur a entré
    std::cout << std::endl;
    std::cout << "  Vous avez entre : " << energie_utilisateur << " MeV" << std::endl;

    // Calcul simple avec la valeur lue
    // Estimation très grossière de la profondeur du pic de Bragg
    // (règle empirique approximative pour des protons dans l'eau)
    double profondeur_bragg_cm = energie_utilisateur / 5.5;
    std::cout << "  Profondeur de Bragg approximative : "
              << profondeur_bragg_cm << " cm" << std::endl;
    std::cout << "  (Attention : c'est une estimation tres grossiere !)" << std::endl;
    std::cout << std::endl;

    // ATTENTION avec std::cin :
    //  - Si l'utilisateur entre du texte alors qu'on attend un nombre,
    //    le flux cin est en état d'erreur et les lectures suivantes échouent.
    //  - En production (code Geant4 réel), on lit les paramètres via des
    //    fichiers macro (.mac) et non via cin. Mais cin est utile pour apprendre.
    //  - Exemple de fichier .mac Geant4 :
    //      /run/beamOn 10000
    //      /gun/energy 160 MeV
    //      /gun/particle proton


    // =========================================================================
    //  RÉCAPITULATIF FINAL
    // =========================================================================

    std::cout << "======================================================" << std::endl;
    std::cout << "  RECAPITULATIF DES POINTS CLES" << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << "  1. Une variable = une boite nommee en memoire" << std::endl;
    std::cout << "  2. Toujours initialiser ses variables !" << std::endl;
    std::cout << "  3. int pour les entiers, double pour les decimaux" << std::endl;
    std::cout << "  4. En Geant4 : preferez double (G4double) a float" << std::endl;
    std::cout << "  5. const protege vos constantes physiques" << std::endl;
    std::cout << "  6. int/int = division entiere -> piege classique !" << std::endl;
    std::cout << "  7. Le modulo % donne le reste de la division entiere" << std::endl;
    std::cout << "  8. G4double, G4int, G4bool = alias Geant4 de double, int, bool" << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "  -> Prochain cours : 02_structures_de_controle.cpp" << std::endl;
    std::cout << "     (if/else, for, while, switch)" << std::endl;
    std::cout << std::endl;

    // La fonction main() doit retourner un entier.
    // Par convention, 0 signifie "tout s'est bien passé".
    // Un code différent de 0 indique une erreur au système d'exploitation.
    return 0;

} // fin de main()

// =============================================================================
//  FIN DU FICHIER 01_variables_et_types.cpp
// =============================================================================
//
//  EXERCICES SUGGERES :
//  --------------------
//  1. Déclarez une variable 'double' pour stocker la masse du neutron
//     (939.565 MeV/c²) en tant que constante. Calculez et affichez
//     la différence de masse neutron - proton en MeV.
//
//  2. Demandez à l'utilisateur d'entrer un nombre d'événements (int),
//     puis vérifiez avec le modulo s'il est pair ou impair.
//
//  3. Essayez d'écrire : float energie = 3.14159265358979323846 ;
//     Affichez le résultat. Que remarquez-vous ? (Perte de précision !)
//
//  4. Calculez l'énergie cinétique E = 0.5 * m * v² pour :
//     - m = 938 MeV (masse proton), v = 0.9 * vitesse_lumiere
//     - Faites attention aux unités !
//
//  5. Tentez de compiler avec la ligne : PI = 3.14 ;
//     Lisez attentivement le message d'erreur du compilateur.
//
// =============================================================================
