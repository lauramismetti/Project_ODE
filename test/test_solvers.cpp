//
// Created by tvannier@INTRANET.EPFL.CH on 16.12.21.
//

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "gtest/gtest.h"
#include "../src/ODE_method/ForwardEulerSolver.hpp"
#include "../src/ODE_method/BackwardEulerSolver.hpp"
#include "../src/ODE_method/RungeKuttaSolver.hpp"
#include "../src/ODE_method/AdamsBashforthSolver.hpp"

/*
 * We can easily proof by hand that the solution of the equation dy(t)/dt = y with y0 = (1, 2) at time t0 = 0 is :
 * y = (exp(t), 2*exp(t))
 * So we can use this simple equation to check if our methods are accurate
 */

//The following tests assess the accuracy of the methods by showing an error = |y_true - y_computed| < 1e-2 with a step size h = 0.001

Eigen::Vector2d y (double t){
    Eigen::Vector2d y_ ;
    y_ << exp(t), 2*exp(t) ;
    return y_ ;
}


TEST (AdamsBashforthSolver, is_correct) {

    Eigen::Vector2d y0;
    y0 << 1., 2.;
    shared_ptr<RH_function> ptr_f = make_shared<RH_function>("identity");
    AbstractOdeSolver *ptr_solver = nullptr;
    ptr_solver = new AdamsBashforthSolver("bashforth", 0.001, 100, 0, y0, ptr_f);

    std::map<double, Eigen::VectorXd> map;
    map = ptr_solver->SolveOde();

    for(auto &m : map){
        double t = m.first ;
        Eigen::Vector2d y_exp = y(t) ;
        Eigen::Vector2d y = m.second ;

        EXPECT_NEAR(y[0], y_exp[0], 1e-2) ;
        EXPECT_NEAR(y[1], y_exp[1], 1e-2) ;
    }

    delete ptr_solver;
}

TEST (ForwardEulerSolver, is_correct) {

    Eigen::Vector2d y0;
    y0 << 1., 2.;
    shared_ptr<RH_function> ptr_f = make_shared<RH_function>("identity");
    AbstractOdeSolver *ptr_solver = nullptr;
    ptr_solver = new ForwardEulerSolver("forward_euler", 0.001, 100, 0, y0, ptr_f);

    std::map<double, Eigen::VectorXd> map;
    map = ptr_solver->SolveOde();

    for(auto &m : map){
        double t = m.first ;
        Eigen::Vector2d y_exp = y(t) ;
        Eigen::Vector2d y = m.second ;

        EXPECT_NEAR(y[0], y_exp[0], 1e-2) ;
        EXPECT_NEAR(y[1], y_exp[1], 1e-2) ;
    }
    delete ptr_solver;
}

TEST (BackwardEulerSolver, is_correct) {

    Eigen::Vector2d y0;
    y0 << 1., 2.;
    shared_ptr<RH_function> ptr_f = make_shared<RH_function>("identity");
    AbstractOdeSolver *ptr_solver = nullptr;
    ptr_solver = new BackwardEulerSolver("backward_euler", 0.001, 100, 0, y0, ptr_f);

    std::map<double, Eigen::VectorXd> map;
    map = ptr_solver->SolveOde();

    for(auto &m : map){
        double t = m.first ;
        Eigen::Vector2d y_exp = y(t) ;
        Eigen::Vector2d y = m.second ;

        EXPECT_NEAR(y[0], y_exp[0], 1e-2) ;
        EXPECT_NEAR(y[1], y_exp[1], 1e-2) ;
    }
    delete ptr_solver;
}

TEST (RungeKuttaSolver, is_correct) {

    Eigen::Vector2d y0;
    y0 << 1., 2.;
    shared_ptr<RH_function> ptr_f = make_shared<RH_function>("identity");
    AbstractOdeSolver *ptr_solver = nullptr;
    ptr_solver = new RungeKuttaSolver("runge_kutta", 0.001, 100, 0, y0, ptr_f);

    std::map<double, Eigen::VectorXd> map;
    map = ptr_solver->SolveOde();

    for(auto &m : map){
        double t = m.first ;
        Eigen::Vector2d y_exp = y(t) ;
        Eigen::Vector2d y = m.second ;

        EXPECT_NEAR(y[0], y_exp[0], 1e-2) ;
        EXPECT_NEAR(y[1], y_exp[1], 1e-2) ;
    }
    delete ptr_solver;
}