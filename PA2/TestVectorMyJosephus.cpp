#include "VectorMyJosephus.h"
#include "readCSV.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::ofstream log("results_vector.log");
    std::vector<std::string> allDestinations = readCSV("destinations-1.csv");

    std::cout << "Loaded " << allDestinations.size() << " destinations from CSV.\n";

    if (allDestinations.empty()) {
        std::cerr << "CSV read failed.\n";
        return 1;
    }

    std::vector<long long> timings;
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int N = 1; N <= 1025; ++N) {
        if (N > allDestinations.size()) {
            std::cerr << "N exceeds available destinations. Breaking at N = " << N << "\n";
            break;
        }

        int M = rand() % N + 1;

        std::vector<std::string> subset(allDestinations.begin(), allDestinations.begin() + N);
        VectorMyJosephus game(M, N, subset);

        std::cout << "\n--- N = " << N << ", M = " << M << " ---\n";

        auto start = std::chrono::high_resolution_clock::now();
        Destination winner = game.eliminateDestination();  
        auto end = std::chrono::high_resolution_clock::now();

        long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        timings.push_back(duration);

        log << "N=" << N << ", M=" << M << ", Time=" << duration << " us\n";
        std::cout << "Winner: " << winner.getName() << "\n";
    }

    long long total = 0;
    for (auto t : timings) total += t;

    if (!timings.empty()) {
        std::cout << "\nAverage time (vector): " << (total / timings.size()) << " us\n";
    }
}
