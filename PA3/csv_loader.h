#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include "avl_map.h"
#include "USCity.h"
#include <fstream>
#include <list>
#include <map>

template <typename Map>
void load_zip_csv(const std::string& filename,
                  Map& dest_map,
                  std::map<std::string, USCity>& stl_map,
                  std::list<std::string>& zips)
{
    std::ifstream in(filename);
    std::string line;

    if (!in) {
        throw std::runtime_error("Cannot open CSV file");
    }

    std::getline(in, line); // skip header

    while (std::getline(in, line)) {
        auto cols = USCity::split(line);
        if (cols.empty()) continue;

        std::string zip = cols[0];
        USCity city = USCity::from_csv(cols);

        dest_map.insert(zip, city);
        stl_map.emplace(zip, city);
        zips.push_back(zip);
    }
}

#endif
