/*
 * Test class AbstractOdeSolver
 */
#include <iostream>
#include <memory>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/ODE_method/AbstractOdeSolver.hpp"
#include "../src/ODE_method/ForwardEulerSolver.hpp"
#include "../src/Functions/Polynomial.h"


TEST (AbstractOdeSolver, set_methods) {

    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new ForwardEulerSolver;
    Eigen::Vector2d y;
    y << 1.1, 2.1;
    shared_ptr<RH_function> ptr_f= nullptr;
    ptr_f = make_shared<Polynomial>("poly");
    ptr_solver->SetTimeStep(0.01);
    ptr_solver->SetInitialTime(1.3);
    ptr_solver->SetNumberSteps(100);
    ptr_solver->SetInitialValue(y);
    ptr_solver->SetFunction(ptr_f);
    ptr_solver->SetName("runge_kutta");


    EXPECT_DOUBLE_EQ(0.01, ptr_solver->GetTimeStep());
    EXPECT_DOUBLE_EQ(1.3, ptr_solver->GetInitialTime());
    EXPECT_EQ(100, ptr_solver->GetNumberSteps());
    EXPECT_DOUBLE_EQ(y[0], ptr_solver->GetInitialValue()[0]);
    EXPECT_DOUBLE_EQ(y[1], ptr_solver->GetInitialValue()[1]);
    EXPECT_EQ("runge_kutta", ptr_solver->GetNameMethod());
    EXPECT_EQ("poly", ptr_solver->GetNameFunction());

    delete ptr_solver;
}

