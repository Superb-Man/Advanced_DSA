import pydot
from collections import defaultdict, deque

# Function to build De Bruijn graph
def build_de_bruijn_graph(seqs, k):
    graph = defaultdict(list)
    for seq in seqs:
        for i in range(len(seq) - k + 1):
            kmer = seq[i:i+k]
            prefix = kmer[:-1]
            suffix = kmer[1:]
            graph[prefix].append(suffix)
    return graph

# Function to find Eulerian path in a directed graph
def find_eulerian_path(graph):
    in_degree = defaultdict(int)
    out_degree = defaultdict(int)
    
    # Calculate in-degrees and out-degrees
    for node, neighbors in graph.items():
        out_degree[node] += len(neighbors)
        for neighbor in neighbors:
            in_degree[neighbor] += 1
    
    # Find start node for Eulerian path (where out-degree > in-degree)
    start_node = next((node for node, out in out_degree.items() if out > in_degree[node]), None)
    if not start_node:
        start_node = next(iter(graph))  # Fall back to any node if graph is Eulerian
    
    # Hierholzer’s algorithm to find Eulerian path
    path = []
    stack = [start_node]
    
    while stack:
        u = stack[-1]
        if out_degree[u]:
            v = graph[u].pop()
            out_degree[u] -= 1
            stack.append(v)
        else:
            path.append(stack.pop())
    
    path.reverse()
    return path

def merge_path(eulerian_path):
    return eulerian_path[0] + ''.join([node[-1] for node in eulerian_path[1:]])

# Function to visualize De Bruijn graph with Eulerian path
def visualize_de_bruijn_with_path(graph, eulerian_path, output_file):
    dot_graph = pydot.Dot(graph_type='digraph')
    
    # Add nodes
    for node in graph:
        dot_node = pydot.Node(node, shape='circle', style='filled', fillcolor='lightblue')
        dot_graph.add_node(dot_node)
    
    # Add edges
    for node, neighbors in graph.items():
        for neighbor in neighbors:
            dot_edge = pydot.Edge(node, neighbor, color='black')
            dot_graph.add_edge(dot_edge)
    
    # Highlight Eulerian path
    for i in range(len(eulerian_path) - 1):
        dot_edge = pydot.Edge(eulerian_path[i], eulerian_path[i+1], color='red', penwidth=2.0)
        dot_graph.add_edge(dot_edge)
    
    # Save dot file
    dot_graph.write(output_file, format='raw')
    # print(f"Dot file saved: {output_file}")

# Example usage
if __name__ == '__main__':
    num = input("How many sequences : ")
    sequences = [] 
    for i in range(int(num)):
        sequences.append(input(f"Enter sequence {i} : "))

    
    k = int(input("Enter k value for De Bruijn graph: "))

    de_bruijn_graph = build_de_bruijn_graph(sequences, k)
    eulerian_path = find_eulerian_path(de_bruijn_graph)
    print("Eulerian Path:", merge_path(eulerian_path))
    visualize_de_bruijn_with_path(de_bruijn_graph, eulerian_path, 'de_bruijn_graph_with_eulerian_path.dot')
