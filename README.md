# ProjectODE by Laura Mismetti and Théau Vannier
MATH-458, Programming Concepts in Scientific Computing, project on ODE in C++

# A/ Presentation of the project

## 1/ Theory

The goal of the project is to solve an Ordinary Differential Equation (ODE) with general form

    d(y(t))/dt = f(y(t),t)     with y(t) a vector

by using different numerical methods to approximate the solution y(t), where initial conditions (time and initial values of the vector y), time interval and right hand side (function f) of the equation are specified. 

## 2/ The program in brief
      
The program offers the possibility to choose between 4 different numerical methods to solve an ODE: 
- Forward Euler method
- Adams Bashforth method
- Backward Euler method
- Runge-Kutta method (order 4)

The required inputs are :

- the time interval [t0, tf], 
- the dimension of the vector y,
- the name of the chosen method, 
- the initial values of the y vector 
- the name of the right hand side function f (to choose between some specific options, see below section C/ 1/)

They should all be stored in a precise way (see below section C) in the input file.

Once the program has been launched, an instance of a class to read the input file is generated. 
It reads the input and creates a pointer to an abstract class for the solver. It creates also an instance of one of the daughter classes of the mother abstract class (accordingly with the chosen method) by setting all the members to the input parameters.

Then the method (of the instanciated class) which solves the ODE is called. It returns a map which stores the solution, with both time steps and values of the y functions.

The last step consists in the creation of an instance of the class which manages the output. If the name of a file is provided in the command line, the output will be written in this file, else, the solution is written inside the terminal. In both cases a column with the values of the sequential time steps and as many columns as many are the components of the y vector (which stores the values of the function y at each time step) are printed.


# B/ Getting started

Here are provided the information which are necessary to use our project.

## 1/ Clone this repository

You can clone our repository using this command in a terminal at the location of your choice:

With SSH : ```git clone git@gitlab.epfl.ch:tvannier/project_ode.git```

With https : ```git clone https://gitlab.epfl.ch/tvannier/project_ode.git```

## 2/ Clone eigen repository

The code uses the well known eigen library. So, to be able to compile and run properly all the files, the eigen folder must be generated using the following commands from location /project_ode :
```
git clone https://gitlab.com/libeigen/eigen.git
```

## 3/ Clone googletest repository

Some tests have been implemented in order to check the correctness of the program. To reproduce them you have to generate the googletest folder yourself using the following commands from location /project_ode :
```
git clone https://github.com/google/googletest.git -b release-1.11.0
```

## 4/ Structure of the project

To store the file in a clear and intuitive way, different folders have been created.
The project folder also contains a CMakeLists to link all the different files and create 2 executables : main and test_main.

There is also a Doxyfile is stored here to generate the html documention (see section D/ Documentation).

#### a) src folder

This folder contains most of the project as it contains all the code to make the program work.
It contains all the classes required for the project and a main.cpp that "link" everything together to create the executable via the CMakeLists.

Inside src folder 4 subfolders are present:

- Functions: for the classes which define different forms of the function f(y(t), t)
- ODE-method: for the different ODE solver methods (Abstract mother class, Forward Euler method, Backward Euler, Adams-Bashforth and Runge-Kutta) 
- Input: it contains a class able to handle the input (see below the section "The input")
- Output: it contains classes able to handle the output (see below the section "The output")

#### b) test folder

This folder contains all the files used to test the program. Their goal is to test the behavior of most of our classes and functions. It is useful to assess the correctness of what has been done.  (see test section below)

#### c) build folder

This folder is used when the CMake of the program is created manually and then the program compiled and run from the terminal (see section B/ 3/ Compilation and execution). It should be empty until that moment.

#### d) doc folder

This folder is empty on the gitlab repository, it is filled in until the documentation is locally generated (see section D/ Documentation).

#### e) files folder

This folder contains 3 text files which are : 

- a template input.txt file : by default, if no input file is given by the user, our program will read this file
- a template output.txt file : contains an exmple of output
- a test input file test_input.txt : This file should NOT be removed or changed, it is used in the test. Therefore, if you change it, the test for the reader may not pass.

You can add in this folder your own input/output files or directly modify the existent ones.


# C/ Use our program

## 1/ The input

The input consists of an input file that can be specified in the command line when running the executable (if not specified, the program will take the input.txt by default)

**The input file should be written exactly as follow**  :
```
t0 tf N dimension_of_y method_name y01 y02 ... y0n
function_name
```
Where:
- t0 is the initial time (double, t0>=0)
- tf is the final time (double, tf>0, tf>t0)
- N the number of time steps we want to compute in the time interval [t0, tf] (int, N>=1)
- dimension_of_y is the dimension of the vector y (int, >=1)
- method_name is the name of the method used to compute the solution, it must be chosen exactly between **forward_euler**, **backward_euler**, **bashforth** or **runge_kutta**.
- y01, y02, ..., y0n are the initial values of the vector y (double)
- function_name is the name of the right hand side function f that defines the ODE problem. It must be chosen between **identity**, **t_square**, **y_square**, **poly** or **exp**.

In particular, the function names provided correspond to the following right hand sides:
- **identity**: f(y,t) = y
- **t_square**: f(y,t) = t*t - y
- **y_square**: f(y,t) = y*y
- **poly**: f(y,t) = 2ty +3y*y +4
- **exp**: f(y,t) = exp(y)

Every parameter is required, except function_name which is optional (if not provided the identity is chosen by default).

**BE CAREFUL** : The names should be exactly as above to be understood by the program. 

**Examples of input file**:
1)
```
0.1 5.2 100 3 forward_euler 1 2 3
```
2)
```
0.1 1.2 10 3 runge_kutta 1 2 3
t_square
```

## 2/ The output

When executing the code, the name of an output file can be specified from the command line. In that case, the program will write the solution of the ODE in that file. If a name is not provided, the output will be displayed by default on the terminal.

**BE CAREFUL** : If the name corresponds to a file which already exists in the folder, that file will be overwritten.

The output consists in a column with the values of all the computed time steps and a column for each component of the y vector, with all the values computed at each time step t_i (t0 <= ti <= tf).

## 3/ Compilation and execution

#### a) From CLion

After opening CLion, it's possible to select the executable "main" and run it. However, in this way you won't be able to choose an input file and write the output in a file. The input file will always be "input.txt" in the 'files' folder, so if you want to modify the input, you can change it from there. The solution will always be printed on the screen.

If you want to give an input file different from "input.txt" and to write the output on a file, you have to run the code from the terminal (see below).

### b) From terminal

In this way you can choose the input and output files that you prefer, but it's not strictly necessary, if you don't type their names the code will use the "input.txt" file as input and will write the solution in the terminal. 
Here the commands to run the code using cmake are provided (see below examples of execution commands).
In folder ~/project_ode/build type in the terminal:
```
cmake ../
make
./main path/to/input_file_name.txt path/to/output_file_name.txt
```

**Examples of run command** :
```
./main
```
```
./main ../files/input.txt ../files/output.txt
```

# D/Tests

## 1/ Descriptions and test lists

##### a) Class tests :
These tests check the correctness of the methods of each class. They are "trivial sanitary tests".

- AbstractOdeSolver class and daughters : (AbstractOdeSolver, set_methods), (AdamsBashforthSolver, SolveOde), (BackwardEulerSolver, calculateNewton), (BackwardEulerSolver, next_y), (ForwardEulerSolver, next_time_step), (ForwardEulerSolver, next_y), (RungeKuttaSolver, next_time_step), (RungeKuttaSolver, next_y)

- RH_function and daughters : (RH_function, identity), (RH_function, y_square), (RH_function, polynomial), (RH_function, t_square), (RH_function, exponential)

##### b) Workflow tests : 
Reader reads the correct input (Reader, read_well_the_input), passes well the arguments to the Solver (Reader, input_well_given_to_Solver) and finally the Solver gives well the solution to the Output (Output, store_solution).

##### c) Check the accuracy of the solvers

The tests "is_correct" (in the file test_solvers) assess the accuracy of the ODE solvers by comparing the true solution of an easy ODE to the computed solution.

List : (AdamsBashforthSolver, is_correct), (ForwardEulerSolver, is_correct), (BackwardEulerSolver, is_correct), (RungeKuttaSolver, is_correct)

## 2/ Test execution :

#### a) From CLion

You can directly select the executable "test_main" in CLion and run it. However, the display of the tests is different on CLion and on the terminal, if you want to see the details of the tests, run it as in the section below.

#### b) From terminal

Command to run the tests using cmake. In folder ~/project_ode/build type:

**ONLY IF NOT ALREADY DONE BEFORE**
```
    cmake ../
    make
```
Then
``` 
./test_main
```

# E/ Documentation

A more detailed description of the files, classes, methods, members, functions and parameters of the program is provided in the doxygen file of the project. To generate the documentation type the following commands. In folder ~/project_ode/doc :
```
doxygen ../Doxyfile
cd html/
firefox index.html
```

# F/ Issues and perspectives
The biggest issue of the program is about the input file, it is very capricious. It has bee done in this way so that it can deal exceptions and send user-friendly error messages. But still the input should be precisely written.

The provided program is able to compute the numerical solution for easy, already implemented, right hand side functions but also in these easy cases it can't guarantee the convergence of the method used. Indeed, the divergence of the solution can be easily reached by choosing some combinations of input parameters.

The perspectives to improve this project could be to create new solvers as daughter classes of the AbstractOdeSolver, to make the program able to solve an ODE by using more methods. An example could be to create a mother class for all the Runge-Kutta methods with lots of daughter classes which solve the ODE with a specific order. 

For sure new right-hand side functions could be added as daughters of the class RH_Function (mother class for all the right hand side functions). An example could be by using matrices in the definition of the function f.

Finally the reading of the input could be done also from the command line, by adding a new daughter class, and the output could be able to create plots (maybe in python linked to this C++ project), also in this case by adding a daughter class.

