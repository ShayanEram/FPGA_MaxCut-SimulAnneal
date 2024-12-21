#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"

typedef ap_axis<8, 2, 5, 6> axi_stream;
typedef ap_int<8> int8_a;
typedef ap_int<32> int32_a;
typedef ap_uint<32> uint32_a;

int32_a lrand() {
    static uint32_a lfsr = 0xAFAFu;
    uint32_a bit;
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

int exp_approx(int x) {
    return 1000 + x + (x * x) / 2000;
}

void maxCut(hls::stream<axi_stream> &input_stream, hls::stream<axi_stream> &output_stream) 
{
    #pragma HLS INTERFACE axis port=input_stream
    #pragma HLS INTERFACE axis port=output_stream
    #pragma HLS INTERFACE s_axilite port=return

    const uint32_a RANDMAX = 0x7fff;
    const int INITIAL_TEMP = 20000;
    const int FINAL_TEMP = 10;
    const uint32_a MAX_ITER = 250000;
    const int ENERGY_THRESH = 100;

    int matrix[6][6] = {0};
    axi_stream input;

    // Read the next available data from the input stream
    for (int8_a i = 0; i < 6; i++) {
        for (int8_a j = 0; j < 6; j++) {
            input = input_stream.read();
            matrix[i][j] = static_cast<int>(input.data) * 1000;
        }
    }

    int currentSolution[6] = {0};
    for (int8_a i = 0; i < 6; ++i) {
        currentSolution[i] = (lrand() % 2 == 0) ? -1000 : 1000;
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
            energyContribute += currentSolution[i] * matrix[i][j] * currentSolution[j] / 1000;
        }
    }

    int currentEnergy = -25 * (edgesWeightSum - energyContribute) / 1000;

    int temperature = INITIAL_TEMP;

    for (int32_a iterate = 0; iterate < 250000; ++iterate) {
        int32_a vertexIndex = lrand() % 6;

        int localFieldVal = 0;
        for (int8_a j = 0; j < 6; ++j) {
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
        fpga_output = static_cast<int8_a>(currentSolution[i] / 1000); // Scale back output values
        output.data = fpga_output;
        output.last = (i == 5) ? 1 : 0;
        output_stream.write(output);
    }
}
