import random
import math

INITIAL_TEMP = 20
FINAL_TEMP = 0.0001
MAX_ITER = 2500000
ENERGY_THRESH = 0.1
K_B = 1.0

def initialSolution(nVertices):
    '''
    Purpose: Initializes the state of the system.
    Functionality: Creates an array of size nVertices, where each element is randomly chosen to be either -1.0 or 1.0. 
    This represents the initial configuration of the vertices in the graph.
    '''
    initVerticesState = []
    for _ in range(nVertices):
        initVerticesState.append(random.choice([-1.0, 1.0]))
    return initVerticesState

def energy(verticesState, edgesWeight):
    '''
    Purpose: Calculates the energy of the current state.
    Functionality: Computes the total weight of edges crossing the cut defined by the state. 
    The energy is negative, reflecting that lower energy states (more edges cut) are preferred. 
    The formula accounts for both the total weight of edges and the contributions from the current state.
    '''
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
    '''
    Purpose: Selects a random vertex index.
    Functionality: Returns a random index from the range of the state array, allowing for random exploration of the state space during the annealing process.
    '''
    index = random.choice(range(len(state)))
    return index

def localField(state, index, edges):
    '''
    Purpose: Computes the local field for a specific vertex.
    Functionality: Calculates the influence of neighboring vertices on the vertex at index. 
    This is used to determine how flipping the state of this vertex will affect the overall energy.
    '''
    localFieldValue = 0
    for j in range(len(state)):
        localFieldValue += edges[index][j] * state[j]
    return localFieldValue

def adjustTemperature(temperature, iteration):
    '''
    Purpose: Adjusts the temperature in a specific manner.
    Functionality: This function modifies the temperature based on the iteration count, alternating the temperature slightly to facilitate exploration of the state space.
    '''
    percentage = (iteration + 1) / MAX_ITER
    if int(1000 * percentage) % 2 == 0:
        return 0.99999 * temperature
    else:
        return temperature

def acceptanceProbability(deltaEnergy, temperature):
    '''
    Purpose: Determines whether to accept a new state based on energy change.
    Functionality: If the energy decreases (deltaEnergy is negative), the new state is always accepted. 
    If the energy increases, the acceptance probability is calculated using the Boltzmann distribution, which depends on the temperature and the change in energy.
    '''
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
    
    # 0: No edge between the vertices.
    # 1: An edge exists between the vertices.
    matrix = [[0., 1., 1., 1., 0., 1., 1., 0., 0., 1.], # Vertex 0 is connected to vertices 1, 2, 3, 5, 6, and 9.
            [1., 0., 0., 1., 1., 0., 0., 1., 1., 0.],   # Vertex 1 is connected to vertices 0, 3, 4, 7, and 8.
            [1., 0., 0., 0., 0., 0., 1., 1., 1., 0.],   # ...
            [1., 1., 0., 0., 0., 0., 0., 1., 0., 1.],
            [0., 1., 0., 0., 0., 0., 1., 1., 0., 0.],
            [1., 0., 0., 0., 0., 0., 0., 0., 1., 0.],
            [1., 0., 1., 0., 1., 0., 0., 0., 1., 1.],
            [0., 1., 1., 1., 1., 0., 0., 0., 1., 1.],
            [0., 1., 1., 0., 0., 1., 1., 1., 0., 1.],
            [1., 0., 0., 1., 0., 0., 1., 1., 1., 0.]]


    best_solution = simulatedAnnealing(matrix)

    print("Best State:", best_solution)