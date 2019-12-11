#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class DataFileReader
{
public:
    DataFileReader(char*, char, char);

    // Get integer data vectors
    std::vector <std::vector <int>> GetIntegerData();
    // Get string data vectors
    std::vector <std::vector <std::string>> GetStringData();
private:

    std::vector <std::vector <int>> integerDataVector{};
    std::vector <std::vector <std::string>> stringDataVector{};

    // Read data from given file
    std::vector <std::string> DataFileInput(char*);

    // Split vector of data strings to vectors of integers by given delimiter
    std::vector <std::vector <int>> IntDataInput(std::vector <std::string>, char);

    // Split vector of data strings to vectors of strings by given delimiter
    std::vector <std::vector <std::string>> StrDataInput(std::vector <std::string>, char);
};

