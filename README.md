## Parallel Computing

Parallelizes Matrix operations such as:

1. Matrix Multiplication
2. Gaussian Elimination
3. Matrix Inversion (using Co-factors and Minors)

This project compares the time taken to perform these operations using *pthreads* and *openmp*.


### Run the Project
* Clone the repository
* From the root of project use command
    ```
    make
    ```
    Let the files compile and then an executable **./a.out** will be generated.
* Run the executable
  ``` shell
  ./a.out <Argument_1> <Argument_2>
  ```
  * Argument_1: This specifies the which of the 3 operations to run
  * Argument_2: This specifies the test case number to run

  *If no arguments are provided then all the 3 operaions with all the test cases will run. However, if only one arguemnt is provided then only that operaion will run with all the test cases.*
* 
