#include "Orbits.h"

Orbits::Orbits(std::vector <std::vector <std::string>> connections) {

    orbitingPlanets = new std::vector <OrbitingPlanet*>;

    for (int i = 0; i < connections.size(); i++) {
        AddConnection(connections[i][0], connections[i][1]);
    }

    SetPlanetsPosition();

    for (int i = 0; i < orbitingPlanets->size(); i++) {
        sum += (*orbitingPlanets)[i]->GetDistance();
    }
}

void Orbits::AddConnection(std::string centre, std::string satellite) {
    // Check if each planet exist
    int posCentre = GetPlanetWithID(centre, *orbitingPlanets);
    int posSatellite = GetPlanetWithID(satellite, *orbitingPlanets);

    // If centre exists
    if (posCentre >= 0)
    {   // If satellite exists
        if (posSatellite >= 0) {
            // Set new connection
            (*orbitingPlanets)[posCentre]->AddSatellite((*orbitingPlanets)[posSatellite]);
            (*orbitingPlanets)[posSatellite]->SetCentre((*orbitingPlanets)[posCentre]);
        }
        else {
            // Create new satellite and set new connection
            OrbitingPlanet* newSatellite = new OrbitingPlanet(satellite);
            (*orbitingPlanets)[posCentre]->AddSatellite(newSatellite);
            newSatellite->SetCentre((*orbitingPlanets)[posCentre]);
            (*orbitingPlanets).push_back(newSatellite);
        }
    }
    else {
        if (posSatellite >= 0) {
            // Create new centree and set new connection
            OrbitingPlanet* newCentre = new OrbitingPlanet(centre);
            (*orbitingPlanets)[posSatellite]->SetCentre(newCentre);
            newCentre->AddSatellite((*orbitingPlanets)[posSatellite]);
            (*orbitingPlanets).push_back(newCentre);
        }
        else {
            // Create new planets and set new connection
            OrbitingPlanet* newCentre = new OrbitingPlanet(centre);
            OrbitingPlanet* newSatellite = new OrbitingPlanet(satellite);
            newCentre->AddSatellite(newSatellite);
            newSatellite->SetCentre(newCentre);
            (*orbitingPlanets).push_back(newCentre);
            (*orbitingPlanets).push_back(newSatellite);
        }
    }
}

int Orbits::GetPlanetWithID(std::string planet, std::vector<OrbitingPlanet*> planetList) {
    for (int i = 0; i < planetList.size(); i++) {
        if (planetList[i]->GetPlanetID() == planet) {
            return i;
        }
    }
    return -1;
}

void Orbits::SetPlanetsPosition() {
    for (int i = 0; i < (*orbitingPlanets).size(); i++) {
        if ((*orbitingPlanets)[i]->GetDistance() < 0) {
            (*orbitingPlanets)[i]->SetDistance(NextPlanet((*orbitingPlanets)[i]));
        }
    }
}

int Orbits::NextPlanet(OrbitingPlanet* planet) {
    OrbitingPlanet* next = planet->GetCentrePlanet();
    if (next != nullptr) {
        if (next->GetDistance() < 0) {
            planet->SetDistance(NextPlanet(next) + 1);
        }
        else {
            planet->SetDistance(next->GetDistance() + 1);
        }
        return planet->GetDistance();
    }
    else {
        planet->SetDistance(0);
        return 0;
    }
}

int Orbits::GetSum(){
    return sum;
}

// Find distance between two planets
int Orbits::GetOrbitDifference(std::string planetA, std::string planetB){
    
    std::vector <std::string> planetTrail{};

    OrbitingPlanet *newPlanet = (*orbitingPlanets)[GetPlanetWithID(planetA, *orbitingPlanets)]->GetCentrePlanet();
    
    // Get planet trail from planet's A centre to the Centre Of Mass
    while (newPlanet != nullptr) {
        planetTrail.push_back(newPlanet->GetPlanetID());
        newPlanet = newPlanet->GetCentrePlanet();
    }

    newPlanet = (*orbitingPlanets)[GetPlanetWithID(planetB, *orbitingPlanets)]->GetCentrePlanet();
    while (newPlanet != nullptr){
        int pos = GetStringFormVector(newPlanet->GetPlanetID(), planetTrail);
        if (pos < 0) {
            planetTrail.push_back(newPlanet->GetPlanetID());
        }
        else {
            planetTrail.erase(planetTrail.begin() + pos);
        }
        newPlanet = newPlanet->GetCentrePlanet();
    }

    return planetTrail.size();
}

int Orbits::GetStringFormVector(std::string ID, std::vector<std::string> planetList) {
    for (int i = 0; i < planetList.size(); i++) {
        if (planetList[i] == ID) {
            return i;
        }
    }
    return -1;
}