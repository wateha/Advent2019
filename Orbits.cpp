#include "Orbits.h"

std::vector <OrbitingPlanet*> orbitingPlanets;
int sum = 0;

Orbits::Orbits(std::vector <std::vector <std::string>> connections) {

    for (int i = 0; i < connections.size(); i++) {
        AddConnection(connections[i][0], connections[i][1]);
    }

    SetPlanetsPosition();

    for (int i = 0; i < orbitingPlanets.size(); i++) {
        sum += orbitingPlanets[i]->GetDistance();
    }
}

void Orbits::AddConnection(std::string centre, std::string satellite) {
    // Check if each planet exist
    int posCentre = GetPlanetWithID(centre);
    int posSatellite = GetPlanetWithID(satellite);

    // If centre exists
    if (posCentre >= 0)
    {   // If satellite exists
        if (posSatellite >= 0) {
            // Set new connection
            orbitingPlanets[posCentre]->AddSatellite(orbitingPlanets[posSatellite]);
            orbitingPlanets[posSatellite]->SetCentre(orbitingPlanets[posCentre]);
        }
        else {
            // Create new satellite and set new connection
            OrbitingPlanet* newSatellite = new OrbitingPlanet(satellite);
            orbitingPlanets[posCentre]->AddSatellite(newSatellite);
            newSatellite->SetCentre(orbitingPlanets[posCentre]);
            orbitingPlanets.push_back(newSatellite);
        }
    }
    else {
        if (posSatellite >= 0) {
            // Create new centree and set new connection
            OrbitingPlanet* newCentre = new OrbitingPlanet(centre);
            orbitingPlanets[posSatellite]->SetCentre(newCentre);
            newCentre->AddSatellite(orbitingPlanets[posSatellite]);
            orbitingPlanets.push_back(newCentre);
        }
        else {
            // Create new planets and set new connection
            OrbitingPlanet* newCentre = new OrbitingPlanet(centre);
            OrbitingPlanet* newSatellite = new OrbitingPlanet(satellite);
            newCentre->AddSatellite(newSatellite);
            newSatellite->SetCentre(newCentre);
            orbitingPlanets.push_back(newCentre);
            orbitingPlanets.push_back(newSatellite);
        }
    }
}

int Orbits::GetPlanetWithID(std::string planet) {
    for (int i = 0; i < orbitingPlanets.size(); i++) {
        if (orbitingPlanets[i]->GetPlanetID() == planet) {
            return i;
        }
    }
    return -1;
}

void Orbits::SetPlanetsPosition() {
    for (int i = 0; i < orbitingPlanets.size(); i++) {
        if (orbitingPlanets[i]->GetDistance() < 0) {
            orbitingPlanets[i]->SetDistance(NextPlanet(orbitingPlanets[i]));
        }
    }
}

int Orbits::NextPlanet(OrbitingPlanet* planet) {
    OrbitingPlanet* next = planet->GetCentrePlanet();
    if (next != NULL) {
        planet->SetDistance(NextPlanet(next) + 1);
        return planet->GetDistance();
    }
    else {
        planet->SetDistance(0);
        return 0;
    }
}

int Orbits::SumInt(int x) {
    if (x > 0){
        return x + SumInt(x-1);
    }
    else {
        return 0;
    }
}

int Orbits::GetSum(){
    return sum;
}