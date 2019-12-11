#include "OpCodeHandler.h"

int programInput = 1;
int programOutput = 0;
int instructionTable[] = { 0, 0, 0, 0, 0 };

int OpCodeHandler::OpCodeInstruction(int vectorIndex) {
    OpCodeParser(opCodeProgramInput[vectorIndex]);
    int opCodeInstructionID = instructionTable[0] + 10 * instructionTable[1];
    int newIndex = 0;

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
    // std::vector<int> param = { parameterModeA, parameterModeB, parameterModeC };
    // OpCodeCheckParameterModes(param, vectorIndex);
    // opCodeProgramInput[param[0]] = opCodeProgramInput[param[1]] + opCodeProgramInput[param[2]];

    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgramInput[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    opCodeProgramInput[parameterA] = opCodeProgramInput[parameterB] + opCodeProgramInput[parameterC];

}

void OpCodeHandler::OpCodeMultiply(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgramInput[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    opCodeProgramInput[parameterA] = opCodeProgramInput[parameterB] * opCodeProgramInput[parameterC];
}

void OpCodeHandler::OpCodeInput(int vectorIndex, int parameterMode) {
    int parameter;
    parameter = parameterMode ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];
    opCodeProgramInput[parameter] = programInput;
}

void OpCodeHandler::OpCodeOutput(int vectorIndex, int parameterMode) {
    int parameter;
    parameter = parameterMode ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];
    programOutput = opCodeProgramInput[parameter];
}

int OpCodeHandler::OpCodeJumpIfTrue(int vectorIndex, int parameterModeB, int parameterModeC) {
    int parameterB, parameterC;
    int newIndex;
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    return newIndex = opCodeProgramInput[parameterC] ? opCodeProgramInput[parameterB] : (vectorIndex + 3);
}

int OpCodeHandler::OpCodeJumpIfFalse(int vectorIndex, int parameterModeB, int parameterModeC) {
    int parameterB, parameterC;
    int newIndex;
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    return newIndex = opCodeProgramInput[parameterC] ? (vectorIndex + 3) : opCodeProgramInput[parameterB];
}

void OpCodeHandler::OpCodeLessThan(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgramInput[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    opCodeProgramInput[parameterA] = (opCodeProgramInput[parameterB] > opCodeProgramInput[parameterC]) ? 1 : 0;
}

void OpCodeHandler::OpCodeEqual(int vectorIndex, int parameterModeA, int parameterModeB, int parameterModeC) {
    int parameterA, parameterB, parameterC;

    parameterA = parameterModeA ? (vectorIndex + 3) : opCodeProgramInput[vectorIndex + 3];
    parameterB = parameterModeB ? (vectorIndex + 2) : opCodeProgramInput[vectorIndex + 2];
    parameterC = parameterModeC ? (vectorIndex + 1) : opCodeProgramInput[vectorIndex + 1];

    opCodeProgramInput[parameterA] = (opCodeProgramInput[parameterB] == opCodeProgramInput[parameterC]) ? 1 : 0;
}

int OpCodeHandler::GetOpCodeResult() {
    return programOutput;
}

void OpCodeHandler::SetOpCodeInput(int input) {
    programInput = input;
}

void OpCodeHandler::OpCodeCheckParameterModes(std::vector<int>& parameters, int index) {
    for (int i = 0; i < parameters.size(); i++) {
        parameters[i] = parameters[i] ? (index + 1 + i) : opCodeProgramInput[index + 1 + i];
    }
}