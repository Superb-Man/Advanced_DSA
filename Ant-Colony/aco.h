#include "Utils.h"


class ACO {
public:
    ACO(int ants, int cities, double alpha, double beta, double rho, double q, double tau, std::vector<std::vector<double>> distances) {
        this->ants = ants;
        this->cities = cities;
        this->alpha = alpha;
        this->beta = beta;
        this->rho = rho;
        this->q = q;
        this->tau = tau;
        this->distances = distances;
        initPheromones();
        initProbabilities();
    }

    void initPheromones() {
        //
        // for (int i = 0; i < cities; ++i) {
        //     for (int j = 0; j < cities; ++j) {
        //         pheromones[i][j] = tau;
        //     }
        // }
        pheromones.resize(cities, std::vector<double>(cities, tau));
    }

    void initProbabilities() {
        probabilities.resize(cities , std::vector<double>(cities, 0.0));
    }

    //define a phi function for visibility
    double phi(int city1, int city2) {
        return 1.0 / distances[city1][city2];
    }

    //Pheromone update rule

    void updatePheromones(std::vector<int> &antPath, double route_length) {
        for (int i = 0; i < cities; i++) {
            int from = antPath[i];
            int to = antPath[(i+1) % cities];
            pheromones[from][to] += q / route_length;
            pheromones[to][from] = pheromones[from][to];
        }
    }

    //Evaporation rule

    void evaporatePheromones() {
        for (int i = 0; i < cities; ++i) {
            for (int j = 0; j < cities; ++j) {
                pheromones[i][j] *= (1.0 - rho);
            }
        }
    }


    void updateProbabilities() {
        for (int i = 0; i < cities; i ++) {
            double sum = 0.;
            for (int j = 0; j < cities; j++) {
                // if there's an edge exist!
                if (i !=j && distances[i][j] > 0) 
                    sum += (std::pow(pheromones[i][j],alpha) * std::pow(phi(i,j),beta));
                else 
                    probabilities[i][j] = 0.;
            }

            //normalizing now
            for (int j = 0; j < cities; j++) {
                probabilities[i][j] /= (sum > 0) ? sum : 1.; 
            }
        }
    }

    //Select the next city to visit  based on probability!

    int selectNextCity(std::vector<bool> &visited, int current_city, std::vector<int> &shuffleedCities) {
        std::vector<std::pair<double,int>> city_prob;

        for (int i = 0; i < cities; i++) {
            //same like antPath.find(i)
            if (!visited[shuffleedCities[i]] && distances[current_city][shuffleedCities[i]]) {
                city_prob.push_back({probabilities[current_city][shuffleedCities[i]], shuffleedCities[i]});
            }
        }

        //if no unvisited city in reachable
        if (city_prob.empty()) {
            return -1;
        }

        double sum = 0.;
        for (const auto &[prob, city] : city_prob) {
            sum += prob;
        } 

        double p = rand() / RAND_MAX;
        double cumSum = 0.;

        for (const auto &[prob, city] : city_prob) {
            cumSum += prob / sum;
            if (cumSum >= p) return city;
        }

        return city_prob.back().second;
        

    }

    //run ACO algorithm

    /**
     * @brief RUN ACO algorithm
     * 
     * @param iterations 
     */

    void run(int iterations) {
        double globalBestLength = INT_MAX * 1.0;
        std::vector<int>globalBestPath;

        
        for (int iter = 0; iter < iterations; iter++) {
            
            //initially high beta for visibility and low alpha for pheromone
            //gradually increase alpha
            updateAlphaBeta(iter, iterations);
            std::vector<int>bestPath;
            //update the probabilities
            updateProbabilities();
            double bestLength = INT_MAX * 1.0;
            int PathCount = 0;

            for (int ant = 0; ant < ants; ant++) {
                std::vector<bool>visited(cities, false);
                std::vector<int>antPath;
                
                std::vector<int>shuffleedCities ;
                for (int i = 0; i < cities; i++) {
                    shuffleedCities.push_back(i);
                }
                //initialize the ant path with a random city
                int startCity = randomNumber(cities) % cities;
                antPath.push_back(startCity);
                visited[startCity] = true;

                //shuffle the cities
                std::random_shuffle(shuffleedCities.begin(), shuffleedCities.end());

                int nextCity = -1;
                while (antPath.size() < cities) {
                    //get the next city
                    nextCity = selectNextCity(visited, antPath.back(), shuffleedCities); 
                    if (nextCity == -1) break;

                    antPath.push_back(nextCity);
                    visited[nextCity] = true;
                }

                if (distances[startCity][nextCity] == 0.) {
                    continue;
                }

                // std::cout << "Ant Path size: " << antPath.size() << std::endl; 

                if (antPath.size() == cities) {

                    double length = calcLength(antPath);

                    if (length < bestLength) {
                        bestLength = length;
                        bestPath = antPath;
                    }
                    PathCount++;

                    // std::cout << "Path length: " << length << std::endl;

                    updatePheromones(antPath, length);
                }
            }

            if (bestLength < globalBestLength) {
                globalBestLength = bestLength;
                globalBestPath = bestPath;
            }
            std::cout << "<-----------------------Iteration: " << iter << "----------------------->" << std::endl; 
            std::cout << "<-----------------------Path Count: " << PathCount << "----------------------->" << std::endl;
            std::cout << "<-----------------------BEST PATH LENGTH: " << bestLength << "----------------------->" << std::endl;
            printPath(bestPath);
            std::cout << std::endl ;
            evaporatePheromones();
        }
        std::cout << "<-----------------------GLOBAL BEST PATH LENGTH: " << globalBestLength << "----------------------->" << std::endl;

        printPath(globalBestPath);
    }




private:
    int ants; 
    int cities; 
    double alpha; // pheromone factor
    double beta; // visibility factor
    double rho; // evaporation rate
    double q; // pheromone deposit factor
    double tau; // initial pheromone level

    std::vector<std::vector<double>> pheromones;
    std::vector<std::vector<double>> distances; // distance between cities , if no edge then -1.
    std::vector<std::vector<double>> probabilities; // probability of moving from one city to another
    std::vector<std::vector<int>> ants_path; // path of each ant

    void printPath(std::vector<int> path) {
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }

    double calcLength(std::vector<int> path) {
        double length = 0.;
        for (int i = 0; i < path.size() - 1; i++) {
            if (distances[path[i]][path[i+1]] == 0.) {
                return INT_MAX * 1.0;
            }
            length += distances[path[i]][path[i+1]];
        }
        length += distances[path.back()][path[0]];
        return length;
    }

    void updateAlphaBeta(int iter, int max_iter) {
        double alpha_start = 1.0;
        double alpha_end = 5.0;
        double beta_start = 5.0;
        double beta_end = 2.0;
        double lambda = 5.0;

        alpha = alpha_start + (alpha_end - alpha_start) * (1.0 - exp(-lambda * (iter * 1.) / max_iter));
        //beta should decrease
        beta = beta_end + (beta_end - beta_start) * exp(-lambda * (iter * 1.) / max_iter);
        std::cout << "Alpha: " << alpha << " Beta: " << beta << std::endl;
    }


};


