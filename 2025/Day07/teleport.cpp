#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <cctype>

long sum = 0;

void process(const char* filename) {
    std::ifstream file(filename);

    std::string line;
    std::set<long> next_pos = {};
    while (std::getline(file, line)) {
        std::vector<char> parts(line.begin(), line.end());
        std::set<long> next_next_pos = {};
        for (auto i=0; i < parts.size(); ++i) {
            if (parts[i] == 'S') {
                next_pos.insert(i);
                continue;
            }
        }

        for (auto pos: next_pos) {
            if (parts[pos] == '.' || parts[pos] == 'S') {
                next_next_pos.insert(pos);
            }
            if (parts[pos] == '^') {
                sum += 1;
                if (pos > 0) {
                    next_next_pos.insert(pos - 1);
                }
                if (pos < parts.size() - 2) {
                    next_next_pos.insert(pos + 1);
                }
            }
        }

        next_pos = next_next_pos;
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
