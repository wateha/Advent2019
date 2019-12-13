#pragma once
#include <string>
#include <vector>
#include "OrbitingPlanet.h"

class Orbits {

public:
    // Create vector of orbiting planets with their relative centre-satellite connections
    Orbits(std::vector <std::vector <std::string>> connections);

    // Get the sum of all orbit counts
    int GetSum();
    
private:
    // Vector containing all planets
    std::vector <OrbitingPlanet*>* orbitingPlanets{};

    // Sum of all distances
    int sum = 0;

    // Create centre-satellite connection between two planets, creating them when necessary
    void AddConnection(std::string centre, std::string satellite);

    // Find the index of the planet with provided ID in orbitingPlanets vetor
    int GetPlanetWithID(std::string planet);
    //int GetPlanetWithPredicate(bool (*getID)(OrbitingPlanet*));

    // Calculate planet's distance from innermost planet (Centre Of Mass)
    void SetPlanetsPosition();

    // Recursively calculate planet's distance and distances of all intermediary planets down the chain
    int NextPlanet(OrbitingPlanet* planet);
};

