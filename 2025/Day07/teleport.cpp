#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cctype>

long sum = 0;

void process(const char* filename) {
    std::ifstream file(filename);

    std::string line;
    std::map<long, long> next_pos;

    long index = 0;
    while (std::getline(file, line)) {
        auto pos = line.find('S');
        if (pos != std::string::npos) {
            next_pos[pos] = 1;
            continue;
        }

        std::vector<char> parts(line.begin(), line.end());

        for (const auto [pos, count]: next_pos) {
            if (parts[pos] == '^') {
                next_pos[pos - 1] += count;
                next_pos[pos + 1] += count;
                next_pos[pos] = 0;
            }
        }
    }

    for (const auto [pos, count]: next_pos) {
        sum += count;
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: teleport <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
