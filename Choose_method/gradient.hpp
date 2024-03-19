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
    std::function<std::vector<double>(std::vector<double>)> grad;   //gradient
    std::vector<double> start_point{0.0,0.0};                       //starting point

    double epsilon_step{0.01};  //tolerance on the step length
    double epsilon_res{0.01};   //tolerance on the residual
    double initial_step{0.5};   //initial step size
    double initial_step_nesterov {0.1}; // initial step size for the nesterov method
    double maxit{1000};         //maximum number of iterations
    double mu{0.92};            //parameter for exponential and inverse decay
    double eta{0.9};            //memory parameter heavy ball
};

// Declaration of three function, one for each possible method
std::vector<double> gradient_method(const Data& );
std::vector<double> Heavy_ball(const Data& );
std::vector<double> Nesterov(const Data& );

double Inverse_decay(const Data& , unsigned int, const double );

double norm(const std::vector<double> &  );

std::vector<double> operator-(std::vector<double>, std::vector<double>);
std::vector<double> operator+(std::vector<double>, std::vector<double>);
std::vector<double> operator*(double, std::vector<double>);




#endif // GRADIENT_HPP