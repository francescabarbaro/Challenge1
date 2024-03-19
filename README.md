# Challenge1
First challenge PACS course

Francesca Barbaro  
Codice persona: 10662154  
Matricola: 220332  


In this repository you find:  
### Vainlla:
This directory contains the 'Vanilla' code, where the normal 
gradient descent is implemented with the Armijo rule for the 
step alpha.

### Choose_alpha:
This directory contains the gradient descent method where is 
possible to select the preferred method for the step alpha between:  
* Armijo
* Exponential decay
* Inverse decay  

The instructions on how to select the preferred method are containded 
in the file gradient.cpp, in particular in the function 
gradient_method, where the choice has to be made. The choice is done in this way 
in order to use `if constexpr`.

### Centered_differences
This directory contains the gradient descent method where the gradient of the function f is computed
via a finite difference method, in particular the centered differences. 

### Heavy_ball_method
This directory contains the Heavy ball method, also called momentum. 

### Nesterov_method
This directory contains the Nesterov method to implement the gradient descent.

### Makefile
Every directory contains its Makefile, so it is 'ready to go'.
In order to soothly compile and run the code just go in the desired directory
and type `make`.
To visualize the result, and so the minimum point of the function f, type `./main`