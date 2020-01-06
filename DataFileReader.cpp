#include "DataFileReader.h"

DataFileReader::DataFileReader(std::string fileName, char delimiter, DataType dataType) {
    // Read data file
    DataFileInput(fileName);
    
    // Parse data streams as selected data type with delimiter
    switch (dataType) {
    case DataType::INT:
        IntDataInput(delimiter);
        break;
    case DataType::STR:
        StrDataInput(delimiter);
        break;
    case DataType::FLOAT:
        FloatDataInput(delimiter);
        break;
    default:
        break;
    }
}

// Read input file and load to vector
void DataFileReader::DataFileInput(std::string fileName) {

    // Read file input
    std::ifstream inputDataFile;

    // Get data input
    inputDataFile.open(fileName);
    while (inputDataFile.eof() == 0) {
        std::string data;
        inputDataFile >> data;
        dataInputVector.push_back(data);
    }
    inputDataFile.close();
}

// Split input data to integers
void DataFileReader::IntDataInput(char delimiter) {
    for (size_t dataStringCounter = 0; dataStringCounter < dataInputVector.size(); dataStringCounter++) {
        size_t pos = 0;
        std::vector <int> dataVector;
        while ((pos = dataInputVector[dataStringCounter].find(delimiter)) != std::string::npos) {
            int data = std::stoi(dataInputVector[dataStringCounter].substr(0, pos));
            dataVector.push_back(data);
            dataInputVector[dataStringCounter].erase(0, pos + 1);
        }
        integerDataVector.push_back(dataVector);
    }
}

// Split input data to strings
void DataFileReader::StrDataInput(char delimiter) {
    for (size_t dataStringCounter = 0; dataStringCounter < dataInputVector.size(); dataStringCounter++) {
        size_t pos = 0;
        std::vector <std::string> dataVector;
        while (true) {
            pos = dataInputVector[dataStringCounter].find(delimiter);
            std::string data = dataInputVector[dataStringCounter].substr(0, pos);
            dataVector.push_back(data);
            dataInputVector[dataStringCounter].erase(0, pos + 1);
            if (pos == std::string::npos) {
                break;
            }
        }
        stringDataVector.push_back(dataVector);
    }
}

// Split input data to floats
void DataFileReader::FloatDataInput(char delimiter) {
    for (size_t dataStringCounter = 0; dataStringCounter < dataInputVector.size(); dataStringCounter++) {
        size_t pos = 0;
        std::vector <float> dataVector;
        while ((pos = dataInputVector[dataStringCounter].find(delimiter)) != std::string::npos) {
            float data = std::stof(dataInputVector[dataStringCounter].substr(0, pos));
            dataVector.push_back(data);
            dataInputVector[dataStringCounter].erase(0, pos + 1);
        }
        floatDataVector.push_back(dataVector);
    }
}

// Integer data access
const std::vector <std::vector <int>>& DataFileReader::GetIntegerData() {
    return integerDataVector;
}

// String data access
const std::vector <std::vector <std::string>>& DataFileReader::GetStringData() {
    return stringDataVector;
}

// Float data access
const std::vector <std::vector <float>>& DataFileReader::GetFloatData() {
    return floatDataVector;
}