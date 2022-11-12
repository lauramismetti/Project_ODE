/*
 * Test class Functions
 */
#include <iostream>
#include <memory>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/Functions/RH_function.h"
#include "../src/Functions/Square.h"
#include "../src/Functions/T_square.h"
#include "../src/Functions/Polynomial.h"
#include "../src/Functions/Exponential.h"

//Here we check that each functions trivially gives the right output

TEST (RH_function, identity) {

    // f(y, t) = y and df(y,t)/dy = 1

    shared_ptr<RH_function> ptr_f = make_shared<RH_function>("identity") ;
    Eigen::Vector2d y;
    y << 1., 2.;
    Eigen::Vector2d computed_y;
    computed_y = ptr_f->f(y,0.1);
    Eigen::Vector2d expected_y;
    expected_y << 1., 2.;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);

    //compute also the derivative
    computed_y = ptr_f->df(y,0.1);
    expected_y << 1., 1.;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);
}

TEST (RH_function, y_square) {

    //f(y, t) = y^2 and df(y,t)/dy = 2*y

    shared_ptr<RH_function> ptr_f = make_shared<Square>("y_square") ;
    Eigen::Vector2d y;
    y << 1., 2.;
    Eigen::Vector2d computed_y;
    computed_y = ptr_f->f(y,0.1);
    Eigen::Vector2d expected_y;
    expected_y << 1., 4.;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);

    //compute also the derivative
    computed_y = ptr_f->df(y,0.1);
    expected_y << 2., 4.;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);
}

TEST (RH_function, polynomial) {

    //f(y, t) = 2*t*y + 3*y^2 + 4*Id and df(y,t)/dy = 2*t + 6*y

    shared_ptr<RH_function> ptr_f = make_shared<Polynomial>("poly") ;
    Eigen::Vector2d y;
    y << 1., 2.;
    Eigen::Vector2d computed_y;
    computed_y = ptr_f->f(y,0.1);
    Eigen::Vector2d expected_y;
    expected_y << 7.2, 16.4;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);

    //compute also the derivative
    computed_y = ptr_f->df(y,0.1);
    expected_y << 6.2, 12.2;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);
}

TEST (RH_function, t_square) {

    // f(y, t)= t^2 - y and df(y,t)/dy = -1

    shared_ptr<RH_function> ptr_f = make_shared<T_square>("t_square") ;
    Eigen::Vector2d y;
    y << 1., 2.;
    Eigen::Vector2d computed_y;
    computed_y = ptr_f->f(y,0.1);
    Eigen::Vector2d expected_y;
    expected_y << -0.99, -1.99;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);

    //compute also the derivative
    computed_y = ptr_f->df(y,0.1);
    expected_y << -1, -1;

    EXPECT_DOUBLE_EQ (expected_y[0], computed_y[0]);
    EXPECT_DOUBLE_EQ (expected_y[1], computed_y[1]);
}

TEST (RH_function, exponential) {

    // f(y, t)=exp(y) and df(y,t)/dy = exp(y)

    shared_ptr<RH_function> ptr_f = make_shared<Exponential>("exp") ;
    Eigen::Vector2d y;
    y << 1., 2.;
    Eigen::Vector2d computed_y;
    computed_y = ptr_f->f(y,0.1);
    Eigen::Vector2d expected_y;
    expected_y << 2.718, 7.389;

    EXPECT_NEAR(expected_y[0], computed_y[0], 1e-3);
    EXPECT_NEAR (expected_y[1], computed_y[1], 1e-3);

    //compute also the derivative
    computed_y = ptr_f->df(y,0.1);
    expected_y << 2.718, 7.389;

    EXPECT_NEAR (expected_y[0], computed_y[0], 1e-3);
    EXPECT_NEAR (expected_y[1], computed_y[1], 1e-3);
}
