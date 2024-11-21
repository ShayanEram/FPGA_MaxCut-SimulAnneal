#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"
#include <hls_vector.h>
#include "hls_math.h"

// Type definitions
typedef ap_axis<8,2,5,6> axi_stream;
typedef ap_int<8> int8_t;
typedef ap_int<16> int16_t;
typedef ap_int<32> int32_t;
typedef ap_uint<32> uint32_t;

// Defines
#define ARRAY_SIZE int8_t(36)
#define MATRIX_SIZE int8_t(6)
#define BYTE int8_t(8)
#define RAND_MAX uint32_t(0x7fff)

// Global variables
const double INITIAL_TEMP = 20.0;
const double FINAL_TEMP = 0.0001;
const int MAX_ITER = 2500000;
const double ENERGY_THRESH = 0.1;
const double K_B = 1.0;

int lrand(){
    
    static uint32_t reg = 0xACE1; // Static register to hold the state

    // Feedback taps (example taps for a 32-bit LFSR)
    bool new_bit = (reg[31] ^ reg[21] ^ reg[1] ^ reg[0]); // XOR feedback

    // Shift right and insert the new bit
    reg = (reg >> 1) | (new_bit << 31);

    return reg; // Return the current state as a pseudo-random number

}

hls::vector<double, MATRIX_SIZE> initialSolution(int8_t nVertices) {
    hls::vector<double, MATRIX_SIZE> initVerticesState = 0;
    
    for (short i = 0; i < nVertices; ++i) {
        initVerticesState[i] = (lrand() % 2 == 0) ? -1.0 : 1.0; // Randomly choose -1 or 1
    }
    return initVerticesState;
}

double energy(const hls::vector<double, MATRIX_SIZE>& verticesState, const hls::vector<hls::vector<double, MATRIX_SIZE>, MATRIX_SIZE>& edgesWeight) {
    double edgesWeightSum = 0.0;
    for (short i = 0; i < MATRIX_SIZE; ++i) {
        for (short j = 0; j < MATRIX_SIZE; ++j) {
            edgesWeightSum += edgesWeight[i][j];
        }
    }

    double energyContribute = 0.0;
    for (short i = 0; i < MATRIX_SIZE; ++i) {
        for (short j = 0; j < MATRIX_SIZE; ++j) {
            energyContribute += verticesState[i] * edgesWeight[i][j] * verticesState[j];
        }
    }

    return -0.25 * (edgesWeightSum - energyContribute);
}

int vertexIndexSel(const hls::vector<double, MATRIX_SIZE>& state) {
    return lrand() % MATRIX_SIZE; // Randomly select an index
}

double localField(const hls::vector<double, MATRIX_SIZE>& state, int index, const hls::vector<hls::vector<double, MATRIX_SIZE>, MATRIX_SIZE>& edges) {
    double localFieldValue = 0.0;
    for (short j = 0; j < MATRIX_SIZE; ++j) {
        localFieldValue += edges[index][j] * state[j];
    }
    return localFieldValue;
}

double adjustTemperature(double temperature, int iteration) {
    double percentage = static_cast<double>(iteration + 1) / MAX_ITER;
    return (static_cast<int>(1000 * percentage) % 2 == 0) ? 0.99999 * temperature : temperature;
}

double acceptanceProbability(double deltaEnergy, double temperature) {
    if (deltaEnergy <= 0) {
        return 1.0;
    } else {
        return exp(-deltaEnergy / (K_B * temperature));
    }
}

void simulatedAnnealing(hls::stream<axi_stream_data> &input_stream, hls::stream<axi_stream_data> &output_stream) 
{
    #pragma HLS INTERFACE axis port=input_stream
    #pragma HLS INTERFACE axis port=output_stream
    #pragma HLS INTERFACE s_axilite port=return
    
    // Initialize the matrix and data
    hls::vector<hls::vector<double, MATRIX_SIZE>, MATRIX_SIZE> matrix = 0; // Initialize the matrix with zeros
    axi_stream_data input;

    // Read the next available data from the input stream
    for(short i = 0; i < MATRIX_SIZE; i++){
        for(short j = 0; j < MATRIX_SIZE; j++){
            input = input_stream.read();
            matrix[i][j] = static_cast<double>(input.data);
        }
    }

    hls::vector<double, MATRIX_SIZE> currentSolution = initialSolution(MATRIX_SIZE);
    double currentEnergy = energy(currentSolution, matrix);
    double temperature = INITIAL_TEMP;

    for (int iterate = 0; iterate < MAX_ITER; ++iterate) {
        
        // 1. Select a random vertex
        int vertexIndex = vertexIndexSel(currentSolution);

        // 2. Calculate the local field
        double localFieldVal = localField(currentSolution, vertexIndex, matrix);

        // 3,4. Calculate Energy Difference with new energy (from flipping the vertex)
        double deltaEnergy = -currentSolution[vertexIndex] * localFieldVal;

        // 5. Acceptance Criteria
        double prob = acceptanceProbability(deltaEnergy, temperature);
        if (static_cast<double>(lrand()) / RAND_MAX <= prob) {
            // 6. Update current solution
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        // 7. Update temperature
        temperature = adjustTemperature(temperature, iterate);
        if (temperature == 0) {
            break;
        }

        // 8. Check for convergence
        if (temperature <= FINAL_TEMP && deltaEnergy <= ENERGY_THRESH) {
            break;
        }
    }

    // Initialize the output
    int8_t fpga_output = 0;
    axi_stream_data output;

    // Initialize master signal
    output.keep = input.keep;        // Keep signal
    output.strb = input.strb;        // Strobe signal
    output.user = input.user;        // User signal
    output.id   = input.id;            // ID signal
    output.dest = input.dest;        // Destination signal
    output.last = 0;                     // Last signal

    // Write the output to the output stream
    for(short i = 0; i < MATRIX_SIZE; i++){
        fpga_output = static_cast<int8_t>(currentSolution[i]);
        output.data = fpga_output;
        output_stream.write(output);
    }
    output.last = 1;                     // Last signal
    
}