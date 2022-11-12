/** \file
 * @brief Definition of the class Reader to read the input file
 */

#include "Reader.h"

tuple<double, double, int, int, string, Eigen::VectorXd, string> Reader::read() const{

    //We try to open the input file
    std::ifstream read_file(name_file) ;
    if (!read_file.is_open())
    {
        throw runtime_error("ERROR : Unable to open the input file " + name_file);
    }

    //We declare all the variables useful for the ODE solver
    int i = 0;
    double t0, tf;
    int N, dim ;
    string method;
    //t_square function by default
    string f_name = "identity";
    Eigen::VectorXd y0 ;

    read_file.seekg(0,ios::beg); //bring position of file pointer to beginning of file

    //We will give the values from the input file to the above declared variables
    //First line -> parameter of the ODE equation , 2nd line -> right-hand side function (optional)

    while (!read_file.eof() and i<2) { // i < 2 because we don't care about what is above the second line
        if(i==0) {
			if(count_number_of_params() > 5){
				read_file >> t0 >> tf >> N >> dim >> method;
			}
			else{
				throw invalid_argument("error in the input file at line 0 : the number of arguments is invalid, it should be 5 +dimension(y). Your input file has "+
                                       to_string(count_number_of_params()) + " arguments");
			}
            if(5+dim == count_number_of_params()){
                y0.resize(dim);
                for (int j = 0; j < dim; ++j) {
                    read_file >> y0[j];
                }
            }
            else{
                throw invalid_argument("error in the input file at line 0 : the number of arguments is invalid, it should be 5 +dimension(y). Your input file has "+
                                       to_string(count_number_of_params()) + " arguments");
            }
        }
        if(i==1) {
            read_file >> f_name;
        }
        i++;
    }
    read_file.close();

    // We check if the inputs are correct for our future ODE solver
    if(t0<0 or tf<0 or N<0){
        throw invalid_argument("error in the input file at line 0 : t0, tf and N should be positive");
    }
    if(t0 >= tf){
        throw invalid_argument("error in the input file at line 0 : t0 should be strictly smaller than tf");
    }
    if(N<0 or dim<0){
        throw invalid_argument("error in the input file at line 0 : N (the number of steps) and the dimension of y should be both greater than 0");
    }
    // Check if the given name of the method exists
    if (method_dict.count(method) <= 0){
        string message = "error in the input file at line 0 : the name of the method is invalid, it should be exactly one of the following : " ;
        for(auto const &m : method_dict){
            message += m.first + " " ;
        }
        throw invalid_argument(message) ;
    }
    // Check if the given name of the right-hand side function exists
    if (f_dict.count(f_name) <= 0){
        string message = "error in the input file at line 1 : the name of the right hand sight function is invalid, it should be exactly one of the following : " ;
        for(auto const &f : f_dict){
            message += f.first + " " ;
        }
        message += ". But you gave the name " + f_name ;
        throw invalid_argument(message) ;
    }


    return make_tuple(t0, tf, N, dim, method, y0, f_name);
}


AbstractOdeSolver* Reader::create_solver () const{

    //Declare the future arguments of the solver
    double t0, tf;
    int N, dim;
    Eigen::VectorXd y0;
    string method;
    string f_name;

    //calls the read function to read the parameters from the input file
    try {
        tie(t0, tf, N, dim, method, y0, f_name) = read();
    }catch(const invalid_argument& e){
        cerr << e.what() << endl ;
        cerr << "This error message can also appear in the case you did not enter the input in the correct order or if you did not enter a positive integer for N or dim(y)"<< endl ;
        cerr << endl ;
        cerr << "RECALL : The input should be as follow : " << endl ;
        cerr << "t0 tf N dim(y) ODE_method_name y1 y2 ... yn" << endl ;
        cerr << "name_function(optional)" << endl ;
        cerr << endl ;
        cerr << "Be careful to leave only one white space between each argument" << endl ;
        cerr << endl ;
    }

    //Declare the pointers to an AbstractOdeSOlver class and to an RH_function class
    AbstractOdeSolver *ptr_solver = nullptr ;
    shared_ptr<RH_function> ptr_f = nullptr ;

    //Calculate the step size
    double h;
    h= (tf - t0)/N;

    //switch to select the right-hand side the user want to use according to the input file
    switch (f_dict.at(f_name)) {
        case 0 :
            ptr_f = make_shared<RH_function>(f_name) ;
            break ;
        case 1 :
            ptr_f = make_shared<Square>(f_name) ;
            break ;
        case 2 :
            ptr_f = make_shared<Polynomial>(f_name) ;
            break ;
        case 3 :
            ptr_f = make_shared<Exponential>(f_name) ;
            break ;
        case 4 :
            ptr_f = make_shared<T_square>(f_name) ;
            break ;
        default :
            cerr << "The name of the function you entered is invalid, please try again" << endl ;
            break;
    }

    //switch to select the ODE method the user want to use according to the input file
    switch (method_dict.at(method)) {
        case 1 :
            ptr_solver = new ForwardEulerSolver(method,h,N,t0,y0,ptr_f) ;
            break ;
        case 2 :
            ptr_solver = new AdamsBashforthSolver(method,h,N,t0,y0,ptr_f) ;
            break ;
        case 3 :
            ptr_solver = new BackwardEulerSolver(method,h,N,t0,y0,ptr_f) ;
            break ;
        case 4 :
            ptr_solver = new RungeKuttaSolver(method,h,N,t0,y0,ptr_f) ;
            break ;
        default :
            cerr << "The name of the method you entered is invalid, please try again" << endl ;
            break;
    }


    return ptr_solver ;
}


//Building blocks functions for the count_number_params method of Reader

bool isWhiteSpace(char c){
    return c == ' ' || c == '\n' || c == '\t';
}

bool isWord(char previous){
    return isWhiteSpace(previous);
}

int countWords(const string& str)
{
    int count=0;
    char cur;
    char previous = ' ';

    for(auto char_ : str){
        cur=char_;
        if (isWord(previous)) count++;
        previous = cur;
    }
    return count;
}

int Reader::count_number_of_params() const {

    //Try to open the file
    std::ifstream infile(name_file);
    if (!infile.is_open()) {
        throw runtime_error("ERROR : Unable to open the input file " + name_file);
    }


    int word ;
    string sLine;

    if (infile.good())
    {
        //We will look at the first line of the file (only one which is interesting in our case) and count the numner of parameters on this line
        getline(infile, sLine) ;
        word = countWords(sLine) ;
    }

    infile.close(); //closing file
    return word ;
}
