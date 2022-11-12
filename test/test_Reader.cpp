/*
 * Test of the class Reader
 */

#include <iostream>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/Input/Reader.h"

//Here we check if the input file is yell read and if Reader class passes well the arguments to the Solver class
// Be careful : It requires the input_test.txt to be UNCHANGED, else the tests won't pass

TEST (Reader, read_well_the_input) {

    string filename = "../files/input_test.txt";
    Reader input(filename);
    input.read();

    double t0, tf ;
    int N ;
    int dim ;
    Eigen::VectorXd y0;
    string method;
    string f_name ;

    tie(t0, tf, N, dim, method, y0, f_name) = input.read() ;
    EXPECT_TRUE (t0 == 0.1);
    EXPECT_TRUE (tf == 5.2);
    EXPECT_TRUE (N == 100);
    EXPECT_TRUE (dim == 3);
    EXPECT_TRUE (method == "forward_euler");
    EXPECT_TRUE (f_name == "t_square");


    Eigen::Vector3d y ;
    y << 1.1, 2.0, -2.1 ;

    EXPECT_TRUE (y0 == y);
}

TEST (Reader, input_well_given_to_Solver) {

    string filename = "../files/input_test.txt";
    Reader input(filename);
    input.read();

    AbstractOdeSolver *ptr_solver ;
    ptr_solver = input.create_solver() ;

    double time_step = (5.2-0.1)/100 ;

    Eigen::Vector3d y_input ;
    y_input << 1.1, 2.0, -2.1 ;

    Eigen::Vector3d y_ODE ;
    y_ODE = ptr_solver -> GetInitialValue() ;

    EXPECT_EQ (ptr_solver -> GetTimeStep(), time_step);
    EXPECT_EQ (ptr_solver -> GetNumberSteps(), 100);
    EXPECT_EQ (ptr_solver -> GetInitialTime(), 0.1);
    EXPECT_EQ (y_ODE[0], y_input[0]);
    EXPECT_EQ (y_ODE[1], y_input[1]);
    EXPECT_EQ (y_ODE[2], y_input[2]);
    EXPECT_EQ (ptr_solver -> GetNameMethod(), "forward_euler");
    EXPECT_EQ (ptr_solver -> GetNameFunction(),"t_square");
}
