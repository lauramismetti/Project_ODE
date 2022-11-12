/** \file
 * @brief Declaration of the methods of the class Square for the RHS
 */

#include "Square.h"

#include <cmath>


///@brief return the values of y=f(x, t) = x^2
Eigen::VectorXd Square::f(const Eigen::VectorXd &x, const double &t) const {
    return x.cwiseAbs2() ;
}

///@brief return the values of y'=df(x,t)/dx = 2*x (can be useful for Backward Euler using Newton's method)
Eigen::VectorXd Square::df(const Eigen::VectorXd &x, const double &t) const {
    return 2*x ;
}