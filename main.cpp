#include <iostream>
#include "blackbox/function.h"
#include "epsilon/epsilon.h"

double cos2Pi(double f) {
    return std::cos(f * M_PI * 2);
}

double sin2Pi(double f) {
    return std::sin(f * M_PI * 2);
}

double f3(double f) {
    return f * f;
}

double f32(double f) {
    return f * f * f;
}

double f4(double f) {
    return std::sqrt(f);
}

double f5(double f) {
    return std::cbrt(f);
}

std::pair<double, double> runComplexity(double f(double)) {
    std::vector<double> data{1, 2, 3};
//    std::vector<double> data{1, 2, 3};
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> coeffs;
    for (double exponent : data) {
        double epsilon = pow(10, -exponent);
        x.push_back(log(epsilon));
        y.push_back(-log(complexity(epsilon, f)));
    }

    PolynomialRegression<double>().fitIt(x, y, 1, coeffs);

    double A = coeffs.at(0);
    double B = coeffs.at(1);

    for (double _ : y) {
        std::cout << _ << " ";
    }

    std::cout << std::endl;

    return {A, B}; // A + B log e
}

int main(int argc, char **argv) {
    auto sinComp = runComplexity(sin2Pi);
    auto cosComp = runComplexity(cos2Pi);
    auto f3Comp = runComplexity(f3);
    auto f32Comp = runComplexity(f32);
    auto f4Comp = runComplexity(f4);
    auto f5Comp = runComplexity(f5);

    std::cout << "cos: " << cosComp.first << " + " << cosComp.second << " log e" << "\n"
              << "sin: " << sinComp.first << " + " << sinComp.second << " log e" << "\n"
              << "x^2: " << f3Comp.first << " + " << f3Comp.second << " log e" << "\n"
              << "x^3: " << f32Comp.first << " + " << f32Comp.second << " log e" << "\n"
              << "sqrt(x): " << f4Comp.first << " + " << f4Comp.second << " log e" << "\n"
              << "cbrt(x): " << f5Comp.first << " + " << f5Comp.second << " log e" << "\n"
              << std::endl
              ;
    return 0;
}
