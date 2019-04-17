// -*- c++ -*-
//
// This file is part of eigen-matio, a lightweight C++ template
// library for reading data files into Eigen matrices.
//
// Copyright (C) 2019 Michael Tesch, tesch1 (a) gmail com
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
#include <iostream>
#include <Eigen/Dense>
#include <MATio>

using namespace Eigen;
using namespace matio;

int main(int argc, char * argv[])
{
  const char * filename = "../tests/data.mat";
  const char * objname = "dd";

  for (int i = 1; i < argc; i++) {
    filename = argv[i];
    if (i < argc-1) {
      objname = argv[i+1];
      i++;
    }

    // read
    MatioFile f(filename);
    MatrixXd M;
    if (f) {
      if (f.read_mat(objname, M))
        std::cout << "error: " << f.lasterr() << "\n";
      else
        std::cout << objname << " = " << M << "\n";
    }
    
    // next
    filename = argv[i];
  }
}
