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
        }
    }

    std::sort(ranges.begin(), ranges.end(), [](const auto& a, const auto& b) {
            const auto& [a_start, a_end] = a;
            const auto& [b_start, b_end] = b;
            return a_start < b_start;
    });

    std::vector<std::tuple<long, long>> merged_ranges;
    for (const auto& range : ranges) {
        auto [start, end] = range;

        if (merged_ranges.empty()) {
            merged_ranges.emplace_back(start, end);
            continue;
        }

        auto& [m_start, m_end] = merged_ranges.back();

        if (start <= m_end + 1) {
            m_end = std::max(m_end, end);
        } else {
            merged_ranges.emplace_back(start, end);
        }
    }

    for (const auto& range : merged_ranges) {
        auto [start, end] = range;
        sum += (end - start + 1);
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
