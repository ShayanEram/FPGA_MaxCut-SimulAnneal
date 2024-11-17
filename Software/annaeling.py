import numpy as np
import random
import math

# Constants
INITIAL_TEMP = 30.0
FINAL_TEMP = 0.1
MAX_ITER = 1000

# Function to calculate the energy of a given state
def generateInitialSolution(n):
    return [random.randint(0, 1) for _ in range(n)]

# Function to generate an initial random solution
def calculateEnergy(state, graph):
    energy = 0
    n = len(state)
    for i in range(n):
        for j in range(i + 1, n):
            if state[i] != state[j]:  # If vertices are in different sets
                energy += graph[i][j]  # Add the weight of the edge
    return energy

# Function to generate a neighbor by flipping a random vertex
def generateNeighbor(current_solution):
    neighbor = current_solution.copy()
    flip_index = random.randint(0, len(current_solution) - 1)
    neighbor[flip_index] = 1 - neighbor[flip_index]  # Flip the state
    return neighbor

# Function to cool down the temperature
def coolDown(temperature):
    return temperature * 0.99  # Simple cooling schedule

# Function to perform simulated annealing
def simulatedAnnealing(graph):
    
    n = len(graph)
    
    currentSolution = generateInitialSolution(n)
    bestSolution = currentSolution
    temperature = INITIAL_TEMP
    bestEnergy = calculateEnergy(currentSolution, graph)

    #while temperature > FINAL_TEMP:
    for _ in range(MAX_ITER):
        newSolution = generateNeighbor(currentSolution)
        newEnergy = calculateEnergy(newSolution, graph)

        deltaEnergy = newEnergy - bestEnergy

        # Acceptance criterion
        if deltaEnergy <= 0:
            currentSolution = newSolution
            bestEnergy = newEnergy

        elif deltaEnergy > 0 or random() < math.exp(-deltaEnergy / temperature):
            currentSolution = newSolution

        # Update best solution
        if calculateEnergy(currentSolution, graph) < bestEnergy:
            bestEnergy = calculateEnergy(currentSolution, graph)
            bestSolution = currentSolution

        temperature = coolDown(temperature)

    return bestSolution, bestEnergy



if __name__ == "__main__":
    
    graph = [
        [0, 1, 1, 0, 0],  # Edges for vertex 0
        [1, 0, 0, 1, 1],  # Edges for vertex 1
        [1, 0, 0, 1, 0],  # Edges for vertex 2
        [0, 1, 1, 0, 1],  # Edges for vertex 3
        [0, 1, 0, 1, 0]   # Edges for vertex 4
    ]

    best_solution, best_energy = simulatedAnnealing(graph)

    print("Best Cut Energy:", best_energy)
    print("Best State:", best_solution)
