/** \file
 * @brief Definition of the class WriteFile
 * It allows to output the results of the ODE by writing them in a file.
 */

#ifndef ODE_PROJECT_WRITEFILE_H
#define ODE_PROJECT_WRITEFILE_H

#include <string>
#include <fstream>

#include "Output.h"

///@brief Class to write the output in a file
class WriteFile : public Output  {
public :
    //Constructor
    WriteFile(const map<double, Eigen::VectorXd>& solutions, const string& name_method_, const string& name_f_, const string& filename) :
        Output(solutions, name_method_, name_f_), filename_(filename) {}

    ///Write the solution at each time step in the file defined in the command line
    void out() const override;

private :
    ///Name of the output file
    string filename_;
};


#endif //ODE_PROJECT_WRITEFILE_H
