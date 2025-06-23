#include "avl_map.h"
#include "USCity.h"
#include "csv_loader.h"

#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using HRClock = std::chrono::high_resolution_clock;

template<typename F>
double time_it(F&& f) {
    auto start = HRClock::now();
    f();
    auto end = HRClock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " uszips.csv\n";
        return 1;
    }

    avl_map<std::string, USCity> my_map;
    std::map<std::string, USCity> stl_map;
    std::list<std::string> zip_list;

    try {
        load_zip_csv(argv[1], my_map, stl_map, zip_list);
    } catch (const std::exception& e) {
        std::cerr << e.what();
        return 1;
    }

    std::cout << "Loaded " << my_map.size() << " ZIP rows.\n";

    std::vector<std::string> samples(zip_list.begin(), zip_list.end());

    std::mt19937 rng(std::random_device{}());
    std::shuffle(samples.begin(), samples.end(), rng);
    if (samples.size() > 1000)
        samples.resize(1000);

    double t_avl = time_it([&] {
        for (const std::string& z : samples)
            (void)my_map.find(z);
    });

    double t_std = time_it([&] {
        for (const std::string& z : samples)
            (void)stl_map.find(z);
    });

    std::cout << "Lookup 1000 keys:\n";
    std::cout << "  avl_map : " << t_avl << " ms\n";
    std::cout << "  std::map: " << t_std << " ms\n";
}
