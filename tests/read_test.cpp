#define BOOST_TEST_MODULE ReadTest

#include <boost/test/unit_test.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <complex>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <MATio/MATio.hpp>
#include <map>

using namespace Eigen;

struct ReadRealFixture
{
  std::map<std::string, Eigen::MatrixXd> mat;
  const double epsilon = 10e-6;
  const std::string file = "test.mat";

  ReadRealFixture()
  {
    mat["r14"].resize(1, 4);
    mat["r14"] << 0.859442, 0.805489, 0.576722, 0.182922;

    mat["r41"].resize(4, 1);
    mat["r41"] << 0.479922, 0.904722, 0.609867, 0.617666;

    mat["r42"].resize(4, 2);
    mat["r42"] << 0.903721, 0.19781, 0.890923, 0.0305409, 0.334163, 0.744074, 0.698746, 0.500022;
  }
};

struct ReadComplexFixture
{
  std::map<std::string, Matrix<std::complex<double>, Dynamic, Dynamic>> mat;
  const double epsilon = 10e-6;
  const std::string file = "test.mat";

  ReadComplexFixture()
  {
    mat["c14"].resize(1, 4);
    mat["c14"].real() << 0.99715, 0.972018, 0.750809, 0.855213;
    mat["c14"].imag() << -0.0754396, 0.234904, -0.66052, -0.518277;

    mat["c41"].resize(4, 1);
    mat["c41"].real() << 0.0632169, 0.756359, 0.983814, -0.997988;
    mat["c41"].imag() << 0.998, -0.654156, 0.179192, 0.0634089;

    mat["c42"].resize(4, 2);
    mat["c42"].real() << -0.427325, -0.568524, 0.65396, -0.99933, -0.1798, 0.181525, 0.783322, -0.217916;
    mat["c42"].imag() << -0.904098, -0.822667, 0.756529, 0.0365981, -0.983703, -0.983386, 0.621616, -0.975968;
  }
  // c42
};
BOOST_AUTO_TEST_CASE(test_read_real)
{
  std::cout << "Running read test on real matrices" << std::endl;
  ReadRealFixture fix;

  // Open test.mat
  Eigen::MatioFile file(fix.file.c_str(), MAT_ACC_RDONLY, false);

  for (const auto& mat : fix.mat)
  {
    Eigen::MatrixXd matrix;
    file.read_mat(mat.first.c_str(), matrix);
    BOOST_REQUIRE_MESSAGE(matrix.size() == mat.second.size(), "matrix size doesn't match!");
    BOOST_REQUIRE_MESSAGE(matrix.isApprox(mat.second, fix.epsilon), "\nRead:\n" << matrix << "\nExpected:\n"
                                                                                << mat.second);
  }
}

BOOST_AUTO_TEST_CASE(test_read_complex)
{
  std::cout << "Running read test on complex matrices" << std::endl;
  ReadComplexFixture fix;

  // Open test.mat
  Eigen::MatioFile file(fix.file.c_str(), MAT_ACC_RDONLY, false);

  // Read and print the complex matrices
  for (const auto& mat : fix.mat)
  {
    Matrix<std::complex<double>, Dynamic, Dynamic> matrix;
    file.read_mat(mat.first.c_str(), matrix);
    BOOST_REQUIRE_MESSAGE(matrix.size() == mat.second.size(), "matrix size doesn't match!");
    BOOST_REQUIRE_MESSAGE(matrix.isApprox(mat.second, fix.epsilon), "\nRead:\n" << matrix << "\nExpected:\n"
                                                                                << mat.second);
  }
}
