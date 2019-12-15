#include "OpCodeHandler.h"



int OpCodeHandler::OpCodeInstruction(int vectorIndex) {
    OpCodeParser(opCodeProgram[vectorIndex]);
    int opCodeInstructionID = instructionTable[0] + 10 * instructionTable[1];
    int newIndex = 0;
    outputReady = false;
    switch (opCodeInstructionID) {
    case 1:
        OpCodeAdd(vectorIndex, instructionTable[4], instructionTable[3], instructionTable[2]);
        return vectorIndex + 4;
    case 2:
        OpCodeMultiply(vectorIndex, instructionTable[4], instructionTable[3], instructionTable[2]);
        return vectorIndex + 4;
    case 3:
        OpCodeInput(vectorIndex, instructionTable[2]);
        return vectorIndex + 2;
    case 4:
        OpCodeOutput(vectorIndex, instructionTable[2]);
        outputReady = true;
        return vectorIndex + 2;
    case 5:
        return OpCodeJumpIfTrue(vectorIndex, instructionTable[3], instructionTable[2]);
    case 6:
        return OpCodeJumpIfFalse(vectorIndex, instructionTable[3], instructionTable[2]);
    case 7:
        OpCodeLessThan(vectorIndex, instructionTable[4], instructionTable[3], instructionTable[2]);
        return vectorIndex + 4;
    case 8:
        OpCodeEqual(vectorIndex, instructionTable[4], instructionTable[3], instructionTable[2]);
        return vectorIndex + 4;
    default:
        return 0;
    }
}

void OpCodeHandler::OpCodeParser(int opCodeInstruction) {
    for (int i = 0; i < 5; i++) {
        instructionTable[i] = opCodeInstruction % 10;
        opCodeInstruction = (opCodeInstruction - instructionTable[i]) / 10;
    }
}

void OpCodeHandler::OpCodeAdd(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgram[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    opCodeProgram[parameterA] = opCodeProgram[parameterB] + opCodeProgram[parameterC];

}

void OpCodeHandler::OpCodeMultiply(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgram[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    opCodeProgram[parameterA] = opCodeProgram[parameterB] * opCodeProgram[parameterC];
}

void OpCodeHandler::OpCodeInput(int vectorIndex, int parameterMode) {
    int parameter;
    parameter = parameterMode ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];
    if (opCodeInputIndex < opCodeProgramInput.size()) {
        opCodeProgram[parameter] = opCodeProgramInput[opCodeInputIndex];
        opCodeInputIndex++;
    }
    else {
        opCodeProgram[parameter] = 0;
    }
}

void OpCodeHandler::OpCodeOutput(int vectorIndex, int parameterMode) {
    int parameter;
    parameter = parameterMode ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];
    programOutput = opCodeProgram[parameter];
}

int OpCodeHandler::OpCodeJumpIfTrue(int vectorIndex, int parameterModeB, int parameterModeC) {
    int parameterB, parameterC;
    int newIndex;
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    return newIndex = opCodeProgram[parameterC] ? opCodeProgram[parameterB] : (vectorIndex + 3);
}

int OpCodeHandler::OpCodeJumpIfFalse(int vectorIndex, int parameterModeB, int parameterModeC) {
    int parameterB, parameterC;
    int newIndex;
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    return newIndex = opCodeProgram[parameterC] ? (vectorIndex + 3) : opCodeProgram[parameterB];
}

void OpCodeHandler::OpCodeLessThan(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgram[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    opCodeProgram[parameterA] = (opCodeProgram[parameterB] > opCodeProgram[parameterC]) ? 1 : 0;
}

void OpCodeHandler::OpCodeEqual(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgram[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgram[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgram[vectorIndex + 1];

    opCodeProgram[parameterA] = (opCodeProgram[parameterB] == opCodeProgram[parameterC]) ? 1 : 0;
}

int OpCodeHandler::GetOpCodeResult() {
    return programOutput;
}

void OpCodeHandler::SetOpCodeInputIndex(int index) {
    opCodeInputIndex = index;
}

void OpCodeHandler::SetOpCodeInput(std::vector<int> inputVector) {
    opCodeProgramInput = inputVector;
    opCodeInputIndex = 0;
}

void OpCodeHandler::OpCodeCheckParameterModes(std::vector<int>& parameters, int index) {
    for (int i = 0; i < parameters.size(); i++) {
        parameters[i] = parameters[i] ? (index + 1 + i) : opCodeProgram[index + 1 + i];
    }
}