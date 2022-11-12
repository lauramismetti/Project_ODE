/** \file
 * @brief Declaration of the class T_square for the RHS
 */

#ifndef ODE_PROJECT_T_SQUARE_H
#define ODE_PROJECT_T_SQUARE_H

#include "RH_function.h"
///@brief Class for the right hand side function which returns the square of the time for each component of the input vector
class T_square : public RH_function{
public :
    //Constructor and destructor
    T_square(const string &name_) : RH_function(name_) {} ;
    ~T_square() = default;

    ///@brief return the values of y=f(x, t)= t^2 - x
    Eigen::VectorXd f(const Eigen::VectorXd &x, const double &t) const override ;

    ///@brief return the values of y'=df(x,t)/dx = -1 (can b useful for Backward Euler using Newton's method)
    Eigen::VectorXd df(const Eigen::VectorXd &x, const double &t) const override ;
};


#endif //ODE_PROJECT_T_SQUARE_H

