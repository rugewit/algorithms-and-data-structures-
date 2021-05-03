#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

#define MAX_COUNT_OF_NUMBERS 15

int main() {

    std::ofstream file ("test_numbers.txt");
    if (file.is_open()) {
        for(int i = 0;i < MAX_COUNT_OF_NUMBERS; i++) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1,100); // distribution in range [1, 6]
            file << dist6(rng) << " ";
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file";
    }

    return 0;
}
