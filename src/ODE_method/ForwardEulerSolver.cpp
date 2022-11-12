/**\file
 * @brief Implementation of the methods of class ForwardEulerSolver
 */

#include "ForwardEulerSolver.hpp"
using namespace std;


Eigen::VectorXd ForwardEulerSolver::CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev){
    return y_prev + timestep_* GetValueFunction(y_prev, t_prev);
}


std::map<double, Eigen::VectorXd> ForwardEulerSolver::SolveOde() {
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