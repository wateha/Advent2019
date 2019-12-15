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
    const std::vector <std::vector <int>>& GetIntegerData();

    // Get string data vectors
    const std::vector <std::vector <std::string>>& GetStringData();

private:
    // Raw data input from file
    std::vector<std::string> dataInputVector{};

    // Ingteger data vector
    std::vector <std::vector <int>> integerDataVector{};

    // String data vector
    std::vector <std::vector <std::string>> stringDataVector{};

    // Read data from given file
    void DataFileInput(std::string fileName);

    // Split vector of data strings to vectors of integers by given delimiter
    void IntDataInput(char delimiter);

    // Split vector of data strings to vectors of strings by given delimiter
    void StrDataInput(char delimiter);
};

