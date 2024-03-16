#include "gradient.hpp"


std::vector<double> gradient_method(const Data &data)
{
    //initial values
    std::vector<double> current_point = data.start_point;
    std::vector<double> previous_point = data.start_point;
    double alpha = data.initial_step;

    unsigned int i{0}; //counter 

    while(i< data.maxit && norm(current_point - previous_point) < data.epsilon_step && norm(data.grad(current_point)) < data.epsilon_res){

        //update previous_point
        previous_point = current_point;

        //update step size
        alpha = Armijo(data, current_point);

        //update current_point
        current_point = current_point - alpha * data.grad(current_point);


        //increase counter
        ++i;
    }


    return current_point;
}

// function to find the next step size with the Armijo role
double Armijo(const Data &data, std::vector<double> &current_point) {
    double alpha_k = data.initial_step;
    std::vector<double> grad = data.grad(current_point);

    //condition to be satisfied
    bool cond= false;
    cond = data.f(current_point) - data.f(current_point - alpha_k * grad) >= data.sigma* std::pow(norm(grad),2);

    //counter
    unsigned int i = 0;
    //while loop to find the next step size
    while(!cond && i<data.maxit){
        //update alpha
        alpha_k= alpha_k/2;
        //check the condition
        cond = data.f(current_point) - data.f(current_point - alpha_k * grad) >= data.sigma* std::pow(norm(grad),2);
        //increase the counter
        ++i;
    }
    // DOVREI CONTROLLARE SE HA TROVATO O NO
    return alpha_k;
}

// function to evaluate the eucledean norm of a vector
double norm(const std::vector<double> &x) {
    double vec_norm = 0.0;
    //euclidean norm
    for (auto elem : x) {
        vec_norm += elem * elem;
    }
    // square root
    vec_norm = std::sqrt(vec_norm);

    return vec_norm;
}

// operator - between two vectors
std::vector<double> operator-(const std::vector<double> vec1, const std::vector<double> vec2) {
    // check if the vector have the same dimension
    if (vec1.size() != vec2.size()) {
        // print an error message
        std::cerr << "Errore: I vettori devono avere le stesse dimensioni per eseguire la sottrazione." << std::endl;
    }

    std::vector<double> result;

    // subtraction
    for (size_t i = 0; i < vec1.size(); ++i) {
        result.emplace_back(vec1[i] - vec2[i]);
    }
    return result;
}

// operator * between a vector and a scalar
std::vector<double> operator*(double scalar, const std::vector<double> vec) {
    std::vector<double> result;

    // product between a scalar and a vector
    for (const double& elem : vec) {
        result.emplace_back(scalar * elem);
    }

    return result;
}
