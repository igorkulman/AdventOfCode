#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
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

long process_machine(const int desired_state, const std::vector<int> buttons, const int desired_state_size) {
    auto start_state = 0;
    int num_states = 1 << desired_state_size;
    std::vector<long> distances(num_states, -1);

    distances[start_state] = 0;
    std::queue<int> queue;
    queue.push(start_state);

    while (!queue.empty()) {
        auto current_state = queue.front();
        queue.pop();

        if (current_state == desired_state) {
            return distances[current_state];
        }

        for (auto button : buttons) {
            auto next_state = current_state ^ button;
            if (distances[next_state] == -1) {
                distances[next_state] = distances[current_state] + 1;
                queue.push(next_state);
            }
        }
    }

    return 0;
}

void process(const char* filename) {
    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line)) {
        auto parts = split(line, ' ');
        parts[0].erase(0, 1);
        parts[0].erase(parts[0].size() - 1);

        auto desired_state = 0;
        for (auto i = 0; i < parts[0].size(); i++) {
            if (parts[0][i] == '#') {
                desired_state |= (1 << i);
            }
        }

        std::vector<int> buttons;
        for (auto i = 1; i < parts.size() - 1; i++) {
            auto button_mask = 0;
            parts[i].erase(0, 1);
            parts[i].erase(parts[i].size() - 1);
            auto btns = split(parts[i], ',');
            for (auto& b : btns) {
                auto btn_index = stoi(b);
                button_mask |= (1 << btn_index);
            }
            buttons.push_back(button_mask);
        }

        sum += process_machine(desired_state, buttons, parts[0].size());
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: machines <filename>\n";
        return 1;
    }

    const char* filename = argv[1];
    process(filename);

    std::cout << sum << '\n';
    return 0;
}
