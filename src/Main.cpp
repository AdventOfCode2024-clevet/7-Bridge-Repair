#include <iostream>

#include "ArgumentParser.hpp"
#include "CalibrationCalculator.hpp"
#include "FileReader.hpp"

int main(int argc, char* argv[]) {
    try {
        BridgeRepair::ArgumentParser parser(argc, argv);

        BridgeRepair::FileReader reader(parser.getInputFile());
        auto data = reader.getData();

        long long result = 0;
        switch (parser.getPart()) {
            case 1:
                result = BridgeRepair::CalibrationCalculator::calculateCalibrationPartOne(data);
                std::cout << "Result (part 1): " << result << std::endl;
                break;
            case 2:
                result = BridgeRepair::CalibrationCalculator::calculateCalibrationPartTwo(data);
                std::cout << "Result (part 2): " << result << std::endl;
                break;
            default:
                throw std::invalid_argument("Error: part must be 1 or 2");
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}
