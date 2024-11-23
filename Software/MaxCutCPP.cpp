#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>

int32_t lrand(){
    
    static uint32_t reg = 0xACE1;

    uint32_t new_bit = (reg >> 15) ^ (reg >> 13) ^ (reg >> 12) ^ (reg >> 12) ^ (reg >> 10);

    reg = (reg >> 1) | (new_bit << 15);

    return reg;
}

std::vector<int8_t> simulatedAnnealing(const std::vector<int8_t> &input_stream)
{
    
    // Defines & Constants
    const int8_t ARRAY_SIZE = 36;
    const int8_t MATRIX_SIZE = 6;
    const int8_t BYTE = 8;
    const uint32_t RANDMAX = 0x7fff;

    const double INITIAL_TEMP = 20.0;
    const double FINAL_TEMP = 0.0001;
    const uint32_t MAX_ITER = 2500;
    const double ENERGY_THRESH = 0.1;
    const double K_B = 1.0;

    // Initialize the matrix and data
    double matrix[6][6] = {0}; // Initialize the matrix with zeros
    int8_t input = 0;

    // Read the next available data from the input stream
    for(int8_t i = 0; i < 6; i++){
        for(int8_t j = 0; j < 6; j++){
            input = input_stream[j + i * 6];
            matrix[i][j] = static_cast<double>(input);
        }
    }

    // Initialize the current solution ...........................//
    double currentSolution[6] = {0};
    for (int8_t i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -1.0 : 1.0;
    }

    // Initialize the current energy ................................//
    double edgesWeightSum = 0.0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            edgesWeightSum += matrix[i][j];
        }
    }
    double energyContribute = 0.0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            energyContribute += currentSolution[i] * matrix[i][j] * currentSolution[j];
        }
    }
    double currentEnergy = 0.0;
    currentEnergy = -0.25 * (edgesWeightSum - energyContribute);

    // Initialize the temperature ...................................//
    double temperature = INITIAL_TEMP;

    ///////////////////////////////////////////////////////////////////////////
    for (int32_t iterate = 0; iterate < MAX_ITER; ++iterate) {
        
        // 1. Select a random vertex ..................................//
        int32_t vertexIndex = 0;
        vertexIndex = lrand() % 6;

        // 2. Calculate the local field .................................//
        double localFieldVal = 0.0;
        for (int8_t j = 0; j < 6; ++j) {
        	localFieldVal += matrix[vertexIndex][j] * currentSolution[j];
        }

        // 3,4. Calculate Energy Difference with new energy ..............//
        double deltaEnergy = 0.0;
        deltaEnergy = -currentSolution[vertexIndex] * localFieldVal;

        // 5. Acceptance Criteria ......................................//
        double prob = 0.0;
        if (deltaEnergy <= 0) {
            prob = 1.0;
        } else {
            prob = std::exp(-deltaEnergy / temperature);
        }

        // 6. Update current solution ..................................//
        if (static_cast<double>(lrand()) / RANDMAX <= prob) {
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        // 7. Update temperature .......................................//
        double percentage = 0.0;
        percentage = static_cast<double>(iterate + 1) / MAX_ITER;
        temperature = (static_cast<int32_t>(1000 * percentage) % 2 == 0) ? 0.99999 * temperature : temperature;
        if (temperature == 0) {
            break;
        }

        // 8. Check for convergence ....................................//
        if (temperature <= FINAL_TEMP && deltaEnergy <= ENERGY_THRESH) {
            break;
        }
    }
    ///////////////////////////////////////////////////////////////////////////

    // Initialize the output
    int8_t fpga_output = 0;
    std::vector<int8_t> output(6);

    std::vector<int8_t> output_stream(6);
    // Write the output to the output stream
    for(int8_t i = 0; i < 6; i++){
        fpga_output = static_cast<int8_t>(currentSolution[i]);
        output[i] = fpga_output;
        output_stream[i] = output[i];
    }

    return output_stream;
}

int main()
{
    std::vector<std::vector<int8_t>> matrix = {
    {0, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1},
    {0, 1, 0, 1, 0, 0},
    {1, 0, 0, 1, 0, 0}
    };

    std::vector<int8_t> input_stream(36);
    for (const auto& row : matrix) {
        input_stream.insert(input_stream.end(), row.begin(), row.end());
    }

    std::vector<int8_t> output_stream(6);
    output_stream = simulatedAnnealing(input_stream);

    std::cout << "Best State: ";
    for (int8_t state : output_stream) {
        std::cout << static_cast<int>(state) << " ";
    }
    std::cout << std::endl;

    return 0;
}
