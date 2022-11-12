/** \file
 * @brief Declaration of the class Reader to read the input file
 */

#ifndef ODE_PROJECT_READER_H
#define ODE_PROJECT_READER_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <exception>
#include <map>
#include <tuple>
#include <memory>
#include <Eigen/Dense>

#include "../ODE_method/AbstractOdeSolver.hpp"
#include "../ODE_method/ForwardEulerSolver.hpp"
#include "../ODE_method/AdamsBashforthSolver.hpp"
#include "../ODE_method/BackwardEulerSolver.hpp"
#include "../ODE_method/RungeKuttaSolver.hpp"
#include "../Functions/RH_function.h"
#include "../Functions/Square.h"
#include "../Functions/Polynomial.h"
#include "../Functions/Exponential.h"
#include "../Functions/T_square.h"

using namespace std;
///@brief Class that reads the input file
class Reader {

public:
//Constructor :
    ///@brief Constructor which sets the members 'method_dict' and 'f_dict'
    Reader(const string &name) : name_file(name){
        method_dict = {
                {"forward_euler",1},
                {"bashforth",2},
                {"backward_euler", 3},
                {"runge_kutta", 4}
        };

        f_dict ={
                {"identity", 0},
                {"y_square",1},
                {"poly",2},
                {"exp",3},
                {"t_square",4},
        };
    }

//Destructor :
    ~Reader() = default ;

//Methods of the class :
    /**Reads the input file given in argument in the constructor of the class and return a tuple with :
     * \brief This function is able to handle some exceptions, but still the input file should be written exactly as explained in the readme, our code is a bit capricious...
     * \brief To be more user-friendly the error message are meant to help you in case you did not write a "correct" input file
     * \return initial time (double)
     * \return final time (double)
     * \return number of steps (integer)
     * \return dimension of the vector y (integer)
     * \return name of the method to use to solve the ode (string)
     * \return vector with the initial values of y (Eigen::VectorXd)
     */
    tuple<double, double, int, int, string, Eigen::VectorXd, string> read() const ;

    /**Call the read() and from the returned tuple, it will create a pointer to the abstract solver
     * \return pointer to AbstractOdeSolver object (AbstractOdeSolver*)
     */
    AbstractOdeSolver* create_solver() const ;

    /**Calculate the number of parameters to be able to throw an error in read() if the number of parameters is not good
     * \return the number of "words" (parameters) on the first line
     */
    int count_number_of_params() const ;

private:
//Members:
    ///Name of the file from which the input is read
    string name_file ;

    ///Dictionary with the different ODE classes which can be used to solve the ODE
    map<string, int> method_dict ;

    ///Dictionary with the different right hand side functions in the equation y'(t) = f(y(t), t)
    map<string, int> f_dict ;
};

#endif //ODE_PROJECT_READER_H
