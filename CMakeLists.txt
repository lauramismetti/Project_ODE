cmake_minimum_required (VERSION 3.10.2)
project (ODE_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(eigen)

add_library(ode_library
        src/ODE_method/AbstractOdeSolver.cpp src/ODE_method/ForwardEulerSolver.cpp src/ODE_method/AdamsBashforthSolver.cpp src/ODE_method/BackwardEulerSolver.cpp src/ODE_method/RungeKuttaSolver.cpp src/Output/Output.cpp src/Output/WriteFile.cpp src/Output/WriteTerminal.cpp src/Functions/RH_function.cpp src/Functions/Square.cpp src/Functions/Polynomial.cpp src/Functions/Exponential.cpp src/Functions/T_square.cpp src/Input/Reader.cpp
        )

add_subdirectory(googletest)

add_executable(main src/main.cpp)
target_link_libraries(main ode_library)

add_executable(test_main test/test_main.cpp test/test_Reader.cpp test/test_AbstractOdeSolver.cpp test/test_ForwardEulerSolver.cpp test/test_BackwardEulerSolver.cpp test/test_AdamsBashforthSolver.cpp test/test_RungeKuttaSolver.cpp test/test_Functions.cpp test/test_Output.cpp test/test_solvers.cpp)
target_link_libraries(test_main gtest_main gtest pthread ode_library)

add_custom_target(testmain ./test_main DEPENDS test_main)
