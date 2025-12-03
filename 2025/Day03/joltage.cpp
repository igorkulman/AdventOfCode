#include <fstream>
#include <iostream>
#include <string>

long sum = 0;

void process(std::string& line) {
    long max1Index = 0;
    for (auto i = max1Index; i < line.length() - 1; i++) {
        if (line[i] > line[max1Index]) {
            max1Index = i;
        }
    }
    long max2Index = max1Index +1;
    for (auto i = max2Index; i < line.length(); i++) {
        if (line[i] > line[max2Index]) {
            max2Index = i;
        }
    }
    auto max = (line[max1Index] - '0') * 10 + (line[max2Index] - '0');
    std::cout << "Max pair: " << max << " in " << line << '\n';
    sum += max;
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: joltage <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    std::ifstream in(filename);

    if (!in) {
        std::cerr << "Failed to open: " << filename << '\n';
        return 1;
    }

    std::string line;
    while (std::getline(in, line)) {
        process(line);
    }

    std::cout << sum << '\n';
    return 0;
}
