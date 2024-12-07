#pragma once

#ifndef CALIBRATIONCALCULATOR_HPP
    #define CALIBRATIONCALCULATOR_HPP

    #include <functional>
    #include <string>
    #include <vector>

    namespace BridgeRepair
    {
        class CalibrationCalculator
        {
            public:
                static long long calculateCalibrationPartOne(const std::vector<std::pair<long long, std::vector<int>>> &data)
                {
                    const std::vector<std::string> operators = { "+", "*" };

                    return calculateCalibration(data, operators);
                }

                static long long calculateCalibrationPartTwo(const std::vector<std::pair<long long, std::vector<int>>> &data)
                {
                    const std::vector<std::string> operators = { "||", "+", "*" };

                    return calculateCalibration(data, operators);
                }

            private:
                static bool evaluateEquation(const std::vector<int> &numbers, const std::vector<std::string> &operators, long long target)
                {
                    long long result = numbers[0];

                    for (size_t i = 0; i < operators.size(); ++i) {
                        if (operators[i] == "||") {
                            std::string s1 = std::to_string(result);
                            std::string s2 = std::to_string(numbers[i + 1]);
                            result = std::stoll(s1 + s2);
                        } else if (operators[i] == "+") {
                            result += numbers[i + 1];
                        } else if (operators[i] == "*") {
                            result *= numbers[i + 1];
                        }
                    }

                    return result == target;
                }

                static void generateOperatorsCombinations(const std::vector<std::string> &operators, long long target, const std::vector<int> &numbers, size_t index, std::vector<std::string> &currentOperators, bool &found)
                {
                    if (found) return;
                    if (index == numbers.size() - 1)
                    {
                        if (evaluateEquation(numbers, currentOperators, target))
                        {
                            found = true;
                        }
                        return;
                    }

                    for (const auto &op : operators)
                    {
                        currentOperators.push_back(op);
                        generateOperatorsCombinations(operators, target, numbers, index + 1, currentOperators, found);
                        currentOperators.pop_back();
                    }
                }

                static bool canProduceTarget(const std::vector<std::string> &operators, long long target, const std::vector<int> &numbers)
                {
                    std::vector<std::string> currentOperators;
                    bool found = false;

                    generateOperatorsCombinations(operators, target, numbers, 0, currentOperators, found);

                    return (found);
                }

                static long long calculateCalibration(const std::vector<std::pair<long long, std::vector<int>>> &data, const std::vector<std::string> &operators)
                {
                    long long result = 0;

                    for (const auto &entry : data)
                    {
                        if (canProduceTarget(operators, entry.first, entry.second))
                        {
                            result += entry.first;
                        }
                    }

                    return (result);
                }
        };
    }

#endif /* CALIBRATIONCALCULATOR_HPP */
