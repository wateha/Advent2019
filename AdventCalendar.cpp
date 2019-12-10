#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "OpCodeHandler.h"

// File input
std::vector <int> IntDataFileInput(char*);

int main(int argc, char* argv[]) {

    // Input OpCode program
	std::vector<int> vectorDataInput = IntDataFileInput(argv[1]);
	
	size_t index = 0;
	OpCodeHandler opCodeHandler(vectorDataInput);
    if (argc > 2) {
        opCodeHandler.SetOpCodeInput(std::stoi(argv[2]));
    }

	do { 
		index = opCodeHandler.OpCodeInstruction(index);
	} while (index > 0);
	
	std::cout << opCodeHandler.GetOpCodeResult() << std::endl;
 }


// Read input file and load to vector
std::vector <int> IntDataFileInput(char* fileName) {
    // Read file input
	std::ifstream inputDataFile;
	std::vector<int> dataInputVector{};
    int dataCounter = 0;

    // Get data input
    inputDataFile.open(fileName);
    while (inputDataFile.eof() == 0) {
        int data;
        inputDataFile >> data;
        dataInputVector.push_back(data);
        //cout << dataInputVector[dataCounter] << endl;
        dataCounter++;
    }
    inputDataFile.close();

    return dataInputVector;
}