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

#include <stdlib.h>
#include <iostream>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "MATio"
#include "gtest/gtest.h"

using namespace Eigen;
using namespace matio;

std::string datafile;

TEST(read, float) {
  Matrix3f ff;
  MatrixXf ffx;
  EXPECT_THROW(read_mat(datafile, "ff", ff), std::invalid_argument);
  EXPECT_NO_THROW(read_mat(datafile, "ff", ffx));
}
TEST(read, double) {
  Matrix3d dd;
  MatrixXd ddx;
  Matrix<double,2,4> dd24;
  EXPECT_THROW(read_mat(datafile, "dd", dd), std::invalid_argument);
  EXPECT_NO_THROW(read_mat(datafile, "dd", ddx));
  EXPECT_NO_THROW(read_mat(datafile, "dd", dd24));
  EXPECT_EQ((ddx - dd24).norm(), 0);
}
TEST(rw_member, float) {
  MatrixXf ff;
  MatrixXf off;
  MatioFile f(datafile);
  ASSERT_EQ(0, f.read_mat("ff", ff)) << f.lasterr();
  MatioFile fo("out.mat");
  ASSERT_EQ(0, fo.write_mat("off", ff, true)) << fo.lasterr();
  ASSERT_EQ(0, fo.read_mat("off", off)) << fo.lasterr();
  ASSERT_NEAR((ff - off).norm(), 0, 1e-7);
}
TEST(rw_func, float) {
  MatrixXf ff;
  MatrixXf off;
  ff = MatrixXf::Random(3,4);
  EXPECT_NO_THROW(write_mat("out.mat", "off", ff, true));
  ff.setZero();
  EXPECT_NO_THROW(read_mat(datafile, "ff", ff));
  EXPECT_NO_THROW(write_mat("out.mat", "off", ff, true));
  EXPECT_THROW(write_mat("out.mat", "off", ff), std::invalid_argument);
  EXPECT_NO_THROW(read_mat("out.mat", "off", off));
  ASSERT_NEAR((ff - off).norm(), 0, 1e-7);
}

int main(int argc, char * argv[])
{
  datafile = getenv("CMAKE_SOURCE_DIR")
    ? std::string(getenv("CMAKE_SOURCE_DIR")) + "/tests/data.mat"
    : "../tests/data.mat";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
