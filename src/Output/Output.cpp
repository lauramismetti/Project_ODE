/** \file
 * @brief Definition of the constructor of the class Output
 */

#include "Output.h"

///Constructor which sets all the members of the class to the input parameters
Output::Output(const map<double, Eigen::VectorXd>& solutions, const string& name_method_, const string& name_f_) :
    name_method(name_method_), name_f(name_f_){

    for(auto &it : solutions){
        times_.push_back(it.first) ;
        solutions_.push_back(it.second) ;
    }
}

vector<double> Output::GetTimes() const{
    return times_;
}
vector<Eigen::VectorXd> Output::GetSolutions() const{
    return solutions_;
}
string Output::GetMethod() const{
    return name_method;
}
string Output::GetFunction() const{
    return name_f;
}

