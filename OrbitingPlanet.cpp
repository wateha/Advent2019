#include "OrbitingPlanet.h"

OrbitingPlanet::OrbitingPlanet(std::string planetId) {
    planetID = planetId;
}

void OrbitingPlanet::AddSatellite(OrbitingPlanet* satellite) {
    satellites.push_back(satellite);
}

void OrbitingPlanet::SetCentre(OrbitingPlanet* centre) {
    centrePlanet = centre;
}

OrbitingPlanet* OrbitingPlanet::GetCentrePlanet() {
    return centrePlanet;
}

std::string OrbitingPlanet::GetPlanetID(){
    return planetID;
}

int OrbitingPlanet::GetDistance() {
    return distance;
}

void OrbitingPlanet::SetDistance(int dist) {
    distance = dist;
}