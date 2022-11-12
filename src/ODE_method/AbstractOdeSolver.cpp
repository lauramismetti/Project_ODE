/**\file
 * @brief Definition of the methods of the class AbstractOdeSolver
 */

#include "AbstractOdeSolver.hpp"
#include <string>

using namespace std;

// Constructor and destructor
AbstractOdeSolver::AbstractOdeSolver(const string& name, const double& deltat, const int& steps, const double &t0, const Eigen::VectorXd& y0, shared_ptr<RH_function> ptr){
    timestep_=deltat;
    numbersteps_=steps;
    initialtime_=t0;
    initialvalue_=y0;
    name_method=name;
    ptr_f=ptr;
}

//Set methods
void AbstractOdeSolver::SetTimeStep(const double& h) {timestep_ = h;}
void AbstractOdeSolver::SetNumberSteps(const int& n) {numbersteps_=n;}
void AbstractOdeSolver::SetInitialTime(const double& t0) {initialtime_=t0;}
void AbstractOdeSolver::SetInitialValue(const Eigen::VectorXd& y0) {initialvalue_=y0;}
void AbstractOdeSolver::SetFunction(shared_ptr<RH_function> ptr_f_){ ptr_f = ptr_f_ ;}
void AbstractOdeSolver::SetName(const string& name_){name_method = name_ ;}

//Get methods
double AbstractOdeSolver::GetTimeStep() const {return timestep_;}
int AbstractOdeSolver::GetNumberSteps() const {return numbersteps_;}
double AbstractOdeSolver::GetInitialTime() const {return initialtime_;}
Eigen::VectorXd AbstractOdeSolver::GetInitialValue() const {return initialvalue_;}
Eigen::VectorXd AbstractOdeSolver::GetValueFunction(const Eigen::VectorXd& y, const double& t) const {return ptr_f ->f(y, t);}
Eigen::VectorXd AbstractOdeSolver::GetDerivativeFunction(const Eigen::VectorXd& y, const double& t) const {return ptr_f ->df(y, t);}
string AbstractOdeSolver::GetNameMethod() const {return name_method ;}
string AbstractOdeSolver::GetNameFunction() const { return ptr_f -> GetName() ;}

//Other
double AbstractOdeSolver::CalculateNextTimeStep(const double& t_prev) const{
    return t_prev + timestep_;
}