#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#define SAFE_INT 1000000000
#define TOTAL_TESTS 25

int main() {
    std::cout << std::left << std::setw(10) << "Test" 
              << std::setw(15) << "Optimal (Ref)" 
              << std::setw(15) << "Greedy (Out)" 
              << "Error %" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 1; i <= TOTAL_TESTS; i++) {
        std::string id = (i < 10 ? "0" : "") + std::to_string(i);
        
        std::string ref_path = std::string(TEST_REF_DIR) + "test" + id + ".ref";
        std::string out_path = std::string(TEST_OUT_DIR) + "test" + id + ".out";

        std::ifstream fref(ref_path);
        std::ifstream fout(out_path);

        // If files don't exist (N was too large for ref), skip
        if (!fref || !fout) {
            continue; 
        }

        long long optimal, greedy;
        if (!(fref >> optimal) || !(fout >> greedy)) continue;

        std::cout << std::left << std::setw(10) << ("test" + id);
        
        // Handle Disconnected / Infinity
        if (optimal >= SAFE_INT) {
            std::cout << std::setw(15) << "INF" 
                      << std::setw(15) << (greedy >= SAFE_INT ? "INF" : std::to_string(greedy))
                      << "N/A (Disconnected)" << std::endl;
        } else if (greedy >= SAFE_INT) {
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
