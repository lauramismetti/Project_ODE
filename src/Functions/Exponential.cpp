/** \file
 * @brief Declaration of the methods of the class Exponential for the RHS
 */

#include "Exponential.h"

///@brief return the values of y=f(x, t) = exp(x)
Eigen::VectorXd Exponential::f(const Eigen::VectorXd &x, const double &t) const {
    return x.array().exp().matrix();
}

///@brief return the values of y'=df(x,t)/dx = exp(x) (can be useful for Backward Euler using Newton's method)
Eigen::VectorXd Exponential::df(const Eigen::VectorXd &x, const double &t) const {
    return x.array().exp().matrix();
}