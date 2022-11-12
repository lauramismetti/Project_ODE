/** \file
 * @brief Definition of the methods of the class WriteFile
 */

#include "WriteFile.h"


void WriteFile::out() const {

    std::ofstream write_file(filename_);
    if (!write_file.is_open())
    {
        throw runtime_error("ERROR : Unable to open the output file " + filename_);
    }

    write_file.setf(ios::scientific);
    write_file.setf(ios::showpos);
    write_file.precision(3);

    write_file << ">>>>>SOLUTION OF THE ODE<<<<< " << endl ;
    write_file << endl ;
    write_file << "ODE equation : y'(t) = f(y(t), t) " << endl ;
    write_file << endl ;
    write_file << "With : " << endl ;
    write_file << " y is of dimension : " << solutions_[0].size() << endl ;
    write_file << " f is the function : " << name_f << endl ;
    write_file << endl ;
    write_file << " The method used to resolved this equation is : " << name_method << endl ;
    write_file << endl ;
    write_file << "Time          Values y" << endl ;
    for (int i = 0 ; i < times_.size() ; ++i) {
        write_file << times_[i] << "   " << solutions_[i].transpose() << endl ;
    }
    write_file.close();

}