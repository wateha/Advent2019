#pragma once
#include <vector>
#include <string>

class OrbitingPlanet
{
public:
    OrbitingPlanet(std::string planet);
    
    std::string GetPlanetID();
    OrbitingPlanet* GetCentrePlanet();
    void AddSatellite(OrbitingPlanet* satellite);
    void SetCentre(OrbitingPlanet* centre);

    int GetDistance();
    void SetDistance(int dist);


private:
    int distance = -1;
    std::string planetID = "";
    OrbitingPlanet* centrePlanet;
    std::vector <OrbitingPlanet*> satellites{};
};