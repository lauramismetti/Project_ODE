/**\file
 * @brief Implementation of the methods of the class BackwardEulerSolver
 */

#include <cmath>
#include "BackwardEulerSolver.hpp"
using namespace std;

Eigen::VectorXd BackwardEulerSolver::CalculateNewton(const Eigen::VectorXd& y_prev, const double t_n){
    Eigen::VectorXd u_n = y_prev;
    Eigen::VectorXd ratio;
    //double err;
    Eigen::VectorXd identity = Eigen::VectorXd::Ones(u_n.size());
    Eigen::VectorXd F;
    Eigen::VectorXd dF;

    int i=0;
    while(i<200){
        //Here I have to recompute the value of F and dF
        F = u_n - y_prev - timestep_*GetValueFunction(u_n, CalculateNextTimeStep(t_n));
        dF = identity - timestep_* GetDerivativeFunction(u_n, CalculateNextTimeStep(t_n));
        ratio = F.cwiseQuotient(dF);
        //It would be u_(n+1) = u_n -ratio, it's the computation of the next step
        //err = std::abs(u_n[0] - (u_n[0] - ratio[0]));
        u_n = u_n - ratio;
        i++;
    }
    return u_n;
}

Eigen::VectorXd BackwardEulerSolver::CalculateNextStep(const Eigen::VectorXd& y_prev, const double& t_prev){
    return CalculateNewton(y_prev, t_prev);
}


std::map<double, Eigen::VectorXd> BackwardEulerSolver::SolveOde() {
    Eigen::VectorXd y_k=GetInitialValue();
    Eigen::VectorXd y_k1;
    double t_k=GetInitialTime();
    double t_k1;
    std::map<double, Eigen::VectorXd> map_solution;


    map_solution.insert({t_k, y_k});
    for(int i=0; i<numbersteps_; i++){
        //calculating the next step by starting from (y_k, t_k), the Newton method is computed inside CalculateNextStep
        y_k1 = CalculateNextStep(y_k, t_k);
        t_k1 = CalculateNextTimeStep(t_k);
        map_solution.insert({t_k1, y_k1});
        y_k = y_k1;
        t_k = t_k1;
    }

    return map_solution;
}
