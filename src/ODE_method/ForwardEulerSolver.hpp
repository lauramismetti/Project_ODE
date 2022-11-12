/**\file
 * @brief Definition of the class ForwardEulerSolver
 * It solves the ODE by using the Forward Euler method.
 */

#ifndef FORWARDEULERSOLVER_H
#define FORWARDEULERSOLVER_H

#include <Eigen/Dense>
#include "AbstractOdeSolver.hpp"
///@brief Class to solve the ODE by using Forward Euler method
class ForwardEulerSolver : public AbstractOdeSolver {
public:
    // Constructor and destructor
    ForwardEulerSolver() = default;
    // Constructor by setting all the members
    ///@brief Constructor which sets all the members of the class
    ForwardEulerSolver(string name, double deltat, int steps, double t0, Eigen::VectorXd y0, shared_ptr<RH_function> ptr)
        : AbstractOdeSolver(name, deltat, steps, t0, y0, ptr) {};
    ~ForwardEulerSolver() = default;

    //Other methods
    Eigen::VectorXd CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev) override;
    std::map<double, Eigen::VectorXd> SolveOde() override;

};

#endif // FORWARDEULERSOLVER_H
