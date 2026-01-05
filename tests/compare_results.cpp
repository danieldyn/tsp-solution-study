#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int main() {
    std::cout << std::left << std::setw(10) << "Test" 
              << std::setw(15) << "Optimal (Ref)" 
              << std::setw(15) << "Greedy (Out)" 
              << "Error %" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 1; i <= 25; i++) {
        std::string id = (i < 10 ? "0" : "") + std::to_string(i);
        
        std::ifstream fref("ref/test" + id + ".ref");
        std::ifstream fout("out/test" + id + ".out");

        long long optimal, greedy;
        if (!(fref >> optimal) || !(fout >> greedy)) continue;

        std::cout << std::left << std::setw(10) << ("test" + id);
        
        // Handle cases where the graph is disconnected
        if (optimal >= 1000000000) {
            std::cout << std::setw(15) << "INF" 
                      << std::setw(15) << (greedy >= 1000000000 ? "INF" : std::to_string(greedy))
                      << "N/A (Disconnected)" << std::endl;
        } else if (greedy >= 1000000000) {
            std::cout << std::setw(15) << optimal 
                      << std::setw(15) << "INF" 
                      << "Greedy Failed" << std::endl;
        } else {
            double error = ((double)(greedy - optimal) / optimal) * 100.0;
            std::cout << std::setw(15) << optimal 
                      << std::setw(15) << greedy 
                      << std::fixed << std::setprecision(2) << error << "%" << std::endl;
        }
    }
    return 0;
}