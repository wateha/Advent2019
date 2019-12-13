#include "DataFileReader.h"

DataFileReader::DataFileReader(std::string fileName, char delimiter, DataType dataType) {
    switch (dataType) {
    case DataType::INT:
        integerDataVector = IntDataInput(DataFileInput(fileName), delimiter);
        break;
    case DataType::STR:
        stringDataVector = StrDataInput(DataFileInput(fileName), delimiter);
        break;
    default:
        break;
    }
}

// Read input file and load to vector
std::vector<std::string>* DataFileReader::DataFileInput(std::string fileName) {

    // Read file input
    std::ifstream inputDataFile;
    std::vector<std::string>* dataInputVector = new  std::vector<std::string>();
    
    // Get data input
    inputDataFile.open(fileName);
    while (inputDataFile.eof() == 0) {
        std::string data;
        inputDataFile >> data;
        dataInputVector->push_back(data);
    }
    inputDataFile.close();

    return dataInputVector;
}

// Split input data to integers
std::vector <std::vector <int>>* DataFileReader::IntDataInput(std::vector <std::string>* dataString, char delimiter) {

    std::vector <std::vector <int>> *outputVector  = new std::vector <std::vector <int>>{};

    for (size_t dataStringCounter = 0; dataStringCounter < dataString->size(); dataStringCounter++) {
        size_t pos = 0;
        std::vector <int> dataVector;
        while ((pos= (*dataString)[dataStringCounter].find(delimiter)) != std::string::npos) {
            int data = std::stoi((*dataString)[dataStringCounter].substr(0, pos));
            dataVector.push_back(data);
            (*dataString)[dataStringCounter].erase(0, pos + 1);
        }
        outputVector -> push_back(dataVector);
    }

    return outputVector;
}

// Split input data to strings
std::vector <std::vector <std::string>>* DataFileReader::StrDataInput(std::vector <std::string>* dataString, char delimiter) {

    std::vector <std::vector <std::string>>* outputVector = new  std::vector <std::vector <std::string>>;

    for (size_t dataStringCounter = 0; dataStringCounter < dataString->size(); dataStringCounter++) {
        size_t pos = 0;
        std::vector <std::string> dataVector;
        while (true) {
            pos = (*dataString)[dataStringCounter].find(delimiter);
            std::string data = (*dataString)[dataStringCounter].substr(0, pos);
            dataVector.push_back(data);
            (*dataString)[dataStringCounter].erase(0, pos + 1);
            if (pos == std::string::npos) {
                break;
            }
        }
        outputVector -> push_back(dataVector);
    }

    return outputVector;
}

// Integer data access
std::vector <std::vector <int>>* DataFileReader::GetIntegerData() {
    return integerDataVector;
}

// String data access
std::vector <std::vector <std::string>>* DataFileReader::GetStringData() {
    return stringDataVector;
}