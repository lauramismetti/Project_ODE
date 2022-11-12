/**\file
 * @brief Definition of the class RungeKuttaSolver
 * It solves the ODE by using the Runge-Kutta method.
 */

#ifndef RUNGEKUTTASOLVER_H
#define RUNGEKUTTASOLVER_H

#include <memory>
#include <Eigen/Dense>
#include "AbstractOdeSolver.hpp"

///@brief Class to solve the ODE by using the Runge-Kutta method of order 4 (known as RK4)
class RungeKuttaSolver : public AbstractOdeSolver {
public:
    // Constructor and destructor
    RungeKuttaSolver() = default;
    // Constructor which calls the mother constructor which sets all the members of the class
    ///@brief Constructor which sets all the members of the class
    RungeKuttaSolver(string name, double deltat, int steps, double t0, Eigen::VectorXd y0, shared_ptr<RH_function> ptr)
    : AbstractOdeSolver(name, deltat, steps, t0, y0, ptr) {};
    ~RungeKuttaSolver() = default;

    //Other methods
    Eigen::VectorXd CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev) override;
    std::map<double, Eigen::VectorXd> SolveOde() override;

};

#endif // RUNGEKUTTASOLVER_H
