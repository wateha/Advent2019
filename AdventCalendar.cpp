#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//#include "Orbits.h"
#include "DataFileReader.h"
#include "OpCodeHandler.h"

int main(int argc, char* argv[]) {

    DataFileReader dataFileReader(argv[1], ',', DataFileReader::DataType::INT);
    std::vector<int> inputVector = { 3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5 };//dataFileReader.GetIntegerData()[0];
   // OpCodeHandler opCode(inputVector);
    std::vector<OpCodeHandler> amplifiers{};

    int maxResult = 0;

    // AD 7 PART I
    /*
    std::vector<int> inputPhases = { 0,1,2,3,4 };
    do {
        opCode.SetOpCodeDataStream(inputVector);
        int inputValue = 0;
        for (int i = 0; i < 5; i++) {
            opCode.RunOpCodeProgramOnStream(inputVector, std::vector<int>{inputPhases[i], inputValue});
            inputValue = opCode.GetOpCodeResult();
        }
        if (maxResult < opCode.GetOpCodeResult()) {
            maxResult = opCode.GetOpCodeResult();
        }
        std::cout << "Result: " << maxResult << std::endl;
    } while (std::next_permutation(inputPhases.begin(), inputPhases.end()));
    */

    // AD 7 PART II
    std::vector<int> inputPhases = { 5,6,7,8,9 };
    
    do {
        amplifiers.clear();
        for (int i = 0; i < 5; i++) {
            OpCodeHandler* amp = new OpCodeHandler(inputVector);
            amplifiers.push_back(*amp);
        }
        std::vector<int> indexMemory = { 0,0,0,0,0 };
        int inputValue = 0;
        int cycle = 0;
        int index = 0;
        amplifiers[0].SetOpCodeDataStream(inputVector);
        do {
            int ampIndex = cycle % 5;
            index = indexMemory[ampIndex];
            amplifiers[ampIndex].SetOpCodeInput(std::vector<int>{inputPhases[ampIndex], inputValue});
            do {
                index = amplifiers[ampIndex].OpCodeInstruction(index);
            } while (!amplifiers[ampIndex].IsOpCodeOutputReady() && index > 0);
            inputValue = amplifiers[ampIndex].GetOpCodeResult();
            indexMemory[ampIndex] = index;
            amplifiers[ampIndex].ReturnTable();
            cycle++;
        } while (index > 0 || (cycle % 5) != 0);
        
        if (maxResult < amplifiers[4].GetOpCodeResult()) {
            maxResult = amplifiers[4].GetOpCodeResult();
        }
        std::cout << "Phases: ";
        for (int p = 0; p < 5; p++) {
            std::cout << inputPhases[p];
        }
        std::cout << std::endl;
        std::cout << "Result: " << maxResult << std::endl << std::endl;
    } while (std::next_permutation(inputPhases.begin(), inputPhases.end()));
    

    std::cout << "Max result: " << maxResult << std::endl;

    //Orbits orbits(*dataFileReader.GetStringData());
    //std::cout << orbits.GetSum() << std::endl;
	//std::cout << orbits.GetOrbitDifference("YOU", "SAN") << std::endl;
    return 0;
 }

