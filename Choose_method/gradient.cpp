#include "gradient.hpp"

// Implementation of the regular gradient descent method
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
        alpha = Inverse_decay(data, i, data.initial_step);

        //update current_point
        current_point = current_point - alpha * data.grad(current_point);

        //update the error_step
        error_step = norm(current_point - previous_point);
        //increase counter
        ++i;
    }

    // return the minimum point found
    return current_point;
}

// Implementation of the heavy ball method
std::vector<double> Heavy_ball(const Data &data)
{
    //initial values
    std::vector<double> current_point = data.start_point;
    std::vector<double> previous_point = data.start_point;
    double alpha = data.initial_step;
    std::vector<double> grad =  data.grad(current_point);
    std::vector<double> d = - alpha * grad;

    unsigned int i{0}; //counter
    double error_step=data.epsilon_step+1;
    while(i< data.maxit &&  error_step > data.epsilon_step && norm(grad) > data.epsilon_res){

        //update previous_point
        previous_point = current_point;

        //update current_point
        current_point = current_point + d;

        //update gradient
        grad = data.grad(current_point);

        //update d
        d = data.eta*d - alpha * grad;

        //update alpha
        alpha = Inverse_decay( data, i,data.initial_step);

        //update the error_step
        error_step = norm(current_point - previous_point);

        //increase counter
        ++i;
    }
    // return the minimum point found
    return current_point;
}


// Implementation of the Nesterov method
std::vector<double> Nesterov(const Data &data)
{
    //initial values
    double alpha = data.initial_step_nesterov;

    std::vector<double> previous_point = data.start_point;
    std::vector<double> grad =  data.grad(previous_point);
    std::vector<double> current_point = previous_point - alpha * grad;
    std::vector<double> y = current_point + data.eta*(current_point - previous_point);

    unsigned int i{0}; //counter
    double error_step=data.epsilon_step+1;
    while(i< data.maxit &&  error_step > data.epsilon_step && norm(grad) > data.epsilon_res){

        //update previous_point
        previous_point = current_point;

        //update alpha
        alpha = Inverse_decay( data, i, data.initial_step_nesterov);

        //update gradient
        grad = data.grad(y);

        //update current_point
        current_point = y - alpha*grad;

        //update y
        y = current_point + data.eta*(current_point - previous_point);

        //update the error_step
        error_step = norm(current_point - previous_point);

        //increase counter
        ++i;
    }

    return current_point;
}


//Function to define the next step with inverse decay method
double Inverse_decay(const Data & data, unsigned int k, const double alpha0) {
    double alpha_k = alpha0;
    alpha_k = alpha0 /(1+data.mu*k);
    return alpha_k;
}



// function to evaluate the euclidean norm of a vector
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
std::vector<double> operator-( std::vector<double> vec1,  std::vector<double> vec2) {
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

//operator + between two vectors
        std::vector<double> operator+( std::vector<double> vec1,  std::vector<double> vec2) {
    // check if the vector have the same dimension
    if (vec1.size() != vec2.size()) {
        // print an error message
        std::cerr << "Errore: I vettori devono avere le stesse dimensioni per eseguire la sottrazione." << std::endl;
    }

    std::vector<double> result;

    // summation
    for (size_t i = 0; i < vec1.size(); ++i) {
        result.emplace_back(vec1[i] + vec2[i]);
    }
    return result;
}

// operator * between a vector and a scalar
std::vector<double> operator*(double scalar,  std::vector<double> vec) {
    std::vector<double> result;

    // product between a scalar and a vector
    for (const double& elem : vec) {
        result.emplace_back(scalar * elem);
    }

    return result;
}


