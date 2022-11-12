/** \file
 * @brief Definition of the methods of the class RH_function which defines the right hand side of the ODE
 */

#include "RH_function.h"


Eigen::VectorXd RH_function::f(const Eigen::VectorXd &x, const double &t) const {
    return x;
}

Eigen::VectorXd RH_function::df(const Eigen::VectorXd &x, const double &t) const {
	long dim=x.size();
    return Eigen::VectorXd::Ones(dim);
}

string RH_function::GetName() const {return name ;}
