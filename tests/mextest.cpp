/*
 * mextext.c - example how to use MexEig in a mexFunction
 *
 * Takes an input matrix (inMatrix) copies it to an Eigen::Matrix, and
 * then copies that back into an mxArray, and returns that as
 * (outMatrix).
 *
 * The calling syntax is:
 *
 *     outMatrix = mextest(inMatrix)
 *
 * This is a MEX file for OCTAVE or MATLAB.
*/

#include "mex.h"
#include <iostream>
#include <Eigen/Dense>
#include "MexEig"

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
  try {
    if (nrhs != 1)
      throw std::invalid_argument("requires one input arg");
    if (nlhs != 1)
      throw std::invalid_argument("requires one ouput arg");

    Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> x;
    MxArrayToEigen(x, prhs[0]);
    plhs[0] = EigenToMxArray(x);
  }
  catch (std::exception & ex) {
    mexErrMsgIdAndTxt("tmp:error", ex.what());
  }
}
