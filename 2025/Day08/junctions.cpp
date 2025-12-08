#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cctype>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <numeric>

class DisjointSet {
    std::vector<long> parent;
    std::vector<long> sz;
public:
    explicit DisjointSet(int n) : parent(n), sz(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (sz[a] < sz[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }

    std::unordered_map<int, std::vector<int>> components() {
        std::unordered_map<int, std::vector<int>> comp;
        for (int i = 0; i < static_cast<int>(parent.size()); ++i) {
            comp[find(i)].push_back(i);
        }
        return comp;
    }
};

struct Point3D {
    long x;
    long y;
    long z;

    double distanceTo(const Point3D& other) const {
        long dx = x - other.x;
        long dy = y - other.y;
        long dz = z - other.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }
    bool operator==(const Point3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
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

void process(const char* filename, long limit) {
    std::ifstream file(filename);

    std::string line;
    std::vector<Point3D> points;

    while (std::getline(file, line)) {
        auto parts = split(line, ',');
        points.push_back({stol(parts[0]), stol(parts[1]), stol(parts[2])});
    }

    std::vector<std::tuple<double, long, long>> pairs;
    for (auto i = 0; i < points.size(); ++i) {
        for (auto j = i + 1; j < points.size(); ++j) {
            auto dist = points[i].distanceTo(points[j]);
            pairs.push_back({dist, i,j});
        }
    }

    std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
        auto [dist1, p1, p2] = a;
        auto [dist2, p3, p4] = b;
        return dist1 < dist2;
    });

    DisjointSet dsu(static_cast<int>(points.size()));

    for (auto i = 0L; i < limit; ++i) {
        auto [dist, idx1, idx2] = pairs[i];
        auto p1 = points[idx1];
        auto p2 = points[idx2];

        dsu.unite(idx1, idx2);
    }

    auto components = dsu.components();

    std::vector<size_t> sizes;
    for (const auto& [root, members] : components) {
        sizes.push_back(members.size());
    }
    std::sort(sizes.begin(), sizes.end(), std::greater<>());

    sum = 1;
    for (auto i = 0; i < 3; ++i) {
        sum *= sizes[i];
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: junctions <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename, 1000);

    std::cout << sum << '\n';
    return 0;
}
