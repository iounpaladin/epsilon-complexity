#include "epsilon.h"
#include <iostream>

#define MAX_ALGORITHM_STEPS 1000

double stepBasedMaximum(double f(double)) {
    double maximum = 0; // we assume maximum is > 0

    for (int i = 0; i < MAX_ALGORITHM_STEPS; i++) { // 1000 steps
        if (f((double)i / MAX_ALGORITHM_STEPS) > maximum) { // not necessarily increasing so this is fine
            maximum = f((double)i / MAX_ALGORITHM_STEPS);
        }
    }

    return maximum;
}

/**
 * Main file to calculate epsilon-complexity of an arbitrary (black-boxed) function
 * For now, only works on R -> R
 */

double complexity(double epsilon, double (f(double))) {
    // use `function` as the black-boxed function
    // because this is one-dimensional, h*_x = h*_1, so we don't need to implement a separate function
    if (fNontrivial()) {
        double minimum = 2;
        double R = stepBasedMaximum(f); // find R

//        for (int i = ceil(1 / epsilon); i > 0; i--) { // 1000 steps
//            double h = (double)i / ceil(1 / epsilon);
//            if (delta(h, f) / R > epsilon && h < minimum) {
//                minimum = h;
////                return h; // testing
//                // -0.693147 1.60944 4.60517 6.21461
//            }
//        }
        for (int i = 1; i <= ceil(1 / epsilon); i++) { // because delta is increasing in h this should be ok
            double h = (double)i / ceil(1 / epsilon);
            if (delta(h, f) / R > epsilon) {
                return h;
            }
        }

        return minimum; // smallest h such that delta_1(h, F) / R_1 > epsilon
    }

    return 1; // h* is defined as 1 for a F-trivial function
}

bool fNontrivial() {
    return true;
}

double applyPolynomial(std::vector<double> vector, double x) {
    double sum = 0;

    for (int i = 0; i < vector.size(); i++) {
        sum += vector[i] * pow(x, i);
    }

    return sum;
}

double delta(double h, double(f(double))) {
    int count = ceil(1 / h);
    std::vector<double> coeffs;
    std::vector<double> x;
    std::vector<double> y;

    for (int i = 0; i < count; i++) {
        x.push_back((double)i / count);
        y.push_back(f((double)i / count));
    }

    PolynomialRegression<double>().fitIt(x, y, count - 1, coeffs);

    double maximum = 0;

    for (int i = 0; i < MAX_ALGORITHM_STEPS; i++) { // 1000 steps
        double x = (double)i / MAX_ALGORITHM_STEPS;
        if (std::abs(f(x) - applyPolynomial(coeffs, x)) > maximum) {
            maximum = std::abs(f(x) - applyPolynomial(coeffs, x));
        }
    }

    return maximum; // largest difference between approximation and actual function over the unit cube ([0, 1] for us)
}