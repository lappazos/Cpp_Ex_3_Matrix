//
// TimeChecker.cpp

#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include "Complex.h"
#include "Matrix.hpp"
#include <eigen3/Eigen/Eigen>

#define SIZE "size "
#define EIG_MUL "eigen mult "
#define EIG_ADD "eigen add "
#define MY_MULT "matlib mult "
#define MY_ADD "matlib add "
#define NUM_OF_ARGS 2
#define MAT_VAL 1

/**
 * check matlib time against rigen time in marix actions
 * @param argc num of args
 * @param argv args array
 * @return 0 if success, 1 else
 */
int main(int argc, char *argv[])
{
    if (argc == NUM_OF_ARGS)
    {
        int num = std::stoi(argv[1]);
        Eigen::MatrixXd eigenMat = Eigen::MatrixXd::Random(num, num);
        std::vector<int> vec = std::vector<int>(num * num, MAT_VAL);
        Matrix<int> mat = Matrix<int>((unsigned int) num, (unsigned int) num, vec);
        std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
        tictoc_stack.push(std::chrono::system_clock::now());
        mat * mat;
        std::chrono::duration<double> elapsed_seconds =
                std::chrono::system_clock::now() - tictoc_stack.top();
        double myMult = elapsed_seconds.count();
        tictoc_stack.pop();
        tictoc_stack.push(std::chrono::system_clock::now());
        mat + mat;
        elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
        double myAdd = elapsed_seconds.count();
        tictoc_stack.pop();
        tictoc_stack.push(std::chrono::system_clock::now());
        eigenMat * eigenMat;
        elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
        double eigenMult = elapsed_seconds.count();
        tictoc_stack.pop();
        tictoc_stack.push(std::chrono::system_clock::now());
        eigenMat + eigenMat;
        elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
        double eigenAdd = elapsed_seconds.count();
        tictoc_stack.pop();
        std::cout << SIZE << num << std::endl;
        std::cout << EIG_MUL << eigenMult << std::endl;
        std::cout << EIG_ADD << eigenAdd << std::endl;
        std::cout << MY_MULT << myMult << std::endl;
        std::cout << MY_ADD << myAdd << std::endl;
        return 0;
    }
    return 1;
}



