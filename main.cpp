#include <iostream>
#include "blackbox/function.h"
#include "epsilon/epsilon.h"

int main(int argc, char **argv) {
    // {1, 2, 3}
    for (double q : {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}) {
        std::vector<double> data{q, 1 + q, 2 + q};
        std::vector<double> x;
        std::vector<double> y;
//    std::vector<double> data{1, 2, 3};
        for (double exponent : data) {
            double epsilon = pow(10, -exponent);
            x.push_back(log(epsilon));
            y.push_back(-log(complexity(epsilon)));
        }

        double slope1 = (y[1] - y[0]) / (x[1] - x[0]);
        double slope2 = (y[2] - y[1]) / (x[2] - x[1]);
        std::cout << q << ", " << (slope1 + slope2) / 2 << std::endl;

//    for(int i=0; i < x.size(); i++)
//        std::cout << x.at(i) << ' ';
//
//    std::cout << std::endl;
//
//    for(int i=0; i < y.size(); i++)
//        std::cout << y.at(i) << ' ';

    }
    return 0;
}
