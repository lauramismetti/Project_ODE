/*
 * Tests of the class Output (and all the daughter classes)
 */

#include <iostream>
#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../src/Output/Output.h"
#include "../src/Output/WriteTerminal.h"

//This test trivially test if the constructor of the output is correctly implemented by being to correctly take the solutions

TEST (Output, store_solution) {

    string filename = "../files/output_test.txt";
    //I have to create a map which stores a possible solution
    map<double, Eigen::VectorXd> solutions;
    Eigen::Vector3d y_0;
    y_0 << 1.0, 2.0, 3.0;
    Eigen::Vector3d y_1;
    y_1 << 1.1, -2.15, 2.3;
    Eigen::Vector3d y_2;
    y_2 << 1.73, -1.34, 3.1;
    solutions.insert({0.1, y_0});
    solutions.insert({0.2, y_1});
    solutions.insert({0.3, y_2});

    Output * ptr_out= nullptr;
    ptr_out = new WriteTerminal(solutions, "forward_euler", "y_square");

    EXPECT_EQ(0.1, ptr_out->GetTimes()[0]);
    EXPECT_EQ(1.0, ptr_out->GetSolutions()[0][0]);
    EXPECT_EQ(2.0, ptr_out->GetSolutions()[0][1]);
    EXPECT_EQ(3.0, ptr_out->GetSolutions()[0][2]);

    EXPECT_EQ(0.2, ptr_out->GetTimes()[1]);
    EXPECT_EQ(1.1, ptr_out->GetSolutions()[1][0]);
    EXPECT_EQ(-2.15, ptr_out->GetSolutions()[1][1]);
    EXPECT_EQ(2.3, ptr_out->GetSolutions()[1][2]);

    EXPECT_EQ(0.3, ptr_out->GetTimes()[2]);
    EXPECT_EQ(1.73, ptr_out->GetSolutions()[2][0]);
    EXPECT_EQ(-1.34, ptr_out->GetSolutions()[2][1]);
    EXPECT_EQ(3.1, ptr_out->GetSolutions()[2][2]);

    delete ptr_out;
}