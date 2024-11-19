import random
import math

INITIAL_TEMP = 20
FINAL_TEMP = 0.0001
MAX_ITER = 2500000
E_THRESH = 0.1
K_B = 1.0

def generateInitialSolution(size):
    state = []
    for _ in range(size):
        state.append(random.choice([-1.0, 1.0]))
    return state

def calculateEnergy(state, edges):
    wijSum = 0
    for i in range(len(state)):
        for j in range(len(state)):
            wijSum += edges[i][j]
    
    eTerm = 0
    for i in range(len(state)):
        for j in range(len(state)):
            eTerm += state[i] * edges[i][j] * state[j]
    
    return -0.25 * (wijSum - eTerm)

def selectRandomVertex(state):
    return random.choice(range(len(state)))

def generateNeighbor(state, index, edges):
    local_field_value = 0
    for j in range(len(state)):
        local_field_value += edges[index][j] * state[j]
    return local_field_value

def coolDown(temp, k):
    percentage = (k + 1) / MAX_ITER
    if int(1000 * percentage) % 2 == 0:
        return 0.99999 * temp
    else:
        return temp

def acceptanceProbability(deltaEnergy, temperature):
    if deltaEnergy <= 0:
        return 1  # Always accept if energy decreases
    else:
        return math.exp(-deltaEnergy / (K_B * temperature))

def simulatedAnnealing(matrix):
    
    currentSolution = generateInitialSolution(len(matrix))
    currentEnergy = calculateEnergy(currentSolution, matrix)
    temperature = INITIAL_TEMP

    for k in range(MAX_ITER):
        
        # 1. Select a random vertex
        vertexIndex = selectRandomVertex(currentSolution)
        
        # 2. Generate a neighbor
        newSolution = generateNeighbor(currentSolution, vertexIndex, matrix)

        # 3. Calculate the new energy
        # not needed as we are using the local field value

        # 4. Calculate Energy Difference
        deltaEnergy = -currentSolution[vertexIndex] * newSolution

        # 5. Acceptance Criteria
        prob = acceptanceProbability(deltaEnergy, temperature)
        if random.random() <= prob:
            
            # 6. Update current solution
            currentSolution[vertexIndex] = -1.0 * currentSolution[vertexIndex]
            currentEnergy += deltaEnergy

        # 7. Update temperature
        temperature = coolDown(temperature, k)
        if temperature == 0:
            break

        # 8. Check for convergence
        if temperature <= FINAL_TEMP and deltaEnergy <= E_THRESH:
            break

    # return currentSolution, currentEnergy
    print(len(currentSolution), currentSolution, temperature, currentEnergy)


if __name__ == "__main__":
    
    J = [[0., 1., 1., 1., 0., 1., 1., 0., 0., 1.],
         [1., 0., 0., 1., 1., 0., 0., 1., 1., 0.],
         [1., 0., 0., 0., 0., 0., 1., 1., 1., 0.],
         [1., 1., 0., 0., 0., 0., 0., 1., 0., 1.],
         [0., 1., 0., 0., 0., 0., 1., 1., 0., 0.],
         [1., 0., 0., 0., 0., 0., 0., 0., 1., 0.],
         [1., 0., 1., 0., 1., 0., 0., 0., 1., 1.],
         [0., 1., 1., 1., 1., 0., 0., 0., 1., 1.],
         [0., 1., 1., 0., 0., 1., 1., 1., 0., 1.],
         [1., 0., 0., 1., 0., 0., 1., 1., 1., 0.]]

    # best_solution, best_energy = simulatedAnnealing(adjacency_matrix)

    # print("Best Cut Energy:", best_energy)
    # print("Best State:", best_solution)

    times = 2

    for i in range(times):
        simulatedAnnealing(J)

    # 10 [1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0] 9.997616423404991e-05 -17.0
    # 10 [-1.0, 1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0] 9.999516160493437e-05 -17.0