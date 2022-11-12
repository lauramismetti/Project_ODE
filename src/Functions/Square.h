/** \file
 * @brief Declaration of the class Square for the RHS
 */

#ifndef ODE_PROJECT_SQUARE_H
#define ODE_PROJECT_SQUARE_H

#include "RH_function.h"

/// @brief Class for the right hand side function which returns a vector with the square of each component of the input vector

class Square : public RH_function{
public :
    //Constructor and destructor
    Square(const string &name_) : RH_function(name_) {} ;
    ~Square() = default;

    ///@brief return the values of y=f(x, t) = x^2
    Eigen::VectorXd f(const Eigen::VectorXd &x, const double &t) const override ;

    ///@brief return the values of y'=df(x,t)/dx = 2*x (can b useful for Backward Euler using Newton's method)
    Eigen::VectorXd df(const Eigen::VectorXd &x, const double &t) const override ;
};


#endif //ODE_PROJECT_SQUARE_H
