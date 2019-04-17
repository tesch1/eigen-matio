# eigen-matio (MATio)

C++ single-file header-only classes for reading and writing
[Eigen](http://http://eigen.tuxfamily.org) matrices to/from matlab
data files.  It requires the
['matio'](http://sourceforge.net/projects/matio/) library as a
backend.

# eigen-mexeig (MexEig)

C++ single-file-header [MexEig](./MexEig) for inclusion in mex files
to simply convert Eigen matrices to and from mxArray structures.

# Overview

There are two functions in MexEig:
- EigenToMxArray(mxArray * dst, const Matrix & src)
- MxArrayToEigen(Matrix & dst, const mxArray * src)

MATio exports a single class:
- MatioFile wraps a matio data file, and provides read_mat() and
  write_mat() functions to read and write matrices from that file.

# Using (MexEig)

Just `#include "MexEig"` in a mex .cpp file, and call the wrappers.
If the requested conversions are impossible, exceptions will be
thrown, so catch those too:

```cpp
#include "mex.h"
#include <iostream>
#include <Eigen/Core>
#include "MexEig"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  try {
    if (nrhs != 1) throw std::invalid_argument("requires one input arg");
    if (nlhs != 1) throw std::invalid_argument("requires one ouput arg");

    Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> x;
    MxArrayToEigen(x, prhs[0]);
    plhs[0] = EigenToMxArray(x);
  }
  catch (std::exception & ex) {
    mexErrMsgIdAndTxt("tmp:error", ex.what());
  }
}
```

# Using (MATio)

Using the bare functions in MATio:
```cpp
#include "Eigen/Core"
#include "Eigen/Dense"
#include ".../MATio"

using namespace Eigen;

Matrix3f ff;

// read it into floats
read_mat("data.mat", "ff", ff);
std::cout << "ff=" << ff << std::endl;

// write it out as doubles
write_mat("data.mat", "dd", ff.cast<double>());
```

Using the MatioFile class, potentially more efficient:

```cpp
#include "Eigen/Core"
#include "Eigen/Dense"
#include ".../MATio"

using namespace Eigen;

MatioFile file("data.mat");

Matrix3f ff;

// read it into floats
file.read_mat("ff", ff);
std::cout << "ff=" << ff << std::endl;

ff = Matrix3f::Random();

// write it out as doubles
file.write_mat("dd", ff.cast<double>());
```

# Building

```sh
git clone git@github.com:tesch1/eigen-matio.git
cd eigen-matio
cmake -Bbuild .
cmake --build build
cmake --build build --target test
```

# Octave test

There's a [small example](./tests/test.m) showing how to build an
octave module using [MexEig](./MexEig)

# Contributing

Contributions welcome.  They must be MPL2 licensed and maintain the
same code formatting.

# TODO
- error checking
- gather error messages from matio library
- sparse matrix support
- struct and cell support, read/write & parse
- more testing
 - test against matio-1.3.4(?) because still shipping with RH6
- eventually submit to Eigen for inclusion in unsupported(?)

# License
Mozilla 2.0, like the rest of Eigen.
