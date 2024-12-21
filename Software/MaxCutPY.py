import random
import math

INITIAL_TEMP = 20
FINAL_TEMP = 0.0001
MAX_ITER = 2500000
ENERGY_THRESH = 0.1
K_B = 1.0

def initialSolution(nVertices):
    initVerticesState = []
    for _ in range(nVertices):
        initVerticesState.append(random.choice([-1.0, 1.0]))
    return initVerticesState

def energy(verticesState, edgesWeight):
    edgesWeightSum = 0
    for i in range(len(verticesState)):
        for j in range(len(verticesState)):
            edgesWeightSum += edgesWeight[i][j]
    
    energyContribute = 0
    for i in range(len(verticesState)):
        for j in range(len(verticesState)):
            energyContribute += verticesState[i] * edgesWeight[i][j] * verticesState[j]
    
    return -0.25 * (edgesWeightSum - energyContribute)

def vertexIndexSel(state):
    index = random.choice(range(len(state)))
    return index

def localField(state, index, edges):
    localFieldValue = 0
    for j in range(len(state)):
        localFieldValue += edges[index][j] * state[j]
    return localFieldValue

def adjustTemperature(temperature, iteration):
    percentage = (iteration + 1) / MAX_ITER
    if int(1000 * percentage) % 2 == 0:
        return 0.99999 * temperature
    else:
        return temperature

def acceptanceProbability(deltaEnergy, temperature):
    if deltaEnergy <= 0:
        return 1
    else:
        return math.exp(-deltaEnergy / (K_B * temperature))

def simulatedAnnealing(matrix):
    
    currentSolution = initialSolution(len(matrix))
    currentEnergy = energy(currentSolution, matrix)
    temperature = INITIAL_TEMP

    for iterate in range(MAX_ITER):
        
        # 1. Select a random vertex
        vertexIndex = vertexIndexSel(currentSolution)
        
        # 2. Calculate the local field
        localFieldVal = localField(currentSolution, vertexIndex, matrix)

        # 3,4. Calculate Energy Difference with new energy (from flipping the vertex)
        deltaEnergy = -currentSolution[vertexIndex] * localFieldVal

        # 5. Acceptance Criteria
        prob = acceptanceProbability(deltaEnergy, temperature)
        if random.random() <= prob:
            
            # 6. Update current solution
            currentSolution[vertexIndex] = -1.0 * currentSolution[vertexIndex]
            currentEnergy += deltaEnergy

        # 7. Update temperature
        temperature = adjustTemperature(temperature, iterate)
        if temperature == 0:
            break

        # 8. Check for convergence
        if temperature <= FINAL_TEMP and deltaEnergy <= ENERGY_THRESH:
            break

    return currentSolution


if __name__ == "__main__":
    

    matrix = [
            [0., 1., 1., 0., 0., 1.],
            [1., 0., 0., 1., 1., 0.],
            [1., 0., 0., 0., 0., 0.],
            [0., 1., 0., 0., 1., 1.],
            [0., 1., 0., 1., 0., 0.],
            [1., 0., 0., 1., 0., 0.]]

    best_solution = simulatedAnnealing(matrix)
    print()
    print("Best State:", best_solution)
    print()