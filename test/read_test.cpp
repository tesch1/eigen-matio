#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <complex>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include "../MATio"

using namespace Eigen;

int main(int argc, char** argv)
{
   (void) argc;
   (void) argv;

   // Open test.mat
   Eigen::MatioFile file("test.mat", MAT_ACC_RDONLY, false);

   // Read & print the real matrices
   const std::vector<std::string> read_reals{"r14", "r41", "r42"};
   for (const std::string& var_name : read_reals)
   {
      MatrixXd matrix;
      file.read_mat(var_name.c_str(), matrix);
      std::cout << "--------" << std::endl << var_name << std::endl << matrix << std::endl; 
   }

   // Read and print the complex matrices
   const std::vector<std::string> read_cplx{"c14", "c41", "c42"};
   for (const std::string& var_name : read_cplx)
   {
      Matrix<std::complex<double>, Dynamic, Dynamic> matrix;
      file.read_mat(var_name.c_str(), matrix);
      std::cout << "--------" << std::endl << var_name << std::endl << matrix << std::endl; 
   }


   return EXIT_SUCCESS;
}
