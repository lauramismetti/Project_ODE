/** \file
 * @brief Definition of the methods of the class T_square for the RHS
 */

#include "T_square.h"


///@brief return the values of y=f(x, t)= t^2 - x
Eigen::VectorXd T_square::f(const Eigen::VectorXd &x, const double &t) const {
    long dim=x.size();
    Eigen::VectorXd computed_value(dim);
    computed_value = Eigen::VectorXd::Ones(dim) * pow(t,2);
    return computed_value - x ;
}

///@brief return the values of y'=df(x,t)/dx = -1 (can be useful for Backward Euler using Newton's method)
Eigen::VectorXd T_square::df(const Eigen::VectorXd &x, const double &t) const {
    long dim=x.size();
    Eigen::VectorXd computed_value(dim);
    computed_value = Eigen::VectorXd::Ones(dim) * -1;
    return computed_value;
}
