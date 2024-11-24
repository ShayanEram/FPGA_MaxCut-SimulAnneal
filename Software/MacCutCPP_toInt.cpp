#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>

// Define the scaling factor
const int SCALE_FACTOR = 10000;


int32_t lrand(){
    static uint32_t reg = 0xACEF;
    uint32_t new_bit = (reg >> 15) ^ (reg >> 13) ^ (reg >> 12) ^ (reg >> 10);
    reg = (reg >> 1) | (new_bit << 15);
    return reg;
}

int linear_approx_exp(int x) {
    // Linear approximation for exp(-x)
    if (x > SCALE_FACTOR) {
        return 0;
    } else if (x < -SCALE_FACTOR) {
        return SCALE_FACTOR;
    } else {
        // Approximate e^(-x) = 1 - x (first two terms of Taylor series for e^(-x))
        return SCALE_FACTOR - (x / 10); // Scale factor for approximation
    }
}

std::vector<int8_t> maxCut(const std::vector<int8_t> &input_stream)
{
    
    // Defines & Constants
    const uint32_t RANDMAX = 0x7fff;

    const int INITIAL_TEMP = 200000; // 20.0 * SCALE_FACTOR
    const int FINAL_TEMP = 1;        // 0.0001 * SCALE_FACTOR
    const uint32_t MAX_ITER = 2500;
    const int ENERGY_THRESH = 1000;  // 0.1 * SCALE_FACTOR

    // Initialize the matrix and data
    int matrix[6][6] = {0}; // Initialize the matrix with zeros
    int8_t input = 0;

    // Read the next available data from the input stream
    for(int8_t i = 0; i < 6; i++){
        for(int8_t j = 0; j < 6; j++){
            input = input_stream[j + i * 6];
            matrix[i][j] = static_cast<int>(input) * SCALE_FACTOR;
        }
    }

    // Initialize the current solution ...........................//
    int currentSolution[6] = {0};
    for (int8_t i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -SCALE_FACTOR : SCALE_FACTOR;
    }

    // Initialize the current energy ................................//
    int edgesWeightSum = 0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            edgesWeightSum += matrix[i][j];
        }
    }
    int energyContribute = 0.0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            energyContribute += (currentSolution[i] * matrix[i][j] * currentSolution[j]) / SCALE_FACTOR;
        }
    }
    int currentEnergy = 0.0;
    currentEnergy = (-(edgesWeightSum - energyContribute) / 4);

    // Initialize the temperature ...................................//
    int temperature = INITIAL_TEMP;

    ///////////////////////////////////////////////////////////////////////////
    for (int32_t iterate = 0; iterate < MAX_ITER; ++iterate) {
        
        // 1. Select a random vertex ..................................//
        int32_t vertexIndex = 0;
        vertexIndex = lrand() % 6;

        // 2. Calculate the local field .................................//
        int localFieldVal = 0;
        for (int8_t j = 0; j < 6; ++j) {
        	localFieldVal += (matrix[vertexIndex][j] * currentSolution[j]) / SCALE_FACTOR;
        }

        // 3,4. Calculate Energy Difference with new energy ..............//
        int deltaEnergy = 0;
        deltaEnergy = (-currentSolution[vertexIndex] * localFieldVal) / SCALE_FACTOR;

        // 5. Acceptance Criteria ......................................//
        int prob = 0;
        prob = (deltaEnergy <= 0) ? SCALE_FACTOR : linear_approx_exp(deltaEnergy / temperature);
        
        // 6. Update current solution ..................................//
        if (lrand() / RANDMAX <= prob) {
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        // 7. Update temperature .......................................//
        int percentage = 0;
        percentage = static_cast<int>((iterate + 1) * SCALE_FACTOR / MAX_ITER);
        temperature = (1000 * percentage / SCALE_FACTOR % 2 == 0) ? (temperature * 99999 / 100000) : temperature;
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
        fpga_output = static_cast<int8_t>(currentSolution[i] / SCALE_FACTOR);
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
    output_stream = maxCut(input_stream);

    std::cout << "Best State: ";
    for (int8_t state : output_stream) {
        std::cout << static_cast<int>(state) << " ";
    }
    std::cout << std::endl;

    return 0;
}
