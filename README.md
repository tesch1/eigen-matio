# eigen-matio
[Eigen](http://http://eigen.tuxfamily.org) header-only library for reading and writing
Eigen matrices to/from matlab data files, using the ['matio'](http://sourceforge.net/projects/matio/)
library as a backend.  It would be nice to incorporate this with Eigen someday.

Also a single-file header `MexEig` for use in mex files to convert
Eigen matrices to/from mxArray structures.

# Usage
there are two functions in MexEig:
- EigenToMxArray()
- MxArrayToEigen()

there are two interfaces in MATio:
- a MatioFile() class
- bare functions that hide the MatioFile() class

Using the functions in MexEig in a mex .cpp file, just a simple
example that copies the input to the output:

```cpp
#include "mex.h"
#include <iostream>
#include <Eigen/Core>
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
```


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

# Contributing
All contributions welcome!  (With two caveats: they must be MPL2 licensed, and maintain the same code formatting.)

# TODO
- error checking
- gather error messages from matio library
- sparse matrix support
- struct and cell support, read/write & parse
- some testing, any testing!
 - test against matio-1.3.4(?) because still shipping with RH6
- eventually submit to Eigen for inclusion in unsupported(?)

# License
Mozilla 2.0, like the rest of Eigen.
