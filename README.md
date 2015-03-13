# eigen-matio
eigen header-only file for reading and writing matlab data files, using the 'matio' library as a backend.

# Usage
there are two interfaces: 
- a MatioFile() class
- bare functions that hide the MatioFile() class

Using the bare functions:
```cpp
#include "Eigen/Core"
#include "Eigen/Dense"
#include ".../MATIo"

using namespace Eigen;

Matrix3f ff;

// read it into floats
mat_read("data.mat", "ff", ff);
std::cout << "ff=" << ff << std::endl;

// write it out as doubles
mat_write("data.mat", "dd", ff.cast<double>());
```

Using the MatioFile class, potentially more efficient:
```cpp
#include "Eigen/Core"
#include "Eigen/Dense"
#include ".../MATIo"

using namespace Eigen;

MatioFile file("data.mat");

Matrix3f ff;

// read it into floats
file.mat_read("ff", ff);
std::cout << "ff=" << ff << std::endl;

ff = Matrix3f::Random();

// write it out as doubles
file.mat_write("dd", ff.cast<double>());
```

# TODO
- error checking
- gather error messages from matio library
- sparse matrix support
- fill-out the data types for reading
- some testing, any testing!
- eventually submit to Eigen for inclusion in unsupported(?)

# License
Mozilla 2.0, like the rest of Eigen.
