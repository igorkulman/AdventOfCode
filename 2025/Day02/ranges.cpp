#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

long sum = 0;

std::string repeat(const std::string& input, unsigned num)
{
    std::string ret;
    ret.reserve(input.size() * num);
    while (num--)
        ret += input;
    return ret;
}

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

        for (long i = start; i<=end; i++) {
            auto str = std::to_string(i);

            for (long length = 1; length <= str.length() / 2; length++) {
                auto id = str.substr(0, length);
                auto multiplier = str.length() / length;
                auto full = repeat(id, str.length() / length);

                if (full == str) {
                    sum += i;
                    break;
                }
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
