#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <numeric>

struct Point2D {
    long x;
    long y;
};

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

    std::string line;
    std::vector<Point2D> points;

    while (std::getline(file, line)) {
        auto parts = split(line, ',');
        points.push_back({stol(parts[0]), stol(parts[1])});
    }

    std::vector<std::tuple<double, Point2D, Point2D>> areas;
    for (auto i = 0; i < points.size(); ++i) {
        for (auto j = i + 1; j < points.size(); ++j) {
            auto area = (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1);
            areas.push_back({area, points[i],points[j]});
        }
    }

    long max = 0;
    for (const auto& [area, p1, p2]: areas) {
        if (area > max) {
            max = area;
        }
    }
    sum = max;
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: rectangles <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
