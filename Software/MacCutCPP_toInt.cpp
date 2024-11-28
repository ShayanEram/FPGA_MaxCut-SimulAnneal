#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>

uint32_t lrand()
{
    static uint32_t lfsr = 0xACE1u;
    uint32_t bit;
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

int exp_approx(int x)
{
    // Approximate e^x using 1 + x + x^2 / 2, scaled by 1000
    return 1000 + x + (x * x) / 2000;
}

std::vector<int8_t> maxCut(const std::vector<int8_t>& input_stream)
{
    const uint32_t RANDMAX = 0x7fff;
    const int INITIAL_TEMP = 20000;  // Scaled by 1000
    const int FINAL_TEMP = 10;       // Scaled by 1000
    const uint32_t MAX_ITER = 250000;
    const int ENERGY_THRESH = 100;   // Scaled by 1000

    int matrix[6][6] = { 0 };
    int8_t input = 0;

    for (int8_t i = 0; i < 6; i++) {
        for (int8_t j = 0; j < 6; j++) {
            input = input_stream[j + i * 6];
            matrix[i][j] = static_cast<int>(input) * 1000;  // Scaling by 1000
        }
    }

    int currentSolution[6] = { 0 };
    for (int8_t i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -1000 : 1000;  // Scaling by 1000
    }

    int edgesWeightSum = 0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            edgesWeightSum += matrix[i][j];
        }
    }

    int energyContribute = 0;
    for (int8_t i = 0; i < 6; ++i) {
        for (int8_t j = 0; j < 6; ++j) {
            energyContribute += currentSolution[i] * matrix[i][j] * currentSolution[j] / 1000;
        }
    }

    int currentEnergy = -25 * (edgesWeightSum - energyContribute) / 1000;

    int temperature = INITIAL_TEMP;

    for (int32_t iterate = 0; iterate < MAX_ITER; ++iterate) {
        int32_t vertexIndex = lrand() % 6;

        int localFieldVal = 0;
        for (int8_t j = 0; j < 6; ++j) {
            localFieldVal += matrix[vertexIndex][j] * currentSolution[j] / 1000;
        }

        int deltaEnergy = -currentSolution[vertexIndex] * localFieldVal / 1000;

        int prob = (deltaEnergy <= 0) ? 1000 : exp_approx(-deltaEnergy * 1000 / temperature);

        if (static_cast<int>(1000 * lrand() / RANDMAX) <= prob) {
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        int percentage = 1000 * (iterate + 1) / MAX_ITER;
        temperature = (percentage % 2 == 0) ? 99999 * temperature / 100000 : temperature;

        if (temperature == 0) {
            break;
        }

        if (temperature <= FINAL_TEMP && deltaEnergy <= ENERGY_THRESH) {
            std::cout << "Converged at iteration: " << iterate << std::endl;
            break;
        }
    }

    std::vector<int8_t> output(6);
    for (int8_t i = 0; i < 6; i++) {
        output[i] = static_cast<int8_t>(currentSolution[i] / 1000);  // Scale back
    }

    return output;
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

    //srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    std::vector<int8_t> input_stream;
    for (const auto& row : matrix) {
        input_stream.insert(input_stream.end(), row.begin(), row.end());
    }

    std::vector<int8_t> output_stream;
    output_stream = maxCut(input_stream);

    std::cout << "Best State: ";
    for (int8_t state : output_stream) {
        std::cout << static_cast<int>(state) << " ";
    }
    std::cout << std::endl;

    return 0;
}
