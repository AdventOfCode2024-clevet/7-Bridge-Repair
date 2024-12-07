#include <regex>

#include "FileReader.hpp"

BridgeRepair::FileReader::FileReader(const std::string &fileName)
{
    input.open(fileName);
    if (!input.is_open())
    {
        throw std::runtime_error("Error: could not open file " + fileName);
    }
}

std::vector<std::pair<long long, std::vector<int>>> BridgeRepair::FileReader::getData()
{
    auto lines = readLines();

    std::vector<std::pair<long long, std::vector<int>>> data;
    std::regex re("([0-9]+): (.+)");
    std::smatch match;
    for (const auto &l : lines)
    {
        if (std::regex_match(l, match, re))
        {
            long long depth = std::stoll(match[1]);
            std::vector<int> range;
            std::string r = match[2];
            std::regex re2("([0-9]+)");
            std::smatch match2;

            while (std::regex_search(r, match2, re2))
            {
                range.push_back(std::stoi(match2[1]));
                r = match2.suffix();
            }

            data.push_back(std::make_pair(depth, range));
        }
    }

    return (data);
}

std::vector<std::string> BridgeRepair::FileReader::readLines()
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }
    return (lines);
}
