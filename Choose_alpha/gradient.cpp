#include "gradient.hpp"


//Template function to select the alpha method
template < StepMethod method>
auto choose_alpha(const Data & data, std::vector<double> & current_point, unsigned int i){
    if constexpr ( method == StepMethod::Armijo) {
        return  Armijo(data, current_point);
    } else if constexpr (method == StepMethod::Exponential_decay) {
        return  Exponential_decay(data, i);
    } else if constexpr (method == StepMethod::Inverse_decay) {
        return  Inverse_decay(data, i);
    } else
        return Armijo(data, current_point);
}

std::vector<double> gradient_method(const Data &data)
{
    //initial values
    std::vector<double> current_point = data.start_point;
    std::vector<double> previous_point = data.start_point;
    double alpha = data.initial_step;
    std::vector<double> grad =  data.grad(current_point);

    unsigned int i{0}; //counter
    double error_step=data.epsilon_step+1;
    while(i< data.maxit &&  error_step > data.epsilon_step && norm(grad) > data.epsilon_res){

        // update previous_point
        previous_point = current_point;

        // update current_point
        current_point = current_point - alpha * grad;
        std::cout<<"current point: "<<current_point[0]<<"  "<<current_point[1]<<std::endl;

        //update the gradient gradient
        grad = data.grad(current_point);
        std::cout<<"grad current point: "<<grad[0]<<"  "<<grad[1]<<std::endl;

        // Update step size based on the selected method using constexpr
        /*
         * HOW TO SELECT THE METHOD:
         * in choose_alpha<...> is written the name of the method that will be called.
         * 1) Armijo: → StepMethod::Armijo
         * 2) Exponential_decay: → StepMethod::Exponential_decay
         * 3) Inverse_decay: → StepMethod::Inverse_decay
         * Decomment the one you want to use
         *
         * if a non-existing choice is made the defaul method Armijo is employed
         */
        alpha = choose_alpha<StepMethod::Armijo>(data, current_point, i);
        //alpha = choose_alpha<StepMethod::Exponential_decay>(data, current_point, i);
        //alpha = choose_alpha<StepMethod::Inverse_decay>(data, current_point, i);

        //update the error_step
        error_step = norm(current_point - previous_point);
        //increase counter
        ++i;
    }

    return current_point;
}

// function to find the next step size with the Armijo rule
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

    return alpha_k;
}
//Function to define the next step size with exponential decay method
double Exponential_decay(const Data & data,  unsigned int k) {
    double alpha_k = data.initial_step;
    alpha_k = alpha_k * std::exp(- data.mu * k);
    return alpha_k;
}

//Function to define the next step with inverse decay method
double Inverse_decay(const Data & data, unsigned int k) {
    double alpha_k = data.initial_step;
    alpha_k = data.initial_step/(1+data.mu*k);
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

