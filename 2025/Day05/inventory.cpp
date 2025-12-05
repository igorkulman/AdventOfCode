#include <fstream>
#include <vector>
#include <string>
#include <iostream>
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

void process(const char* filename) {
    std::ifstream file(filename);
    std::vector<std::tuple<long, long>> ranges;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        auto parts = split(line, '-');
        if (parts.size() == 2) {
            auto start = std::stol(parts[0]);
            auto end = std::stol(parts[1]);
            ranges.push_back({start, end});
            continue;
        }

        auto number = std::stol(line);
        auto found = false;
        for (const auto& [start, end] : ranges) {
            if (number >= start && number <= end) {
                found = true;
                break;
            }
        }

        if (found) {
            sum += 1;
        }
    }

}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: inventory <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
