/*
 * Test of the main
 */
#include <gtest/gtest.h>

// The tes_main will call all the tests in the different files

int main(int argc, char **argv){

    testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();
    return result;
}
