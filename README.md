# eigen-matio
[Eigen](http://http://eigen.tuxfamily.org) header-only library for reading and writing
Eigen matrices to/from matlab data files, using the ['matio'](http://sourceforge.net/projects/matio/)
library as a backend.  It would be nice to incorporate this with Eigen someday.

# Usage
there are two interfaces: 
- a MatioFile() class
- bare functions that hide the MatioFile() class

Using the bare functions:
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

# To install
```
mkdir build
cd build
cmake ..
sudo make install
```

# Unit Tests (linux platforms)
- Tests that MATio can read 1D and 2D arrays of real and complex doubles
- From the test directory, run ../build/tests/read_test
