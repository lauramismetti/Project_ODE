/** \file
 * @brief Declaration of the methods of the class Polynomial for the RHS
 */

#include "Polynomial.h"

///@brief return the values of y=f(x, t) = 2*t*x + 3*x^2 + 4*Id
Eigen::VectorXd Polynomial::f(const Eigen::VectorXd &x, const double &t) const {
    return 2*t*x + 3*x.cwiseAbs2() + Eigen::VectorXd::Ones(x.size())*4;
}

///@brief return the values of y'=df(x,t)/dx = 2*t + 6*x (can be useful for Backward Euler using Newton's method)
Eigen::VectorXd Polynomial::df(const Eigen::VectorXd &x, const double &t) const {
    return Eigen::VectorXd::Ones(x.size())*2*t + 6*x;
}