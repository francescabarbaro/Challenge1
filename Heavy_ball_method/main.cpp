#include <iostream>
#include <cmath>
#include "gradient.hpp"

int main (){

//Define the function f and his gradient as lambdas functions
    std::function<double(std::vector<double>)> f=[](std::vector<double> x){
        return x[0]*x[1] + 4*std::pow(x[0],4) + std::pow(x[1],2) + 3*x[0];
    };

    std::function<std::vector<double>(std::vector<double>)> grad=[](std::vector<double> x){
        std::vector<double> gradient;

        gradient.emplace_back(x[1] + 16*std::pow(x[0],3) + 3);
        gradient.emplace_back(x[0] + 2*x[1]);

        return gradient;
    };


//Assign values to my structure of data
    Data data;
    data.f = f;
    data.grad = grad;
    data.start_point = {0.0,0.0};
    data.epsilon_step = std::pow(10,-6);
    data.epsilon_res = std::pow(10,-6);
    data.initial_step = 0.25;
    data.maxit = 1000;
    //data.sigma = 0.3;
    data.mu = 0.5;
    data.eta = 0.9;

    // find the minimum point in the function f
    std::vector<double> minimum = data.start_point;
    minimum = gradient_method(data);

    std::cout << "the minimum point is: ";
    for(std::size_t i=0; i<minimum.size(); ++i)
        std::cout<<minimum[i]<<"\t";

    std::cout<<std::endl;

    return 0;

}