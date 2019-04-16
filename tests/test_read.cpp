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
#include "Eigen/Core"
#include "Eigen/Dense"
#include "MATio"
#include "gtest/gtest.h"

using namespace Eigen;

TEST(read, float) {
  Matrix3f ff;
  read_mat("data.mat", "ff", ff);
}
TEST(read, double) {
  Matrix3d dd;
  read_mat("data.mat", "dd", dd);
}
TEST(rw, float) {
  Matrix3f ff;
  Matrix3f off;
  read_mat("data.mat", "ff", ff);
  write_mat("out.mat", "off", ff);
  read_mat("data.mat", "off", off);
  ASSERT_NEAR((ff - off).norm(), 0, 1e-7);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
