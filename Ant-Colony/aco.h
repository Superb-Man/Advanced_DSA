
#include<iostream>
#include<random>    


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

    void updatePheromones(std::vector<int> ant_path, double route_length) {
        for (int i = 0; i < cities - 1; ++i) {
            int city1 = ant_path[i];
            int city2 = ant_path[i + 1];
            pheromones[city1][city2] += q / route_length;
            pheromones[city2][city1] += q / route_length;
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

    int selectNextCity(std::vector<int> ant_path, int current_city) {
    }

    //run ACO algorithm

    /**
     * @brief RUN ACO algorithm
     * 
     * @param iterations 
     */

    void run(int iterations) {

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
};


