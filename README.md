# Challenge1
First challenge PACS course

Francesca Barbaro  
Codice persona: 10662154  
Matricola: 220332  


In this repository you find:  

### Makefile:
Every directory contains its Makefile, so the code is 'ready to go'.
In order to smoothly test the code just go in the desired directory
and type `make`.
To run the code and visualize the result, the minimum point of the function f, type `./main`.


### Vanilla:
This directory contains the 'Vanilla' code, where the normal 
gradient descent is implemented with the Armijo rule for the 
step size alpha.

### Choose_alpha:
This directory contains the gradient descent method where is 
possible to select the preferred method for the step alpha between:  
* Armijo
* Exponential decay
* Inverse decay 

I tried to use a Template function and the `if constexpr` statement,
to avoid the usage of the inefficient `if` statement inside the while loop.  
The implemented code doesn't perfectly align with the request, however 
the best I come up with is the one you can find here.

The instructions on how to select the preferred method are contained 
in the file gradient.cpp, in particular in the function 
gradient_method, where the choice has to be made.

### Choose_method:
This directory contains the implementation of a code where the user 
can choose at runtime wheather to use one of the following methods to compute 
the gradient descent:
* Regular Gradient Descent
* Heavy Ball method (or momentum)
* Nesterov method

### Centered_differences:
This directory contains the code where the user can choose which type of gradient use:
* Exact gradient
* Finite Centered differences gradient


