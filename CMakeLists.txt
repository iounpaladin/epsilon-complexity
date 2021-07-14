cmake_minimum_required(VERSION 3.19)
project(epsilon_complexity)

set(CMAKE_CXX_STANDARD 20)

add_executable(epsilon_complexity main.cpp blackbox/function.h blackbox/function.cpp blackbox/blackbox.h epsilon/epsilon.cpp epsilon/epsilon.h epsilon/recovery_basis.cpp epsilon/recovery_basis.h thirdparty/PolynomialRegression.h)