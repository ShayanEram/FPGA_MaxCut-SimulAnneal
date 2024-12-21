import networkx as nx
import matplotlib.pyplot as plt

# Define the adjacency matrix
matrix = [
    [0., 1., 1., 0., 0.],
    [1., 0., 0., 1., 1.],
    [1., 0., 0., 0., 0.],
    [0., 1., 0., 0., 1.],
    [0., 1., 0., 1., 0.]
]


# Create a graph
G = nx.Graph()

# Add edges based on the adjacency matrix
for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        if matrix[i][j] == 1:
            G.add_edge(i, j)

# Define the best state
best_state = [-1.0, 1.0, 1.0, -1.0, -1.0]

# Assign colors based on the best state
color_map = ['lightblue' if state == 1 else 'lightgreen' for state in best_state]

# Draw the graph
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_color=color_map, edge_color='gray')
plt.show()
