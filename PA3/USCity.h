#ifndef USCITY_H
#define USCITY_H

#include <string>
#include <sstream>
#include <vector>

struct USCity {
    std::string city;
    std::string state_id;
    std::string state_name;
    std::vector<std::string> misc;

    static std::vector<std::string> split(const std::string& line) {
        std::vector<std::string> out;
        std::string cur;
        std::istringstream ss(line);
        while (std::getline(ss, cur, ',')) {
            out.push_back(cur);
        }
        return out;
    }

    static USCity from_csv(const std::vector<std::string>& cols) {
        USCity u;
        u.city       = cols.size() > 3 ? cols[3] : "";
        u.state_id   = cols.size() > 4 ? cols[4] : "";
        u.state_name = cols.size() > 5 ? cols[5] : "";
        for (std::size_t i = 6; i < cols.size(); ++i)
            u.misc.push_back(cols[i]);
        return u;
    }

    std::string pretty() const {
        return city + ", " + state_id;
    }
};

#endif
