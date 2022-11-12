/** \file
 * @brief Declaration of the class Polynomial for the RHS
 */

#ifndef ODE_PROJECT_POLYNOMIAL_H
#define ODE_PROJECT_POLYNOMIAL_H

#include "RH_function.h"

/// @brief Class for the right hand side function defined as f(y,t)=2*t*y + 3*y^2 + 4
class Polynomial : public RH_function{
public :
    //Constructor and destructor
    Polynomial(const string &name_) : RH_function(name_) {} ;
    ~Polynomial() = default;

    ///@brief return the values of y=f(x, t) = 2*t*x + 3*x^2 + 4*Id
    Eigen::VectorXd f(const Eigen::VectorXd &x, const double &t) const override ;

    ///@brief return the values of y'=df(x,t)/dx = 2*t + 6*x (can be useful for Backward Euler using Newton's method)
    Eigen::VectorXd df(const Eigen::VectorXd &x, const double &t) const override ;
};


#endif //ODE_PROJECT_POLYNOMIAL_H
