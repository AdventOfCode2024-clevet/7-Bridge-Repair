#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <regex>

bool evaluateEquation(const std::vector<int> &numbers, const std::vector<char> &operators, long long target) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result == target;
}

void generateOperatorsCombinations(const std::vector<int> &numbers, long long target, size_t index, std::vector<char> &currentOperators, bool &found) {
    if (found) return;
    if (index == numbers.size() - 1) {
        if (evaluateEquation(numbers, currentOperators, target)) {
            found = true;
        }
        return;
    }

    currentOperators.push_back('+');
    generateOperatorsCombinations(numbers, target, index + 1, currentOperators, found);
    currentOperators.pop_back();

    currentOperators.push_back('*');
    generateOperatorsCombinations(numbers, target, index + 1, currentOperators, found);
    currentOperators.pop_back();
}

bool canProduceTarget(const std::vector<int> &numbers, long long target) {
    std::vector<char> currentOperators;
    bool found = false;
    generateOperatorsCombinations(numbers, target, 0, currentOperators, found);
    return found;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return (1);
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return (1);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    std::vector<std::pair<long long, std::vector<int>>> data;
    std::regex re("([0-9]+): (.+)");
    std::smatch match;
    for (const auto &l : lines) {
        if (std::regex_match(l, match, re)) {
            long long depth = std::stoll(match[1]);
            std::vector<int> range;
            std::string r = match[2];
            std::regex re2("([0-9]+)");
            std::smatch match2;
            while (std::regex_search(r, match2, re2)) {
                range.push_back(std::stoi(match2[1]));
                r = match2.suffix();
            }
            data.push_back(std::make_pair(depth, range));
        }
    }

    long long result = 0;
    for (const auto &d : data) {
        if (canProduceTarget(d.second, d.first)) {
            result += d.first;
        }
    }
    std::cout << "Result: " << result << std::endl;

    return (0);
}
