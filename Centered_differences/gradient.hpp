#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include<cmath>
#include <functional>
#include <vector>
#include <iostream>

//structure called Data, defining the data and parameters needed
struct Data
{
    
    std::function<double(std::vector<double>)> f;                   //function
    //std::function<std::vector<double>(std::vector<double>)> grad;   //gradient
    std::vector<double> start_point{0.0,0.0};                       //starting point
    
    double epsilon_step{0.01};  //tolerance on the step length
    double epsilon_res{0.01};   //tolerance on the residual
    double initial_step{1};     //initial step size
    double maxit{1000};         //maximum number of iterations
    double sigma{0.3};          //parameter for Armijo rule
    double h = 1e-6;            //step for Centered differences
};

// declaratio of the used methods
std::vector<double> gradient_method(const Data& );
double Armijo(const Data& , std::vector<double> & );
double norm(const std::vector<double> &  );
std::vector<double> centered_differences(const Data&, const std::vector<double>&);

std::vector<double> operator-(std::vector<double>, std::vector<double>);
std::vector<double> operator*(double, std::vector<double>);




#endif // GRADIENT_HPP