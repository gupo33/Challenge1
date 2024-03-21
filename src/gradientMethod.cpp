#include "gradientMethod.hpp"
#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>

double gradientMethod::minimize() const{

    int k = 1;

    std::vector<double> x = params.init_guess;
    std::vector<double> x_next = x;

    auto norm = [](std::vector<double> v){ //define norm function
        return std::sqrt(std::inner_product(v.begin(),v.end(),v.begin(),0.));
    };

    bool method_conv = false;

    while(k <= params.max_it){

        double fx = params.fun(x);
        std::vector<double> dfx = params.dfun(x);

        double alpha = params.alpha_init;

        std::cout << "alpha: " << alpha << std::endl;

        bool alpha_reach = false;

        while(!alpha_reach){ //Armijo rule
            std::vector <double> sum;

            for(int i = 0; i<x.size(); ++i){
                sum.push_back(x[i] - alpha*dfx[i]);
            }

            double norm_dfx = norm(dfx);

            //evaluate condition and update alpha

            if(fx - params.fun(sum) >= params.sigma * alpha * norm_dfx * norm_dfx){
                alpha_reach = true;
                std::cout << "left: " << fx - params.fun(sum) << std::endl;
                std::cout << "right: " << params.sigma * alpha * norm_dfx * norm_dfx;
                std::cout << "reach, k : " << alpha_reach << "," << k << std::endl;
            }
            else{
                alpha = alpha / 2; 
            }
        }

        //with the current alpha, compute the next iteration

        for(size_t i = 0; i<x.size();++i){
            x_next[i] = x[i] - alpha * dfx[i];
        }

        //evaluate convergence conditions

        std::vector<double> diff = {};

        for(auto i = 0; i<x.size();++i){
            diff.push_back((x_next[i]-x[i])*(x_next[i]-x[i]));
        }

        if(k >= params.max_it || 
           norm(params.dfun(x_next)) < params.tol_res ||
           norm(diff) < params.tol_step){
            method_conv = true;

            //prints information about the result

            double minimum = params.fun(x_next);

            std::cout << "minimum: " << minimum << "\n\n"; 

            std::cout << "minimum point:\n\n";

            for(const auto & i : x_next){
                std::cout << i << "\n";
            }
            std::cout << " \n";
            std::cout << "number of iterations: " << k << std::endl;


            return minimum;
        }

        //advance to the next step

        x.swap(x_next);
        ++k;
    }
}