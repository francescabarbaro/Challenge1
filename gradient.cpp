#include "gradient.hpp"


std::vector<double> gradient_method(const Data &data)
{
    //initial values
    std::vector<double> current_point = data.start_point;
    std::vector<double> previous_point = data.start_point;
    double alpha = data.initial_step;

    unsigned int i{0}; //counter 
    double error_step=data.epsilon_step+1;
    while(i< data.maxit &&  error_step > data.epsilon_step && norm(data.grad(current_point)) > data.epsilon_res){

        //update previous_point
        previous_point = current_point;

        //update step size
        alpha = Armijo(data, current_point);

        //update current_point
        current_point = current_point - alpha * data.grad(current_point);

        //update the error_step
        error_step = norm(current_point - previous_point);
        //increase counter
        ++i;
    }

    //std::cout<<alpha<<std::endl; //problema con il valore di alpha
    //std::cout<<norm(data.grad(current_point))<<std::endl;
    //std::cout<<error_step<<std::endl; //0
    //std::cout<<i<<std::endl;


    return current_point;
}

// function to find the next step size with the Armijo role
double Armijo(const Data &data, std::vector<double> &current_point) {
    double alpha_k = data.initial_step;
    std::vector<double> grad = data.grad(current_point);

    //condition to be satisfied
    bool cond= false;
    double sx{0.0};
    double dx{0.0};

    sx = data.f(current_point) - data.f(current_point - alpha_k * grad);
    dx = data.sigma*alpha_k* std::pow(norm(grad),2);
    cond = sx >= dx;

    //counter
    unsigned int i = 0;
    //while loop to find the next step size
    while(!cond && i<data.maxit){
        //update alpha
        alpha_k= alpha_k/2;
        //check the condition
        sx = data.f(current_point) - data.f(current_point - alpha_k * grad);
        dx = data.sigma* alpha_k * std::pow(norm(grad),2);
        cond = sx >= dx;
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
