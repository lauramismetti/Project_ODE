/** \file
 * @brief Declaration of the class RH_function which defines the right hand side of the ODE
 */

#ifndef ODE_PROJECT_RH_FUNCTION_H
#define ODE_PROJECT_RH_FUNCTION_H

#include "../../eigen/Eigen/Dense"

using namespace std ;

///@brief Mother class for the right hand sight function in the ODE equation y'(t) = f(y(t), t)
/// This is also the "default" right hand side function

class RH_function {
public :
    //Constructor
    RH_function(const string& name_) : name(name_) {}
    //Destructor
    virtual ~RH_function() = default ;

    ///@brief return the values of y=f(x, t) = x
    virtual Eigen::VectorXd f(const Eigen::VectorXd &x, const double &t) const;

    ///@brief return the values of y'=df(x,t)/dx = 1 (can b useful for Backward Euler using Newton's method)
    virtual Eigen::VectorXd df(const Eigen::VectorXd &x, const double &t) const ;

    ///@brief return the name of the function
    string GetName() const ;

protected:
    ///@brief name of the function used (only used for the display of the output) : t_square, y_square
    string name ;
    //Possible parameters of the right hand side function (coefficients of a polynomial function, ...)
};


#endif //ODE_PROJECT_RH_FUNCTION_H
