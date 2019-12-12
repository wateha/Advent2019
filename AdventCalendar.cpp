#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Orbits.h"
#include "DataFileReader.h"

int main(int argc, char* argv[]) {

    DataFileReader dataFileReader(argv[1], ')', 's');

    Orbits orbits(dataFileReader.GetStringData());
    
    std::cout << orbits.GetSum() << std::endl;
	
 }