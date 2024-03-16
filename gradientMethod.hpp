#include <functional>

using fun_type = std::function<double(std::vector<double>)>;
using dfun_type = std::function<std::vector<double>(std::vector<double>)>;


class gradientMethod{
private:
    struct {
        //function and derivative for which to find the minimum

        const fun_type fun;
        const dfun_type dfun;

        const std::vector<double> & init_guess;

        const unsigned int max_it; //maximum number of iterations
        const double tol_step; //tolerance for the difference between iterations
        const double tol_res; //tolerance for the residual of iterations

        const double sigma = 0.25; //sigma value for the armijo rule
        const double alpha_init = 1; //initial alpha value for the armijo rule

    } params;
public:
    //class constructor
    gradientMethod(const fun_type fun, 
                   const dfun_type dfun,
                   const std::vector<double> & init_guess, 
                   const unsigned int max_it, 
                   const double tol_step, 
                   const double tol_res): params({fun,dfun,init_guess,max_it,tol_step,tol_res}){};


    //class constructor, with sigma and alpha_init selection
    gradientMethod(const fun_type fun, 
                   const dfun_type dfun,
                   const std::vector<double> & init_guess, 
                   const unsigned int max_it, 
                   const double tol_step, 
                   const double tol_res,
                   const double sigma,
                   const double alpha_init):params({fun,dfun,init_guess,max_it,tol_step,tol_res,sigma,alpha_init}){};

    //minimizes the function defined in the object
    double minimize() const;
};