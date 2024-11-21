
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <cstdlib>
// #include <ctime>


hls::vector<int> hlsStream() {

    hls::vector<hls::vector<double>> matrix = {
        {0., 1., 1., 0., 0., 1.},
        {1., 0., 0., 1., 1., 0.},
        {1., 0., 0., 0., 0., 0.},
        {0., 1., 0., 0., 1., 1.},
        {0., 1., 0., 1., 0., 0.},
        {1., 0., 0., 1., 0., 0.}
    };

	hls::vector<int> matrixStream(0);
    for (const auto& row : matrix) {
        matrixStream.insert(matrixStream.end(), row.begin(), row.end());
    }
    return matrixStream;
}