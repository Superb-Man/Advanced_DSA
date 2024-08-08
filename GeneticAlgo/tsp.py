import random
import math
import matplotlib.pyplot as plt

# Gene means a city
class Gene:
    def __init__(self, coord2D, label):
        # Initialize a gene (city) with coordinates and label
        self.coord2D = coord2D
        self.label = label
        self.neighbours = []

    def addNeighbour(self, neighbour):
        # Add a neighbour to the city
        self.neighbours.append(neighbour)

class TSPGeneticSolver:
    def __init__(self, leaderBoard, populationSize, mutationRate, crossoverRate, target, cities):
        # Initialize the genetic algorithm solver with parameters
        self.leaderBoard = leaderBoard
        self.populationSize = populationSize
        self.mutationRate = mutationRate
        self.crossoverRate = crossoverRate
        self.target = target
        self.cities = cities  # list of cities (genes)
        self.populationRoutes = []

    def getDistance(self, city1, city2):
        # Calculate the Euclidean distance between two cities
        return math.sqrt((city1.coord2D[0] - city2.coord2D[0]) ** 2 + (city1.coord2D[1] - city2.coord2D[1]) ** 2)

    def getDistanceFromRoute(self, route):
        # Calculate the total distance of a given route
        distance = 0
        for i in range(len(route) - 1):
            distance += self.getDistance(route[i], route[i + 1])
        # Add distance to return to the starting point
        distance += self.getDistance(route[-1], route[0])
        return distance

    def getFittest(self, population):
        # Get the fittest
        fittest = population[0]
        for i in range(1, len(population)):
            if population[i][0] < fittest[0]:
                fittest = population[i]
        return fittest

    def selection(self):
        # Create initial population 
        for _ in range(self.populationSize):
            c = self.cities.copy()
            random.shuffle(c)
            distance = self.getDistanceFromRoute(c)
            self.populationRoutes.append([distance, c])

        fittestRoute = self.getFittest(self.populationRoutes)
        return self.populationRoutes, fittestRoute

    def crossover(self, parent1, parent2):
        # Perform crossover between two parent routes to generate offspring
        point = random.randint(0, len(parent1) - 1)
        child1 = []
        for gene in parent1[:point]:
            child1.append(gene)

        for gene in parent2:
            if gene not in child1:
                child1.append(gene)

        child2 = []
        for gene in parent2[:point]:
            child2.append(gene)

        for gene in parent1:
            if gene not in child2:
                child2.append(gene)

        return child1, child2

    def mutate(self, chromosome):
        # Mutate a chromosome by swapping two genes with a certain probability
        if random.random() < self.mutationRate:
            point1, point2 = random.sample(range(len(chromosome)), 2)
            chromosome[point1], chromosome[point2] = chromosome[point2], chromosome[point1]
        return chromosome

    def evolve(self, sharing=False):
        new_population = []

        # keep the best two solutions
        new_population.append(self.getFittest(self.populationRoutes))
        new_population.append(self.getFittest(self.populationRoutes))

        for _ in range(int((self.populationSize - 2) / 2)):
            parent1 = random.choice(self.populationRoutes)[1]
            parent2 = random.choice(self.populationRoutes)[1]
            child1, child2 = self.crossover(parent1, parent2)

            child1 = self.mutate(child1)
            child2 = self.mutate(child2)

            new_population.append([self.getDistanceFromRoute(child1), child1])
            new_population.append([self.getDistanceFromRoute(child2), child2])

        self.populationRoutes = new_population
        fittestRoute = self.getFittest(self.populationRoutes)
        return fittestRoute


def drawMap(cities, answer):
    # Plot the cities and the best route found
    for city in cities:
        plt.plot(city.coord2D[0], city.coord2D[1], 'ro')
        plt.annotate(city.label, (city.coord2D[0], city.coord2D[1]))

    route = answer[1]
    for i in range(len(route)):
        plt.plot([route[i].coord2D[0], route[(i + 1) % len(route)].coord2D[0]],
                 [route[i].coord2D[1], route[(i + 1) % len(route)].coord2D[1]], 'gray')

    plt.show()
