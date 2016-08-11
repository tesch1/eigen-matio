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

# Read Test (linux platforms)
- Tests that MATio can read 1D and 2D arrays of real and complex doubles
- From the test directory, run ../build/tests/read_test
- Should produce the following output
```
--------
r14
0.859442 0.805489 0.576722 0.182922
--------
r41
0.479922
0.904722
0.609867
0.617666
--------
r42
 0.903721   0.19781
 0.890923 0.0305409
 0.334163  0.744074
 0.698746  0.500022
--------
c14
(0.99715,-0.0754396)  (0.972018,0.234904)  (0.750809,-0.66052) (0.855213,-0.518277)
--------
c41
	(0.0632169,0.998)
 (0.756359,-0.654156)
  (0.983814,0.179192)
(-0.997988,0.0634089)
--------
c42
(-0.427325,-0.904098) (-0.568524,-0.822667)
   (0.65396,0.756529)  (-0.99933,0.0365981)
  (-0.1798,-0.983703)  (0.181525,-0.983386)
  (0.783322,0.621616) (-0.217916,-0.975968)
```
