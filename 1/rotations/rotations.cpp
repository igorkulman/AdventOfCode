#include <fstream>
#include <iostream>
#include <string>

int position = 50;
long zeroCount = 0;

void process(std::string& line) {
    auto rotation = line[0];
    line.erase(0,1);
    auto value = stoi(line);
    if (rotation == 'L') {
        value = -value;
    }
    position = (position + 100 + value) % 100;
    if (position == 0) {
        zeroCount++;
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: rotations <filename>\n";
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

    std::cout << zeroCount << '\n';
    return 0;
}
