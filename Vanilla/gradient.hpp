#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include<cmath>
#include <functional>
#include <vector>
#include <iostream>

//structure called Data, containing the data and parameters needed
struct Data
{
    
    std::function<double(std::vector<double>)> f;                   //function
    std::function<std::vector<double>(std::vector<double>)> grad;   //gradient
    std::vector<double> start_point{0.0,0.0};                       //starting point
    
    double epsilon_step{0.01};  //tolerance on the step length
    double epsilon_res{0.01};   //tolerance on the residual
    double initial_step{1.0};   //initial step size
    double maxit{1000};         //maximum number of iterations
    double sigma{0.3};          //parameter for Armijo rule
};

// Declaration of the method to do the gradient descent
std::vector<double> gradient_method(const Data& );
// Function to compute the Armijo rule in the choice of the step-size
double Armijo(const Data& , std::vector<double> & );
// Function to compute the norm of two vectors
double norm(const std::vector<double> &  );

// Operator - to compute the subtraction between 2 vectors
std::vector<double> operator-(std::vector<double>, std::vector<double>);
// Operator * to compute multiplication between a scalar and a vector
std::vector<double> operator*(double, std::vector<double>);



#endif // GRADIENT_HPP