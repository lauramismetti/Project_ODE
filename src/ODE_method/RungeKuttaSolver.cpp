/**\file
 * @brief Implementation of the methods of the class RungeKuttaSolver
 */

#include "RungeKuttaSolver.hpp"
using namespace std;

Eigen::VectorXd RungeKuttaSolver::CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev){

    Eigen::VectorXd k1, k2, k3, k4;
    k1=GetValueFunction(y_prev,t_prev+ timestep_);
    k2=GetValueFunction(y_prev+timestep_*k1/2, t_prev+timestep_/2);
    k3=GetValueFunction(y_prev+timestep_*k2/2 , t_prev+timestep_/2);
    k4=GetValueFunction(y_prev+timestep_*k3, t_prev+timestep_);

    return y_prev + 1./6.*timestep_ *(k1+ 2*k2+ 2*k3+ k4);
}


std::map<double, Eigen::VectorXd> RungeKuttaSolver::SolveOde() {
    Eigen::VectorXd y_k=GetInitialValue();
    Eigen::VectorXd y_k1;
    double t_k=GetInitialTime();
    double t_k1;
    std::map<double, Eigen::VectorXd> map_solution;

    map_solution.insert({t_k, y_k});
    for(int i=0; i<numbersteps_; i++){
        y_k1 = CalculateNextStep(y_k, t_k);
        t_k1 = CalculateNextTimeStep(t_k);
        map_solution.insert({t_k1, y_k1});
        y_k = y_k1;
        t_k = t_k1;
    }

    return map_solution;
}
