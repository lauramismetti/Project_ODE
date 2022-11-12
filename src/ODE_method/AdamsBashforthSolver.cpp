/** \file
 * @brief Implementation of the methods of the class AdamsBashforthSolver
 */

#include <Eigen/Dense>
#include "AdamsBashforthSolver.hpp"
using namespace std;


std::map<double, Eigen::VectorXd> AdamsBashforthSolver::SolveOde() {
    Eigen::VectorXd y_k=GetInitialValue();
    Eigen::VectorXd y_k1, y_k2, y_k3, y_k4;
    double t_k=GetInitialTime();
    double t_k1, t_k2, t_k3, t_k4;
    std::map<double, Eigen::VectorXd> map_solution;

    map_solution.insert({t_k,y_k});

    for(int i=0; i<numbersteps_; i+=4){
         y_k1 = CalculateNextStep(y_k, t_k); //re-using the Euler formula
         t_k1 = CalculateNextTimeStep(t_k);
         y_k2 = y_k1 + timestep_* ( 3./2. *GetValueFunction(y_k1, t_k1) - 1./2.* GetValueFunction(y_k,t_k) );
         t_k2 = CalculateNextTimeStep(t_k1);
         y_k3 = y_k2 + timestep_* ((23./12.) * GetValueFunction(y_k2, t_k2) -(16./12.) * GetValueFunction(y_k1, t_k1) + (5./12.)* GetValueFunction(y_k, t_k));
         t_k3 = CalculateNextTimeStep(t_k2);
         y_k4 = y_k3 + timestep_* (55./24. * GetValueFunction(y_k3, t_k3) -59./24. * GetValueFunction(y_k2, t_k2) +37./24.*GetValueFunction(y_k1, t_k1) -9./24.*GetValueFunction(y_k, t_k));
         t_k4 = CalculateNextTimeStep(t_k3);

         map_solution.insert({t_k1,y_k1});
         map_solution.insert({t_k2,y_k2});
         map_solution.insert({t_k3,y_k3});
         map_solution.insert({t_k4,y_k4});
         y_k = y_k4;
         t_k = t_k4;
    }

    return map_solution ;
}