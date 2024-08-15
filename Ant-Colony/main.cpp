#include "aco.h"



int main() {
    //make random distance matrix of 25 * 25 matrix

    int cities = 64 ;
    int ants = 1000;
    double alpha = 1.0;
    double beta = 3.0;
    double rho = 0.2;
    double q = 100.0;
    double tau = 0.1;

    std::vector<std::vector<double>> distances(1000, std::vector<double>(cities, 0.));
    freopen("1.txt", "r", stdin);
    for (int i = 0; i <cities ; ++i) {
        for (int j = 0; j <cities; ++j) {
            // if (i == j) {
            //     distances[i][j] = 0.;
            //     continue;
            // }
            // if(i%2 == j%4 || j%2 == i%4) {
            //     distances[i][j] = 0.;
            //     distances[j][i] = distances[i][j];
            //     continue;
            // }
            // if (distances[i][j]) {
            //     continue;
            // }
            // distances[i][j] = (randomNumber(10)) *1.;
            // distances[j][i] = distances[i][j];
            std::cin >> distances[i][j];
        }
        // std::cout << std::endl;
    }

    //print the distance matrix
    for (int i = 0; i < cities; ++i) {
        for (int j = 0; j < cities; ++j) {
            std::cout << distances[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    ACO aco(ants, cities, alpha, beta, rho, q, tau, distances);
    aco.run(1000);
}