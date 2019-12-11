#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "OpCodeHandler.h"
#include "DataFileReader.h"

int main(int argc, char* argv[]) {

    DataFileReader dataFileReader(argv[1], ',', 'i');
	
	size_t index = 0;
	OpCodeHandler opCodeHandler(dataFileReader.GetIntegerData()[0]);
    if (argc > 2) {
        opCodeHandler.SetOpCodeInput(std::stoi(argv[2]));
    }

	do { 
		index = opCodeHandler.OpCodeInstruction(index);
	} while (index > 0);
	
	std::cout << opCodeHandler.GetOpCodeResult() << std::endl;
 }