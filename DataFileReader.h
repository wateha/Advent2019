#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class DataFileReader {

public:
    // Type of data to read
    enum class DataType {
        INT,
        STR
    };

    // Constructor
    DataFileReader(std::string fileName, char delimiter, DataType dataType);

    // Get integer data vectors
    std::vector <std::vector <int>>* GetIntegerData();

    // Get string data vectors
    std::vector <std::vector <std::string>>* GetStringData();

private:
    // Ingteger data vector
    std::vector <std::vector <int>>* integerDataVector{};

    // String data vector
    std::vector <std::vector <std::string>>* stringDataVector{};

    // Read data from given file
    std::vector <std::string>* DataFileInput(std::string fileName);

    // Split vector of data strings to vectors of integers by given delimiter
    std::vector <std::vector <int>>* IntDataInput(std::vector <std::string>* dataString, char delimiter);

    // Split vector of data strings to vectors of strings by given delimiter
    std::vector <std::vector <std::string>>* StrDataInput(std::vector <std::string>* dataString, char delimiter);
};

