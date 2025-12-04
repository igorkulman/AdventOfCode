#include <fstream>
#include <vector>
#include <string>
#include <iostream>

long sum = 0;

void process(const char* filename) {
    std::ifstream file(filename);
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> modified_grid;

    std::string line;
    while (std::getline(file, line)) {
        grid.emplace_back(line.begin(), line.end());
        modified_grid.emplace_back(line.begin(), line.end());
    }

    auto wasModified = true;

    while (wasModified) {
        grid = modified_grid;
        wasModified = false;

        for (auto j = 0; j < grid.size(); ++j) {
            for (auto i = 0; i < grid[j].size(); ++i) {
                if (grid[j][i] != '@') {
                    continue;
                }

                auto adjacentCount = 0;

                for (auto di = -1; di <= 1; ++di) {
                    for (auto dj = -1; dj <= 1; ++dj) {
                        if ((di == 0 && dj == 0) || (j + dj < 0) || (j + dj >= grid.size()) || (i + di < 0) || (i + di >= grid[j].size())) {
                            continue;
                        }

                        if (grid[j + dj][i + di] == '@') {
                            ++adjacentCount;
                        }
                    }
                }

                if (adjacentCount < 4) {
                    modified_grid[j][i] = '.';
                    wasModified = true;
                    ++sum;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: forklifts <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
