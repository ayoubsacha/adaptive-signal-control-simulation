#include "sensorr.h"
#include <iostream>
#include <iomanip>
#include "raylib.h"
#include <vector>

class Vehicule {
public:
    // supposons une position sur une voie (plus la valeur est petite, plus le véhicule est loin du feu)
    double obtenirPosition() const { return 0.0; }
    // supposons un état d'arrêt (vitesse proche de zéro)
    bool estArrete() const { return true; }
};


// constructeur
Capteur::Capteur(const std::string& id)
    : identifiant(id), // Ex: "capteur de nord"
    nombreVehicules(0),
    longueurFileActuelle(0), // combien de véhicules attendent au feu
    vehiculesDepuisDerniereReinitialisation(0) { // compteur pour le flux/minute
    tempsReinitialisationDerniere = GetTime(); // point de départ pour calculer le flux

    // essentielles pour l'interface graphique
    positionX = 0.0f;
    positionY = 0.0f;
    rayonDetection = 0.0f;
    directionSurveillee = "";
}

// détecte un véhicule qui passe
void Capteur::detecterVehicule() {
    nombreVehicules++; // statistiques globales
    vehiculesDepuisDerniereReinitialisation++; // statistiques temps réel (flux)
}

double Capteur::obtenirFluxTrafic() const {
    // récupère le temps écoulé depuis le début du programme
    double maintenant = GetTime();

    // Calcule la durée directement en double (temps actuel - temps de la dernière réinitialisation)
    double tempsEcoule = maintenant - tempsReinitialisationDerniere;

    // Utiliser un seuil très faible au lieu de zéro pour éviter une division par zéro si GetTime() est très précis
    if (tempsEcoule < 0.0001) {
        return 0.0;
    }

    // (Véhicules passés / Temps écoulé en secondes) * 60 = Véhicules/minute
    double fluxParSeconde = static_cast<double>(vehiculesDepuisDerniereReinitialisation) / tempsEcoule;
    return fluxParSeconde * 60.0;
}

// réinitialise les statistiques de flux
void Capteur::reinitialiser() {
    // enregistre le temps actuel comme nouveau point de départ
    tempsReinitialisationDerniere = GetTime();
    vehiculesDepuisDerniereReinitialisation = 0;
}

void Capteur::calculerLongueurFile(const std::vector<Vehicule*>& listeVehicules) {
    int file = 0;
    const double POSITION_FEU = 5.0;         // Position du feu (ex: 5 mètres de la fin de la voie)
    const double LONGUEUR_ZONE_FILE = 80.0;  // On considère une file jusqu'à 80 mètres en amont du feu

    // Position minimale à partir de laquelle on commence à compter (POSITION_FEU - LONGUEUR_ZONE_FILE)
    const double POSITION_DEBUT_FILE = POSITION_FEU - LONGUEUR_ZONE_FILE;

    // Parcourir tous les véhicules dans la liste reçue
    for (const auto& vehicule : listeVehicules) {
        double position = vehicule->obtenirPosition();

        // cas1:le véhicule est dans la zone d'attente (entre POSITION_DEBUT_FILE et POSITION_FEU)
        if (position >= POSITION_DEBUT_FILE && position < POSITION_FEU) {

            // cas2:le véhicule est à l'arrêt (en file)
            if (vehicule->estArrete()) {
                file++;
            }
        }
    }

    // met à jour la variable interne du capteur avec le résultat
    mettreAJourFile(file);
}

// met à jour la longueur de la file d'attente
void Capteur::mettreAJourFile(int longueurFile) {
    if (longueurFile >= 0) {
        longueurFileActuelle = longueurFile; // mise à jour de la variable interne
    }
}

int Capteur::obtenirLongueurFile() const {
    return longueurFileActuelle; // retourne le nombre de véhicules en attente
}

// vérifie s'il y a un embouteillage
bool Capteur::estEmbouteillage() const {
    return longueurFileActuelle >= SEUIL_EMBOUTEILLAGE;
}

// détermine le niveau de trafic
std::string Capteur::obtenirNiveauTrafic() const {
    if (estEmbouteillage()) {
        return "EMBOUTEILLAGE";
    }
    else if (longueurFileActuelle >= SEUIL_TRAFIC_ELEVE) {
        return "ELEVE";
    }
    else if (longueurFileActuelle >= SEUIL_TRAFIC_FAIBLE) {
        return "MOYEN";
    }
    else {
        return "FAIBLE";
    }
}

// Obtient le nombre total de véhicules détectés
int Capteur::obtenirNombreTotalVehicules() const {
    return nombreVehicules;
}


// obtient l'identifiant du capteur
std::string Capteur::obtenirIdentifiant() const {
    return identifiant;
}

// Affiche l'état du capteur
void Capteur::afficherEtat() const {
    std::cout << "=== Capteur: " << identifiant << " ===" << std::endl;
    std::cout << "  Véhicules total: " << nombreVehicules << std::endl;
    std::cout << "  File d'attente: " << longueurFileActuelle << " véhicules" << std::endl;
    std::cout << "  Flux: " << std::fixed << std::setprecision(1)
        << obtenirFluxTrafic() << " véh/min" << std::endl;
    std::cout << "  Niveau: " << obtenirNiveauTrafic() << std::endl;
    std::cout << std::endl;
}