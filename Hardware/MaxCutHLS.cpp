#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"
#include "hls_math.h"

typedef ap_axis<8,2,5,6> axi_stream;
typedef ap_int<8> int8_a;
typedef ap_int<32> int32_a;
typedef ap_uint<32> uint32_a;

int32_a lrand(){
    
    static uint32_a reg = 0xACEF;

    uint32_a new_bit = (reg >> 15) ^ (reg >> 13) ^ (reg >> 12) ^ (reg >> 10);

    reg = (reg >> 1) | (new_bit << 15);

    return reg;
}

void maxCut(hls::stream<axi_stream> &input_stream, hls::stream<axi_stream> &output_stream)
{
    #pragma HLS INTERFACE axis port=input_stream
    #pragma HLS INTERFACE axis port=output_stream
    #pragma HLS INTERFACE s_axilite port=return

    // Defines & Constants
    // const int8_a ARRAY_SIZE = 36;
    // const int8_a MATRIX_SIZE = 6;
    const uint32_a RANDMAX = 0x7fff;

    const float INITIAL_TEMP = 20.0;
    const float FINAL_TEMP = 0.0001;
    const uint32_a MAX_ITER = 2500;
    const float ENERGY_THRESH = 0.1;
    // const float K_B = 1.0;

    // Initialize the matrix and data
    float matrix[6][6] = {0}; // Initialize the matrix with zeros
    axi_stream input;

    // Read the next available data from the input stream
    for(int8_a i = 0; i < 6; i++){
        for(int8_a j = 0; j < 6; j++){
            input = input_stream.read();
            matrix[i][j] = static_cast<float>(input.data);
        }
    }

    // Initialize the current solution ...........................//
    float currentSolution[6] = {0};
    for (int8_a i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -1.0 : 1.0;
    }

    // Initialize the current energy ................................//
    float edgesWeightSum = 0.0;
    for (int8_a i = 0; i < 6; ++i) {
        for (int8_a j = 0; j < 6; ++j) {
            edgesWeightSum += matrix[i][j];
        }
    }
    float energyContribute = 0.0;
    for (int8_a i = 0; i < 6; ++i) {
        for (int8_a j = 0; j < 6; ++j) {
            energyContribute += currentSolution[i] * matrix[i][j] * currentSolution[j];
        }
    }
    float currentEnergy = 0.0;
    currentEnergy = -0.25 * (edgesWeightSum - energyContribute);

    // Initialize the temperature ...................................//
    float temperature = INITIAL_TEMP;

    ///////////////////////////////////////////////////////////////////////////
    for (int32_a iterate = 0; iterate < 2500; ++iterate) {
        
        // 1. Select a random vertex ..................................//
        int32_a vertexIndex = 0;
        vertexIndex = lrand() % 6;

        // 2. Calculate the local field .................................//
        float localFieldVal = 0.0;
        for (int8_a j = 0; j < 6; ++j) {
        	localFieldVal += matrix[vertexIndex][j] * currentSolution[j];
        }

        // 3,4. Calculate Energy Difference with new energy ..............//
        float deltaEnergy = 0.0;
        deltaEnergy = -currentSolution[vertexIndex] * localFieldVal;

        // 5. Acceptance Criteria ......................................//
        float prob = 0.0;
        if (deltaEnergy <= 0) {
            prob = 1.0;
        } else {
            prob = hls::expf(-deltaEnergy / temperature);
        }

        // 6. Update current solution ..................................//
        if (static_cast<float>(lrand()) / RANDMAX <= prob) {
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        // 7. Update temperature .......................................//
        float percentage = 0.0;
        percentage = static_cast<float>(iterate + 1) / MAX_ITER;
        temperature = (static_cast<int32_a>(1000 * percentage) % 2 == 0) ? 0.99999 * temperature : temperature;
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
    int8_a fpga_output = 0;
    axi_stream output;

    // Initialize master signal
    output.keep = input.keep;        // Keep signal
    output.strb = input.strb;        // Strobe signal
    output.user = input.user;        // User signal
    output.id   = input.id;          // ID signal
    output.dest = input.dest;        // Destination signal
    output.last = 0;                 // Last signal

    // Write the output to the output stream
    for(int8_a i = 0; i < 6; i++){
        fpga_output = static_cast<int8_a>(currentSolution[i]);
        output.data = fpga_output;
        output.last = (i == 5) ? 1 : 0;
        output_stream.write(output);
    }
}