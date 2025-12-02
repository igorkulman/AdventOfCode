#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

long sum = 0;

std::vector<std::string> split(const std::string& line, const char separator) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, separator)) {
        parts.push_back(item);
    }
    return parts;
}

void process(const std::string& input) {
    auto ranges = split(input, ',');

    for (const auto& range : ranges) {
        auto bond = split(range, '-');
        auto start = std::stol(bond[0]);
        auto end = std::stol(bond[1]);

        for (long i = start; i<=end; ++i) {
            auto str = std::to_string(i);
            if (str.length() % 2 == 1) {
                continue;
            }

            if (str.substr(0, str.length()/2) == str.substr(str.length()/2)) {
                sum += i;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ranges <filename>\n";
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
