/*
 * Test class BackwardEulerSolver
 */
#include <iostream>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/ODE_method/BackwardEulerSolver.hpp"
#include "../src/Functions/Square.h"

//Here we check the methods of the BackwardEulerSolver


TEST (BackwardEulerSolver, calculateNewton){

    BackwardEulerSolver *ptr_solver=nullptr;
    ptr_solver = new BackwardEulerSolver();
    ptr_solver -> SetTimeStep(0.01);

    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    ptr_solver -> SetFunction(ptr_f) ;

    Eigen::Vector2d y_prev;
    y_prev << 1., 2. ;
    Eigen::Vector2d computed_y = ptr_solver -> CalculateNewton(y_prev,0.);

    EXPECT_NEAR(1.0102, computed_y[0], 1e-4);
    EXPECT_NEAR(2.0417, computed_y[1], 1e-4);

    delete ptr_solver;
};

TEST (BackwardEulerSolver, next_y) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new BackwardEulerSolver();
    ptr_solver -> SetTimeStep(0.1);

    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    ptr_solver -> SetFunction(ptr_f) ;

    Eigen::Vector3d y ;
    y << 1., 2. , 3.;
    Eigen::Vector3d computed_y = ptr_solver -> CalculateNextStep(y,0.) ;

    Eigen::Vector3d expected_y ;
    expected_y << 1.127, 2.7639, 5.4548;

    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);
    EXPECT_NEAR(expected_y[2], computed_y[2], 1e-4);

    computed_y = ptr_solver -> CalculateNextStep(computed_y,0.1) ;
    expected_y << 1.2946, 4.2065, 2.0072;

    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);
    EXPECT_NEAR(expected_y[2], computed_y[2], 1e-4);

    delete ptr_solver;

}

