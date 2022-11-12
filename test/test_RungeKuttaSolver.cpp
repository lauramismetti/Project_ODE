/*
 * Test class RungeKuttaSolver
 */
#include <iostream>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/ODE_method/RungeKuttaSolver.hpp"
#include "../src/Functions/Square.h"

//Here we check the methods of the Runge Kutta

TEST (RungeKuttaSolver, next_time_step) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new RungeKuttaSolver;

    ptr_solver -> SetTimeStep(0.01);
    EXPECT_EQ (1.01, ptr_solver -> CalculateNextTimeStep(1.0));
    ptr_solver -> SetTimeStep(0.3);
    EXPECT_EQ (0.3, ptr_solver -> CalculateNextTimeStep(0.0));
    ptr_solver -> SetTimeStep(0.12);
    EXPECT_EQ (2.27, ptr_solver -> CalculateNextTimeStep(2.15));

    delete ptr_solver;
}


TEST (RungeKuttaSolver, next_y) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new RungeKuttaSolver();
    ptr_solver -> SetTimeStep(0.01);

    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    ptr_solver -> SetFunction(ptr_f) ;

    Eigen::Vector2d y ;
    y << 1., 2. ;
    Eigen::Vector2d computed_y = ptr_solver->CalculateNextStep(y,1.2) ;

    Eigen::Vector2d expected_y ;
    expected_y << 1.0101, 2.04081;

    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);

    computed_y = ptr_solver->CalculateNextStep(computed_y, 1.21);
    expected_y << 1.0204, 2.0833;

    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);

    delete ptr_solver;
}

