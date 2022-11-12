/**\file
 * @brief Definition of the class BackwardEulerSolver
 * It solves the ODE by using the Backward Euler method.
 */

#ifndef BACKWARDEULERSOLVER_H
#define BACKWARDEULERSOLVER_H

#include <memory>
#include <Eigen/Dense>
#include "AbstractOdeSolver.hpp"

///@brief Class to solve the ODE by using the Backward Euler method
class BackwardEulerSolver : public AbstractOdeSolver {
public:
    // Constructor and destructor
    BackwardEulerSolver() = default;
    // Constructor by calling the mother constructor which sets all the members of the class
    ///@brief Constructor which sets all the members
    BackwardEulerSolver(string name, double deltat, int steps, double t0, Eigen::VectorXd y0, shared_ptr<RH_function> ptr)
    : AbstractOdeSolver(name, deltat, steps, t0, y0, ptr) {};
    ~BackwardEulerSolver() = default;

    //Other methods
    ///@brief Compute the approximation of a value by using the Newton method
    ///It is necessary because the Backward Euler method is implicit, then is necessary to approximate the value
    /// of y in the next step, before computing it by the chosen method.
    Eigen::VectorXd CalculateNewton(const Eigen::VectorXd& x, const double t);
    /// @brief Compute the next step by using the Backward Euler method and approximating y at the next step by Newton method
    Eigen::VectorXd CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev) override;
    std::map<double, Eigen::VectorXd> SolveOde() override;

};

#endif // BACKWARDEULERSOLVER_H
