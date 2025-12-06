#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

long sum = 0;

void process(const char* filename) {
    std::ifstream file(filename);
    std::vector<std::vector<char>> matrix;
    std::size_t max_cols = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> parts(line.begin(), line.end());
        matrix.push_back(parts);
        max_cols = std::max(max_cols, parts.size());
    }

    for (auto& row : matrix) {
        if (row.size() < max_cols) {
            row.resize(max_cols, ' ');
        }
    }

    std::vector<long> numbers;
    for (int i = static_cast<int>(matrix[0].size()) - 1; i >= 0; --i) {
        std::string number_string = "";
        for (int j = 0; j < static_cast<int>(matrix.size()) - 1; ++j) {
            if (matrix[j][i] == ' ') {
                continue;
            }
            number_string += matrix[j][i];
        }

        if (!number_string.empty()) {
            numbers.push_back(stol(number_string));
        }

        auto op = matrix[matrix.size() - 1][i];
        if (op == '*' || op == '+') {
            long result = 0;
            if (op == '*') {
                result = 1;
            }
            for (auto number: numbers) {
                if (op == '+') {
                    result += number;
                }
                if (op == '*') {
                    result *= number;
                }
            }
            sum = sum + result;
            numbers.clear();
        }
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
