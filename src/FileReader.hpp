#pragma once

#ifndef FILEREADER_HPP
    #define FILEREADER_HPP

    #include <fstream>
    #include <string>
    #include <vector>

    namespace BridgeRepair
    {
        class FileReader
        {
            public:
                explicit FileReader(const std::string &fileName);
                ~FileReader() = default;

                std::vector<std::pair<long long, std::vector<int>>> getData();

            private:
                std::ifstream input;
                std::vector<std::string> readLines();
        };
    }

#endif /* FILEREADER_HPP */
