#include <fstream>
#include <iostream>
#include <string>

long sum = 0;

void process(std::string& line) {
    const int count = 12;
    long indices[count] = {0};

    for (auto iteration = 0; iteration < count; ++iteration) {
        int start = 0;
        if (iteration > 0) {
            start = indices[iteration - 1] + 1;
        }
        indices[iteration] = start;

        auto maxIndex = line.length() - (count - iteration - 1);
        for (auto i = indices[iteration]; i < maxIndex; i++) {
            if (line[i] > line[indices[iteration]]) {
                indices[iteration] = i;
            }
        }
    }
    long value = 0;
    for (auto j = 0; j < count; ++j) {
        value = value * 10 + (line[indices[j]] - '0');
    }
    std::cout << "Max pair: " << value << " in " << line << '\n';
    sum += value;
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
