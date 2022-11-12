/** \file
 * @brief Declaration of the class Exponential for the RHS
 */

#ifndef ODE_PROJECT_EXPONENTIAL_H
#define ODE_PROJECT_EXPONENTIAL_H

#include "RH_function.h"

/// @brief Class for the right hand side function defined as f(y,t)=2*t*y + 3*y^2 + 4
class Exponential : public RH_function{
public :
    //Constructor and destructor
    Exponential(const string &name_) : RH_function(name_) {} ;
    ~Exponential() = default;

    ///@brief return the values of y=f(x, t)=exp(x)
    Eigen::VectorXd f(const Eigen::VectorXd &x, const double &t) const override ;

    ///@brief return the values of y'=df(x,t)/dx = exp(x) (can b useful for Backward Euler using Newton's method)
    Eigen::VectorXd df(const Eigen::VectorXd &x, const double &t) const override ;
};


#endif //ODE_PROJECT_EXPONENTIAL_H
