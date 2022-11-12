/** \file
 * @brief Declaration of the class WriteTerminal for the output
 * It can print the solution of the ODE into the terminal.
 */

#ifndef ODE_PROJECT_WRITETERMINAL_H
#define ODE_PROJECT_WRITETERMINAL_H

#include "Output.h"
///@brief Class to write the solution in the terminal
class WriteTerminal : public Output  {
public :
    //Constructor
    WriteTerminal(const map<double, Eigen::VectorXd>& solutions, const string& name_method_, const string& name_f_) :
        Output(solutions, name_method_, name_f_) {}

    ///Display the solution at each time step in the terminal (default if no name of the output file is given in the command line)
    void out() const override;
};


#endif //ODE_PROJECT_WRITETERMINAL_H
