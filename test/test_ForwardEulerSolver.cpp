/*
 * Test class ForwardEulerSolver
 */
#include <iostream>
#include <memory>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/ODE_method/ForwardEulerSolver.hpp"
#include "../src/Functions/Square.h"

//Here we check the methods of the ForwardEulerSolver

TEST (ForwardEulerSolver, next_time_step) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new ForwardEulerSolver;

    ptr_solver -> SetTimeStep(0.01);
    EXPECT_EQ (1.01, ptr_solver -> CalculateNextTimeStep(1.0));
    ptr_solver -> SetTimeStep(0.3);
    EXPECT_EQ (0.3, ptr_solver -> CalculateNextTimeStep(0.0));
    ptr_solver -> SetTimeStep(0.12);
    EXPECT_EQ (2.27, ptr_solver -> CalculateNextTimeStep(2.15));

    delete ptr_solver;
}


TEST (ForwardEulerSolver, next_y) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new ForwardEulerSolver();
    ptr_solver -> SetTimeStep(0.01);

    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    ptr_solver -> SetFunction(ptr_f) ;

    Eigen::Vector2d y ;
    y << 3., 7. ;
    Eigen::Vector2d computed_y = ptr_solver -> CalculateNextStep(y,1.2) ;
    Eigen::Vector2d expected_y ;
    expected_y << 3.0900, 7.4900;
    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);

    computed_y = ptr_solver->CalculateNextStep(computed_y,1.21);
    expected_y << 3.1855, 8.051001;
    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);

    computed_y = ptr_solver->CalculateNextStep(computed_y,1.22);
    expected_y << 3.2870, 8.699187171;
    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-4);
    EXPECT_NEAR(expected_y[1], computed_y[1], 1e-4);

    delete ptr_solver;
}

