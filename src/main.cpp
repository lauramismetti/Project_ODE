/*! \mainpage # ProjectODE by Laura Mismetti and Théau Vannier
MATH-458, Programming Concepts in Scientific Computing, project on ODE in C++

# A/ Presentation of the project

## 1/ Theory

The goal of the project is to solve an Ordinary Differential Equation (ODE) with general form

    d(y(t))/dt = f(y(t),t)     with y(t) a vector

by using different numerical methods to approximate the solution y(t), where initial conditions (time and initial values of the vector y),
time interval and right hand side (function f) of the equation are specified.

## 2/ The program in brief

The program offers the possibility to choose between 4 different numerical methods to solve an ODE:
- Forward Euler method
- Adams Bashforth method
- Backward Euler method
- Runge-Kutta method (order 4)

The required inputs are :

- the time interval [t0, tf],
- the dimension of the vector y,
- the name of the chosen method,
- the initial values of the y vector and the name of a function f

They should all be stored in a precise way (see below section C) in the input file.

Once the program has been launched, an instance of a class to read the input file is generated.
It will read the input, create a pointer to an abstract class for the solver and give to it the input parameters.

Then the method which solves the ODE is called and the solution is stored in a map.

The last step consists in the creation of an instance of the class which manages the output. If the name of a file is provided in the command line,
the output will be written in this file, else the solution is written inside the terminal.
In both cases a column with the values of the sequential time steps and as many columns as many are the components of the y vector
(which store the values of the vector y) are printed.
 */

/** \file
 * @brief Acquisition of the input and declaration of the classes used to solve the ODE, especially to read the
 * input and write the output.
 */

#include <iostream>
#include <algorithm>

#include "ODE_method/AbstractOdeSolver.hpp"
#include "Input/Reader.h"
#include "Output/WriteFile.h"
#include "Output/WriteTerminal.h"


using namespace std;

int main(int argc, char *argv[]){

    //Default input file name and declaration of an output file name
    string ifilename = "../files/input.txt";
    string ofilename ;

    //If an input file is given, then the input is taken from this file
    if (argc > 1) {
        ifilename = argv[1] ;
    }

    //Create a reader object with the input file name
    Reader input(ifilename) ;

    //Create a pointer on an abstract solver and point to the right solver according to the input given
    AbstractOdeSolver *ptr_solver ;
    ptr_solver = input.create_solver() ;

    //Create a pointer on an output object
    Output *ptr_output ;

    // If an output file is given, then we will write the solution in this output file, otherwise it will be written on the terminal
    if(argc > 2){
        ofilename = argv[2] ;
        ptr_output = new WriteFile(ptr_solver -> SolveOde(), ptr_solver -> GetNameMethod(), ptr_solver -> GetNameFunction(), ofilename) ;
    }
    else{
        ptr_output = new WriteTerminal(ptr_solver -> SolveOde(), ptr_solver -> GetNameMethod(), ptr_solver -> GetNameFunction()) ;
    }

    //Write the output
    ptr_output -> out();

    delete ptr_solver ;
    delete ptr_output ;

    return 0 ;
}