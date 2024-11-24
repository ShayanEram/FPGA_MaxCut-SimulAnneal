#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"

// Define the scaling factor
const int SCALE_FACTOR = 10000;

typedef ap_axis<8, 2, 5, 6> axi_stream;
typedef ap_int<8> int8_a;
typedef ap_int<32> int32_a;
typedef ap_uint<32> uint32_a;

int32_a lrand() {
    static uint32_a reg = 0xACEF;
    uint32_a new_bit = (reg >> 15) ^ (reg >> 13) ^ (reg >> 12) ^ (reg >> 10);
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

void maxCut(hls::stream<axi_stream> &input_stream, hls::stream<axi_stream> &output_stream) {
    #pragma HLS INTERFACE axis port=input_stream
    #pragma HLS INTERFACE axis port=output_stream
    #pragma HLS INTERFACE s_axilite port=return

    const uint32_a RANDMAX = 0x7fff;

    const int INITIAL_TEMP = 200000; // 20.0 * SCALE_FACTOR
    const int FINAL_TEMP = 1;        // 0.0001 * SCALE_FACTOR
    const uint32_a MAX_ITER = 2500;
    const int ENERGY_THRESH = 1000;  // 0.1 * SCALE_FACTOR

    int matrix[6][6] = {0}; // Initialize the matrix with zeros
    axi_stream input;

    // Read the next available data from the input stream
    for (int8_a i = 0; i < 6; i++) {
        for (int8_a j = 0; j < 6; j++) {
            input = input_stream.read();
            matrix[i][j] = input.data * SCALE_FACTOR; // Scale input values
        }
    }

    int currentSolution[6] = {0};
    for (int8_a i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -SCALE_FACTOR : SCALE_FACTOR;
    }

    int edgesWeightSum = 0;
    for (int8_a i = 0; i < 6; ++i) {
        for (int8_a j = 0; j < 6; ++j) {
            edgesWeightSum += matrix[i][j];
        }
    }

    int energyContribute = 0;
    for (int8_a i = 0; i < 6; ++i) {
        for (int8_a j = 0; j < 6; ++j) {
            energyContribute += (currentSolution[i] * matrix[i][j] * currentSolution[j]) / SCALE_FACTOR;
        }
    }

    int currentEnergy = -((edgesWeightSum - energyContribute) / 4);

    int temperature = INITIAL_TEMP;

    for (int32_a iterate = 0; iterate < 2500; ++iterate) {
        int32_a vertexIndex = lrand() % 6;

        int localFieldVal = 0;
        for (int8_a j = 0; j < 6; ++j) {
            localFieldVal += (matrix[vertexIndex][j] * currentSolution[j]) / SCALE_FACTOR;
        }

        int deltaEnergy = -((currentSolution[vertexIndex] * localFieldVal) / SCALE_FACTOR);

        int prob = (deltaEnergy <= 0) ? SCALE_FACTOR : linear_approx_exp(deltaEnergy / temperature);

        if (lrand() % RANDMAX <= prob) {
            currentSolution[vertexIndex] = -currentSolution[vertexIndex];
            currentEnergy += deltaEnergy;
        }

        int percentage = static_cast<int>((iterate + 1) * SCALE_FACTOR / MAX_ITER);
        temperature = (1000 * percentage / SCALE_FACTOR % 2 == 0) ? (temperature * 99999 / 100000) : temperature;

        if (temperature == 0) {
            break;
        }

        if (temperature <= FINAL_TEMP && deltaEnergy <= ENERGY_THRESH) {
            break;
        }
    }

    int8_a fpga_output = 0;
    axi_stream output;
    output.keep = input.keep;
    output.strb = input.strb;
    output.user = input.user;
    output.id   = input.id;
    output.dest = input.dest;
    output.last = 0;

    for (int8_a i = 0; i < 6; i++) {
        fpga_output = static_cast<int8_a>(currentSolution[i] / SCALE_FACTOR); // Scale back output values
        output.data = fpga_output;
        output.last = (i == 5) ? 1 : 0;
        output_stream.write(output);
    }
}
