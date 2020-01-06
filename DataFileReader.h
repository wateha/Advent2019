#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/* Data File Reader
* Class responsible for reading and parsing input files with data for a specific task.
* Class assumptions:
*   - the data file is text;
*   - data file consist of lines, interpreted as data streams;
*   - data inputs in single stream are separated by single character;
*   - data is either string, integer or float type;
* Data reader will read the entire file at once and store the content in vector of data streams.
* Data streams are vectors of data inputs.
*
* Example:
*   file contents:
*       1,2,3,4
*       5,6,7,8
*
*   result data output (data type: INT, delimiter: ','):
*       std::vector <<std::vector <int>> {<std::vector <int>{1, 2, 3, 4}, <std::vector <int> {5, 6, 7, 8}}
*/
class DataFileReader {

public:
    // Type of data to read
    enum class DataType {
        INT,
        STR,
        FLOAT,
    };

    // Constructor taking data file name, delimiter for data stream inputs and type of data to store
    DataFileReader(std::string fileName, char delimiter, DataType dataType);

    // Get integer data vectors
    const std::vector <std::vector <int>>& GetIntegerData();

    // Get string data vectors
    const std::vector <std::vector <std::string>>& GetStringData();

    // Get float data vectors
    const std::vector <std::vector <float>>& GetFloatData();

private:
    // Raw data input from file
    std::vector<std::string> dataInputVector{};

    // Ingteger data vector
    std::vector <std::vector <int>> integerDataVector{};

    // String data vector
    std::vector <std::vector <std::string>> stringDataVector{};

    // Float data vector
    std::vector <std::vector <float>> floatDataVector{};

    // Read data from given file
    void DataFileInput(std::string fileName);

    // Split vector of data strings to vectors of integers by given delimiter
    void IntDataInput(char delimiter);

    // Split vector of data strings to vectors of strings by given delimiter
    void StrDataInput(char delimiter);

    // Split vector of data strings to vectors of floats by given delimiter
    void FloatDataInput(char delimiter);
};

