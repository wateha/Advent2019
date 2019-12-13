#pragma once
#include <vector>
#include <string>

class OrbitingPlanet {

public:
    // Constructor
    OrbitingPlanet(std::string planet);
    
    // Get planet ID code
    std::string GetPlanetID();

    // Get the planet's centre of orbit
    OrbitingPlanet* GetCentrePlanet();

    // Add planet's satellite to the satellite vector
    void AddSatellite(OrbitingPlanet* satellite);

    // Set the planet's centre of orbit
    void SetCentre(OrbitingPlanet* centre);

    // Get planet's distance (direct an intermediary orbits count) from innermost planet (Centre Of Mass)
    int GetDistance();

    //  Set planet's distance (direct an intermediary orbits count) from innermost planet (Centre Of Mass)
    void SetDistance(int dist);

private:
    // Distance from the Centre of Mass
    int distance = -1;

    // Planet's identificator
    std::string planetID = "";

    // Planet's centre of orbit
    OrbitingPlanet* centrePlanet;

    // Planet's satellites
    std::vector <OrbitingPlanet*> satellites{};
};