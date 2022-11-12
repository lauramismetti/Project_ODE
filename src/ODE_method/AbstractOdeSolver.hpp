/** \file
 * @brief Definition of the abstract class to solve the ODE.
 * From this class, different daughter classes are derived to solve the ODE by using
 * one specific method.
 */

#ifndef ABSTRACTODESOLVER_H
#define ABSTRACTODESOLVER_H

#include <Eigen/Dense>
#include <iostream>
#include <map>
#include <memory>

#include "../Functions/RH_function.h"

using namespace std ;
///@brief Virtual mother class to solve the ODE
//Fully abstract class
class AbstractOdeSolver {
public:
    // Constructor and destructor
    // Default constructor
    AbstractOdeSolver() = default;
    /// @brief Constructor which sets all the members of the class
    AbstractOdeSolver(const string& name, const double& deltat, const int& steps, const double &t0, const Eigen::VectorXd& y0, shared_ptr<RH_function> ptr);
    virtual ~AbstractOdeSolver() = default;

    //Set methods
    void SetTimeStep(const double& h);
    void SetNumberSteps(const int& n);
    void SetInitialTime(const double& t0);
    void SetInitialValue(const Eigen::VectorXd& y0);
    /// @brief Set the pointer to the right hand side function (f(y,t)) of the equation
    void SetFunction(shared_ptr<RH_function> ptr_f_) ;
    /// @brief Set the name of the method used to solve the ODE
    void SetName(const string& name_) ;

    //Get methods
    double GetTimeStep()const;
    int GetNumberSteps()const;
    double GetInitialTime()const;
    Eigen::VectorXd GetInitialValue()const;
    /// @brief It evaluate the right hand side function (f(y,t)) in the point
    /// @param t
    /// @param y
    Eigen::VectorXd GetValueFunction(const Eigen::VectorXd& y, const double& t) const;
    /// @brief It evaluate the derivative of the right hand side function (f(y,t)) in the point
    /// @param t
    /// @param y
    Eigen::VectorXd GetDerivativeFunction(const Eigen::VectorXd& y, const double& t) const;

    string GetNameMethod() const ;
    string GetNameFunction() const ;

    //Other methods
    /**
     * @brief Virtual method of the class, it computes the following step by using a specific method (override in the daughter classes)
     * \return the new y after 1 time step
     */
    virtual Eigen::VectorXd CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev)=0;

    /**
     * @brief Compute the following time step t_new = t_previous + time_step
     * \return the new t after 1 time step
     */

    double CalculateNextTimeStep(const double& t_prev) const ;

    /**
     * @brief Virtual method to solve the ODE by computing the list of values of the function $y$ at different time steps.
     * \return The solutions y for each time step
     */
    virtual std::map<double, Eigen::VectorXd> SolveOde() = 0;

protected://members of the class
    /// @brief Name of the method used to compute the solution
    string name_method;
    double timestep_;
    int numbersteps_;
    double initialtime_;
    Eigen::VectorXd initialvalue_;
    /// @brief Pointer to the right hand side function f(t,y)
    shared_ptr<RH_function> ptr_f ;
};

#endif //ABSTRACTODESOLVER_H
