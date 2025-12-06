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
    std::vector<std::vector<long>> matrix;
    std::vector<std::string> operations;

    std::string line;
    while (std::getline(file, line)) {
        auto parts = split(line, ' ');

        if (parts[0] == "+" || parts[0] == "*") {
            for (auto part : parts) {
                if (part.empty()) {
                    continue;
                }
                operations.push_back(part);
            }

            for (auto i = 0; i < operations.size(); ++i) {
                long result = matrix[0][i];
                for (auto j = 1; j < matrix.size(); ++j) {
                    if (operations[i] == "+") {
                        result += matrix[j][i];
                    }
                    if (operations[i] == "*") {
                        result *= matrix[j][i];
                    }
                }

                sum += result;
            }

            return;
        }

        std::vector<long> row;
        for (auto part: parts) {
            if (part.empty()) {
                continue;
            }
            row.push_back(stol(part));
        }
        matrix.push_back(row);
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: homework <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
