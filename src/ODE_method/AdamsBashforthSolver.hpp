/**\file
 * @brief Definition of the class AdamsBashforthSolver
 * It solves the ODE by using the Adams Bashforth method.
 */

#ifndef ADAMSBASHFORTHSOLVER_H
#define ADAMSBASHFORTHSOLVER_H

#include "ForwardEulerSolver.hpp"
#include <memory>

/// @brief Class to solve the equation by using Adams-Bashforth method

class AdamsBashforthSolver : public ForwardEulerSolver {
public:
    // Constructor and destructor
    AdamsBashforthSolver() = default;
    // Constructor which calls the mother constructor which sets all the members of the class
    /// @brief Constructor which sets all the members
    AdamsBashforthSolver(string name, double deltat, int steps, double t0, Eigen::VectorXd y0, shared_ptr<RH_function> ptr)
    : ForwardEulerSolver(name, deltat, steps, t0, y0, ptr) {};
    virtual ~AdamsBashforthSolver() = default;

    //Other methods
    std::map<double, Eigen::VectorXd> SolveOde() override;
};

#endif // ADAMSBASHFORTHSOLVER_H
