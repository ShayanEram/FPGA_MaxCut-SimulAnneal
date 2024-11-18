import random
import math

# Constants
INITIAL_TEMP = 10000
FINAL_TEMP = 1
MAX_ITER = 10000
ALPHA = 0.95

def generateInitialSolution(graph):
    solution = {}
    for edge in graph.keys():
        for i in edge:
            solution[i] = random.choice([-1, 1])
    return solution

def calculateEnergy(solution, graph):
    energy = 0
    for (i, j), weight in graph.items():
        if solution[i] != solution[j]:  # Different sets
            energy += weight
    return energy

def selectRandomVertex(solution):
    vertex = random.choice(list(solution.keys()))
    return vertex

def generateNeighbor(current_solution, vertex):
    new_solution = current_solution.copy()
    new_solution[vertex] *= -1  # Flip from -1 to 1 or vice versa
    return new_solution

def coolDown(temperature):
    return temperature * ALPHA

def simulatedAnnealing(graph):
    
    currentSolution = generateInitialSolution(graph)
    currentEnergy = calculateEnergy(currentSolution, graph)
    temperature = INITIAL_TEMP

    while temperature > FINAL_TEMP:
        for _ in range(MAX_ITER):
            
            # 1. Select a random vertex
            vertex = selectRandomVertex(currentSolution)
            
            # 2. Generate a neighbor
            newSolution = generateNeighbor(currentSolution, vertex)

            # 3. Calculate the new energy
            newEnergy = calculateEnergy(newSolution, graph)

            # 4. Calculate Energy Difference
            deltaEnergy = newEnergy - currentEnergy

            # 5. Acceptance Criteria
            if deltaEnergy <= 0 or random.random() < math.exp(-deltaEnergy / temperature):
                
                # 6. Update current solution
                currentSolution = newSolution
                currentEnergy = newEnergy

            # 7. Update temperature
            temperature = coolDown(temperature)
            if temperature == 0:
                break

    return currentSolution, currentEnergy


if __name__ == "__main__":
    
    # Define a graph as a dictionary of edges with weights
    graph = {
        (0, 1): 1,
        (0, 2): 2,
        (1, 2): 3,
        (1, 3): 4,
        (2, 3): 5
    }

    best_solution, best_energy = simulatedAnnealing(graph)

    print("Best Cut Energy:", best_energy)
    print("Best State:", best_solution)