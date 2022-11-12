/** \file
 * @brief Definition of the methods of the class WriteTerminal
 */

#include "WriteTerminal.h"

void WriteTerminal::out() const {

    cout.setf(ios::scientific);
    cout.setf(ios::showpos);
    cout.precision(3);

    cout << ">>>>>SOLUTION OF THE ODE<<<<< " << endl ;
    cout << endl ;
    cout << "ODE equation : y'(t) = f(y(t), t) " << endl ;
    cout << endl ;
    cout << "With : " << endl ;
    cout << " y is of dimension : " << solutions_[0].size() << endl ;
    cout << " f is the function : " << name_f << endl ;
    cout << endl ;
    cout << " The method used to resolved this equation is : " << name_method << endl ;
    cout << endl ;
    cout << "Time          Values y" << endl ;
    for (int i = 0 ; i < times_.size() ; ++i) {
        cout << times_[i] << "   " << solutions_[i].transpose() << endl ;
    }

}