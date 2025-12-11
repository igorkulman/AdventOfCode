#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <map>

long sum = 0;

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
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

void process_connection(std::string start, std::vector<std::map<std::string, std::vector<std::string>>> connections) {
    if (start == "out") {
        sum++;
        return;
    }

    for (const auto& connection : connections) {
        for (const auto& [key, value] : connection) {
            if (key == start) {
                for (const auto& next : value) {
                    if (next != "you") {
                        process_connection(next, connections);
                    }
                }
            }
        }
    }
}

void process(const char* filename) {
    std::ifstream file(filename);

    std::vector<std::map<std::string, std::vector<std::string>>> connections;

    std::string line;
    while (std::getline(file, line)) {
        auto parts = split(line, ':');
        auto start = parts[0];

        auto out_parts = split(parts[1], ' ');
        std::vector<std::string> outputs;
        for (auto& out_part : out_parts) {
            trim(out_part);
            outputs.push_back(out_part);
        }
        connections.push_back({{start, outputs}});
    }

    process_connection("you", connections);
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: connections <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
