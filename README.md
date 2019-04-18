# eigen-matio (MATio)

C++11 *single-file-header* [MATio](./MATio) for reading and writing
[Eigen](http://http://eigen.tuxfamily.org) matrices to/from matlab
data files.  It uses the
['matio'](http://sourceforge.net/projects/matio/) library as a
backend.

# eigen-mexeig (MexEig)

C++11 *single-file-header* [MexEig](./MexEig) for inclusion in mex files
to simply convert Eigen matrices to and from mxArray structures.

# Overview

There are two functions in MexEig:
- `template <class Matrix> EigenToMxArray(mxArray * dst, const Matrix & src)`
- `template <class Matrix> MxArrayToEigen(Matrix & dst, const mxArray * src)`

MATio exports a single class MatioFile():
- `MatioFile` wraps a matio data file, and provides `read_mat()` and
  `write_mat()` functions to read and write matrices from that file.
- `read_mat()` and `write_mat()` return 0 on success, and non-zero on
  failure.  In event of failure, the error message can be retrieved
  from `lasterr()`.

And two stand-alone functions that throw standard exceptions on
error conditions:
- `template <class Derived> void read_mat(const char * filename, const char * matname, Derived & matrix)`
- `template <class Derived> void write_mat(const char * filename, const char * matname, Derived & matrix, bool replace = false)`


# Using (MexEig)

Just `#include "MexEig"` in a mex .cpp file, and call the wrappers.
If the requested conversions are impossible, exceptions will be
thrown, so maybe catch those:

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
#include <iostream>
#include "Eigen/Dense"
#include "MATio"

using namespace Eigen;

int main(int argc, char *argv[])
{
  Matrix3f ff;
  
  // read matrix 'ff' from file 'data.mat' in as floats
  try {
    read_mat("data.mat", "ff", ff);
    std::cout << "ff=" << ff << std::endl;
  
    // write it back out as double precision 'dd'
    write_mat("data.mat", "dd", ff.cast<double>());
  }
  catch (const std::exception & ex) {
    std::cout << "error:" << ex.what() << std::endl;
  }
}
```

Using the MatioFile class, potentially more efficient:

```cpp
#include "Eigen/Core"
#include "Eigen/Dense"
#include ".../MATio"

using namespace Eigen;
int main(int argc, char *argv[])
{
  MatioFile file("data.mat");
  Matrix3f ff;
  
  // read matrix 'ff' in as single precision
  if (!file.read_mat("ff", ff)) {
    // show what we got
    std::cout << "ff=" << ff << std::endl;
  }
  else {
    std::cout << "error: " << file.lasterr() << std::endl;
  }

  ff = Matrix3f::Random();
  
  // write ff as double precision matrix 'dd'
  if (!file.write_mat("dd", ff.cast<double>()))
    std::cout << "error: " << file.lasterr() << std::endl;
}
```

# Building the tests

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

Contributions / bug fixes welcome.  They must be MPL2 licensed and
maintain the same code formatting.

# TODO
- sparse matrix support
- struct and cell support, read/write & parse
- more testing
 - test against matio-1.3.4(?) because still shipping with RH6
- when it's stable submit to Eigen or matio

# ChangeLog

- v0.0.1
  initial release, not very good but semi-functional.
- v1.0.0
  cleaned up a lot of small problems and changed the API.

# License
Mozilla 2.0, like the rest of Eigen.
