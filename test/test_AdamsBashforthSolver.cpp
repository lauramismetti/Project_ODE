/*
 * Test of the class AdamsBashforthSolver
 */
#include <iostream>
#include <Eigen/Dense>
#include <map>

#include "gtest/gtest.h"
#include "../src/ODE_method/AdamsBashforthSolver.hpp"
#include "../src/Functions/Square.h"

//Here we check the methods of the AdamsBashforthSolver

TEST (AdamsBashforthSolver, SolveOde) {

    Eigen::Vector2d y0;
    y0 << 1., 2. ;
    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    AbstractOdeSolver *ptr_solver=nullptr;
    ptr_solver = new AdamsBashforthSolver("bashforth", 0.1, 4, 0, y0, ptr_f);

    std::map<double, Eigen::VectorXd> computed_map;
    computed_map = ptr_solver -> SolveOde() ;
    auto it = computed_map.begin();

        EXPECT_NEAR(0.0, it->first, 1e-4);
        EXPECT_NEAR(1.0, it->second[0], 1e-4);
        EXPECT_NEAR(2.0, it->second[1], 1e-4);
        it++;
        EXPECT_NEAR(0.1, it->first, 1e-4);
        EXPECT_NEAR(1.1, it->second[0], 1e-4);
        EXPECT_NEAR(2.4, it->second[1], 1e-4);
        it++;
        EXPECT_NEAR(0.2, it->first, 1e-4);
        EXPECT_NEAR(1.2315, it->second[0], 1e-4);
        EXPECT_NEAR(3.064, it->second[1], 1e-4);
        it++;
        EXPECT_NEAR(0.3, it->first, 1e-4);
        EXPECT_NEAR(1.4025, it->second[0], 1e-4);
        EXPECT_NEAR(4.2620, it->second[1], 1e-4);
        it++;
        EXPECT_NEAR(0.4, it->first, 1e-4);
        EXPECT_NEAR(1.6295, it->second[0], 1e-4);
        EXPECT_NEAR(6.8549, it->second[1], 1e-4);

    delete ptr_solver;
}
