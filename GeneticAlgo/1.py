import random
import math
import tsp
if __name__ == "__main__"
    # Configuration
    POPULATION_SIZE = 200
    TOURNAMENT_SELECTION_SIZE = 4
    MUTATION_RATE = 0.1
    CROSSOVER_RATE = 0.9
    TARGET = 0.0

    # Generate cities
    cities = []
    for i in range(50):
        city = tsp.Gene((random.randint(1, 100), random.randint(1, 100)), i + 1)
        cities.append(city)

    # Initialize solver
    solver = tsp.TSPGeneticSolver(None, POPULATION_SIZE, MUTATION_RATE, CROSSOVER_RATE, TARGET, cities)

    # Initial population and first fittest individual
    population, firstFittest = solver.selection()

    # Evolve the population
    generation = 0
    while True:
        fittestRoute = solver.evolve()
        generation += 1
        if generation % 20 == 0:
            print(f'Generation {generation}, Distance: {fittestRoute[0]}')
        if fittestRoute[0] <= TARGET:
            break

    print("\n------------------------------------------------")
    print(f"Generations: {generation}")
    print(f"Initial fittest distance: {firstFittest[0]}")
    print(f"Final fittest distance: {fittestRoute[0]}")
    print(f"Target distance: {TARGET}")
    print("------------------------------------------------\n")

    drawMap(cities, fittestRoute)