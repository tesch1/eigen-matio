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

const char * datafile = "../tests/data.mat";

TEST(read, float) {
  Matrix3f ff;
  MatrixXf ffx;
  EXPECT_EQ(-1, read_mat(datafile, "ff", ff));
  EXPECT_EQ( 0, read_mat(datafile, "ff", ffx));
}
TEST(read, double) {
  Matrix3d dd;
  MatrixXd ddx;
  Matrix<double,2,4> dd24;
  EXPECT_EQ(-1, read_mat(datafile, "dd", dd));
  EXPECT_EQ(0, read_mat(datafile, "dd", ddx));
  EXPECT_EQ(0, read_mat(datafile, "dd", dd24));
}
TEST(rw, float) {
  MatrixXf ff;
  MatrixXf off;
  ASSERT_EQ(0, read_mat(datafile, "ff", ff));
  ASSERT_EQ(0, write_mat("out.mat", "off", ff));
  ASSERT_EQ(0, read_mat("out.mat", "off", off));
  ASSERT_NEAR((ff - off).norm(), 0, 1e-7);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
