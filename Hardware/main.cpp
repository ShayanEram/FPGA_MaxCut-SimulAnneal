#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

const double INITIAL_TEMP = 20.0;
const double FINAL_TEMP = 0.0001;
const int MAX_ITER = 2500000;
const double ENERGY_THRESH = 0.1;
const double K_B = 1.0;

std::vector<double> initialSolution(int nVertices) {
    std::vector<double> initVerticesState(nVertices);
    
    for (int i = 0; i < nVertices; ++i) {
        initVerticesState[i] = (rand() % 2 == 0) ? -1.0 : 1.0; // Randomly choose -1 or 1
    }
    return initVerticesState;
}

double energy(const std::vector<double>& verticesState, const std::vector<std::vector<double>>& edgesWeight) {
    double edgesWeightSum = 0.0;
    for (size_t i = 0; i < verticesState.size(); ++i) {
        for (size_t j = 0; j < verticesState.size(); ++j) {
            edgesWeightSum += edgesWeight[i][j];
        }
    }

    double energyContribute = 0.0;
    for (size_t i = 0; i < verticesState.size(); ++i) {
        for (size_t j = 0; j < verticesState.size(); ++j) {
            energyContribute += verticesState[i] * edgesWeight[i][j] * verticesState[j];
        }
    }

    return -0.25 * (edgesWeightSum - energyContribute);
}

int vertexIndexSel(const std::vector<double>& state) {
    return rand() % state.size(); // Randomly select an index
}

double localField(const std::vector<double>& state, int index, const std::vector<std::vector<double>>& edges) {
    double localFieldValue = 0.0;
    for (size_t j = 0; j < state.size(); ++j) {
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

std::vector<double> simulatedAnnealing(const std::vector<std::vector<double>>& matrix) {
    std::vector<double> currentSolution = initialSolution(matrix.size());
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
        if (static_cast<double>(rand()) / RAND_MAX <= prob) {
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

    return currentSolution;
}


int main(int graph, int** weight) {
    
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    std::vector<std::vector<double>> matrix = {
        {0., 1., 1., 1., 0., 1., 1., 0., 0., 1.},
        {1., 0., 0., 1., 1., 0., 0., 1., 1., 0.},
        {1., 0., 0., 0., 0., 0., 1., 1., 1., 0.},
        {1., 1., 0., 0., 0., 0., 0., 1., 0., 1.},
        {0., 1., 0., 0., 0., 0., 1., 1., 0., 0.},
        {1., 0., 0., 0., 0., 0., 0., 0., 1., 0.},
        {1., 0., 1., 0., 1., 0., 0., 0., 1., 1.},
        {0., 1., 1., 1., 1., 0., 0., 0., 1., 1.},
        {0., 1., 1., 0., 0., 1., 1., 1., 0., 1.},
        {1., 0., 0., 1., 0., 0., 1., 1., 1., 0.}
    };

    std::vector<double> best_solution = simulatedAnnealing(matrix);

    std::cout << "Best State: ";
    for (double state : best_solution) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    return 0;
}