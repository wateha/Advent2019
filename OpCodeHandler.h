#pragma once
#include <vector>
#include <iostream>
#include <fstream>

/* OpCode
* Program reads from data vector intDataInput, then processes the whole program, starting at intDataInput[0].
* OpCode values:
*   01:  Read values under parameters +1 and +2, ADD them together then store the result under parameter +3;
*   02:  Read values under parameters +1 and +2, MULTIPLY them together then store the result under parameter +3;
*   03:  Take input value and store it under parameter +1;
*   04:  Output the value form the parameter +1;
*   05:  If the value under parameter +1 is NON-ZERO, return new index value form under paramter +2; otherwise do notihing;
*   06:  If the value under parameter +1 is ZERO, return new index value form under paramter +2; otherwise do notihing;
*   07:  If the value under parameter +1 is LESS THAN the value under parameter +2, store 1 under parameter +3; otherwise store 0;
*   08:  If the value under parameter +1 is EQUAL the value under parameter +2, store 1 under parameter +3; otherwise store 0;
*   99: Terminate the program
*
* Parameter modes:
*   0: Position mode - parameter is interpreted as an address to read/store values;
*   1: Immediate mode - parameter is interpreted as a value;
*
* Data structure (up to five digits):
*  +3 +2 +1  O  P   ||   OP - OpCode (e.g. 02, multiplication);
*      1  0  0  2   ||   +1, +2, +3 - Parameter modes (e.g. 0 1 0 - +3 is missing and therefore interpreted as 0);
*   <--------
*   read right to left
*/

class OpCodeHandler
{
public:
    OpCodeHandler(std::vector<int> inputVector) { SetOpCodeDataStream(inputVector); };
    OpCodeHandler() {};
    // Set program data stream
    void SetOpCodeDataStream(std::vector<int> dataStream) { opCodeProgram.clear();  opCodeProgram = dataStream; };
    
    void ReturnTable() {
        // Read file input
        std::ofstream inputDataFile{};
        // Get data input
        if (!inputDataFile.is_open()) {
            inputDataFile.open("programOut.txt", std::ofstream::app);
        }
        inputDataFile << "Program table:\n";
        //std::cout << "Program table:\n";
        for (int i = 0; i < opCodeProgram.size(); i++) {
            inputDataFile << opCodeProgram[i] << ", ";
        }
        inputDataFile << "\n";
        inputDataFile.close();
    }

    // Run program with given inputs and data stream
    bool RunOpCodeProgramOnStream(std::vector<int> dataStream, std::vector<int> inputVector) {
        SetOpCodeDataStream(dataStream);
        SetOpCodeInput(inputVector);
        int index = 0;
        do {
            index = OpCodeInstruction(index);
        } while (index > 0);

        return true;
    }

    bool RunOpCodeProgram(std::vector<int> inputVector) {
        SetOpCodeInput(inputVector);
        int index = 0;
        do {
            index = OpCodeInstruction(index);
        } while (index > 0);

        return true;
    }

    // Execute instructions at given position; return new position
    int OpCodeInstruction(int);

    // Get program result
    int GetOpCodeResult();

    // Set program input
    void SetOpCodeInput(std::vector<int> inputVector);

    // Set program input index
    void SetOpCodeInputIndex(int index);

    bool IsOpCodeOutputReady() { return outputReady; }

private:

    bool outputReady = false;

    int programInput = 1;
    int programOutput = 0;
    int instructionTable[5] = { 0, 0, 0, 0, 0 };

    std::vector<int> opCodeProgram{};
    std::vector<int> opCodeProgramInput{};
    int opCodeInputIndex = 0;
    // Read the opcode data structure (OpCode and parameter modes)
    void OpCodeParser(int);

    // Set parameter values depending on modes
    void OpCodeCheckParameterModes(std::vector<int>&, int);

    // OpCode: 1 - ADD
    void OpCodeAdd(int, int, int, int);
    // OpCode: 2 - MULTIPLY
    void OpCodeMultiply(int, int, int, int);
    // OpCode: 3 - INPUT
    void OpCodeInput(int, int);
    // OpCode: 4 - OUTPUT
    void OpCodeOutput(int, int);
    // OpCode: 5 - JUMP_IF_TRUE
    int OpCodeJumpIfTrue(int, int, int);
    // OpCode: 6 - JUMP_IF_FALSE
    int OpCodeJumpIfFalse(int, int, int);
    // OpCode: 7 - LESS_THAN
    void OpCodeLessThan(int, int, int, int);
    // OpCode: 8 - EQUAL
    void OpCodeEqual(int, int, int, int);
};