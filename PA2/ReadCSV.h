#ifndef READCSV_H
#define READCSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> destinations;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return destinations;
    }

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string city;
        while (std::getline(ss, city, ';')) {  
            destinations.push_back(city);
        }
    }
    else {
        std::cerr << "Error: File is empty or unreadable.\n";
    }

    return destinations;
}

#endif
