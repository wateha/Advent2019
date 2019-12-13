#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Orbits.h"
#include "DataFileReader.h"

int main(int argc, char* argv[]) {

    DataFileReader dataFileReader(argv[1], ')', DataFileReader::DataType::STR);

    Orbits orbits(*dataFileReader.GetStringData());
    
    std::cout << orbits.GetSum() << std::endl;
	
    return 0;
 }