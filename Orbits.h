#pragma once
#include <string>
#include <vector>
#include "OrbitingPlanet.h"

class Orbits
{
public:
    Orbits(std::vector <std::vector <std::string>> connections);
    int GetSum();
    
private:
    void AddConnection(std::string, std::string);
    int GetPlanetWithID(std::string planet);
    void SetPlanetsPosition();
    int NextPlanet(OrbitingPlanet* planet);
    int SumInt(int x);
};

