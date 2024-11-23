#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"
#include "hls_math.h"
#include <iostream>

// Type definitions
typedef ap_axis<8,2,5,6> axi_stream;
typedef ap_int<8> int8_a;
typedef ap_int<32> int32_a;
typedef ap_uint<32> uint32_a;

void maxCut(hls::stream<axi_stream> &input_stream, hls::stream<axi_stream> &output_stream);

// Test Bench
int main() {
    hls::stream<axi_stream> input_stream;
    hls::stream<axi_stream> output_stream;

    // Initialize input data
    axi_stream input_data;
    input_data.data = 1; // Example input data, replace with actual values as needed
    input_data.keep = -1; // All bytes are valid
    input_data.strb = -1; // All strobes are valid
    input_data.user = 0;
    input_data.id   = 0;
    input_data.dest = 0;
    input_data.last = 0;

    // Fill the input stream with example data
    for (int i = 0; i < 36; i++) { // Assuming 36 input elements
        input_stream.write(input_data);
    }

    // Call the simulated annealing function
    maxCut(input_stream, output_stream);

    // Read and print the output data
    while (!output_stream.empty()) {
        axi_stream output_data = output_stream.read();
        std::cout << "Output data: " << output_data.data.to_int() << std::endl;
    }

    return 0;
}
