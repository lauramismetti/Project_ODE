/** \file
 * @brief Declaration of the class Output for the output of the solution
 */

#include <iostream>
#include <map>
#include <Eigen/Dense>
#include <vector>

using namespace std ;


#ifndef ODE_PROJECT_OUTPUT_H
#define ODE_PROJECT_OUTPUT_H

///@brief Class to display the solution
/**
 * This class aims to deal with how to output the result of the ODE solver
 * Member: solution of the ODE solver which is a map<double, vector>. Each entry is a time step t_i and
 * solution $y$ ( $y = (y1, y2, ...., yn)$) at the time $t_i$
 */

class Output {
public :
    //Constructor
    Output(const map<double, Eigen::VectorXd>& solutions_, const string& name_method_, const string& name_f_) ;

    //Destructor
    virtual ~Output() = default ;

    //Get methods
    vector<double> GetTimes() const;
    vector<Eigen::VectorXd> GetSolutions() const;
    string GetMethod() const;
    string GetFunction() const;

    ///@brief Display the results
    virtual void out() const = 0;

protected:
    ///@brief It stores the values of the different time steps
    vector<double> times_;
    /// @brief It stores the computed values of y
    vector<Eigen::VectorXd> solutions_;
    /// @brief Name of the method used to compute the solution
    string name_method ;
    /// @brief Name of the function f used as right hand side
    string name_f ;
};


#endif //ODE_PROJECT_OUTPUT_H
