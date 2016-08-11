// -*- c++ -*-
// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2015 Michael Tesch, tesch1 (a) gmail com
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
#ifndef EIGEN_MATIO_MODULE
#define EIGEN_MATIO_MODULE
#include <sstream>
#include "matio.h"
#ifndef MATIO_VERSION
#define MATIO_VERSION (MATIO_MAJOR_VERSION * 100 + MATIO_MINOR_VERSION * 10 + MATIO_RELEASE_LEVEL)
#endif

#if MATIO_VERSION <= 150
#define MAT_COMPRESSION_NONE COMPRESSION_NONE
#define MAT_COMPRESSION_ZLIB COMPRESSION_ZLIB
typedef ComplexSplit mat_complex_split_t;
#endif

namespace Eigen {

namespace internal {

// defaults
template <typename Tp> struct matio_type;
template <typename Tp> struct matio_class;
template <typename Tp> struct matio_flag { static const matio_flags fid = (matio_flags)0; };
// specializations
//template <> struct matio_type<xxx> { typedef xxx type; matio_types id = MAT_T_UNKNOWN; };
template <> struct matio_type<int8_t>   { typedef int8_t type;   static const matio_types tid = MAT_T_INT8; };
template <> struct matio_type<uint8_t>  { typedef uint8_t type;  static const matio_types tid = MAT_T_UINT8; };
template <> struct matio_type<int16_t>  { typedef int16_t type;  static const matio_types tid = MAT_T_INT16; };
template <> struct matio_type<uint16_t> { typedef uint16_t type; static const matio_types tid = MAT_T_UINT16; };
template <> struct matio_type<int32_t>  { typedef int32_t type;  static const matio_types tid = MAT_T_INT32; };
template <> struct matio_type<uint32_t> { typedef uint32_t type; static const matio_types tid = MAT_T_UINT32; };
template <> struct matio_type<float>    { typedef float type;    static const matio_types tid = MAT_T_SINGLE; };
template <> struct matio_type<double>   { typedef double type;   static const matio_types tid = MAT_T_DOUBLE; };
template <> struct matio_type<long double> { typedef double type; static const matio_types tid = MAT_T_DOUBLE; };
template <> struct matio_type<int64_t>  { typedef int64_t type;  static const matio_types tid = MAT_T_INT64; };
template <> struct matio_type<uint64_t> { typedef uint64_t type; static const matio_types tid = MAT_T_UINT64; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_MATRIX; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_COMPRESSED; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_UTF8; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_UTF16; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_UTF32; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_STRING; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_CELL; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_STRUCT; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_ARRAY; };
//template <> struct matio_type<xxx> { typedef xxx type; static const matio_types tid = MAT_T_FUNCTION; };
template <typename Tp> struct matio_type<std::complex<Tp> >
{
  typedef typename matio_type<Tp>::type type;
  static const matio_types tid = matio_type<Tp>::tid;
};

//template <> struct matio_class<xxx> { static const matio_classes cid = MAT_C_CELL; };
//template <> struct matio_class<xxx> { static const matio_classes cid = MAT_C_STRUCT; };
//template <> struct matio_class<xxx> { static const matio_classes cid = MAT_C_OBJECT; };
template <> struct matio_class<char>     { static const matio_classes cid = MAT_C_CHAR; };
//template <> struct matio_class<xxx>  { static const matio_classes cid = MAT_C_SPARSE; };
template <> struct matio_class<float>    { static const matio_classes cid = MAT_C_SINGLE; };
template <> struct matio_class<double>   { static const matio_classes cid = MAT_C_DOUBLE; };
template <> struct matio_class<long double> { static const matio_classes cid = MAT_C_DOUBLE; };
template <> struct matio_class<int8_t>   { static const matio_classes cid = MAT_C_INT8; };
template <> struct matio_class<uint8_t>  { static const matio_classes cid = MAT_C_UINT8; };
template <> struct matio_class<int16_t>  { static const matio_classes cid = MAT_C_INT16; };
template <> struct matio_class<uint16_t> { static const matio_classes cid = MAT_C_UINT16; };
template <> struct matio_class<int32_t>  { static const matio_classes cid = MAT_C_INT32; };
template <> struct matio_class<uint32_t> { static const matio_classes cid = MAT_C_UINT32; };
template <> struct matio_class<int64_t>  { static const matio_classes cid = MAT_C_INT64; };
template <> struct matio_class<uint64_t> { static const matio_classes cid = MAT_C_UINT64; };
//template <> struct matio_class<xxx> { static const matio_classes cid = MAT_C_FUNCTION; };
template <typename Tp> struct matio_class<std::complex<Tp> >
{
  static const matio_classes cid = matio_class<Tp>::cid;
};

template <typename Tp> struct matio_flag<std::complex<Tp> >
{
  static const matio_flags fid = MAT_F_COMPLEX;
};
//template <> struct matio_flag<xxx> { matio_flags fid = MAT_F_GLOBAL; };
//template <> struct matio_flag<xxx> { matio_flags fid = MAT_F_LOGICAL; };
//template <> struct matio_flag<xxx> { matio_flags fid = MAT_F_CLASS_T; };

// reverse map from id to basic type
template <int matio_type_id = -1> struct type_matio {};
template <int matio_class_id = -1> struct class_matio {};
template <> struct type_matio<MAT_T_INT8>   { typedef int8_t   type; };
template <> struct type_matio<MAT_T_UINT8>  { typedef uint8_t  type; };
template <> struct type_matio<MAT_T_INT16>  { typedef int16_t  type; };
template <> struct type_matio<MAT_T_UINT16> { typedef uint16_t type; };
template <> struct type_matio<MAT_T_INT32>  { typedef int32_t  type; };
template <> struct type_matio<MAT_T_UINT32> { typedef uint32_t type; };
template <> struct type_matio<MAT_T_SINGLE> { typedef float    type; };
template <> struct type_matio<MAT_T_DOUBLE> { typedef double   type; };
template <> struct type_matio<MAT_T_INT64>  { typedef int64_t  type; };
template <> struct type_matio<MAT_T_UINT64> { typedef uint64_t type; };

template <> struct class_matio<MAT_C_DOUBLE> { typedef double type; };

} // Eigen::internal::

class MatioFile {

private:
  mat_t * _file;
  mat_ft _ft;
  int _mode;
  bool _written;
  std::stringstream _errstr;

public:

  MatioFile() : _file(NULL), _ft(MAT_FT_DEFAULT), _mode(0), _written(false) {}

  MatioFile(const char * filename,
            int mode = MAT_ACC_RDWR,
            bool create = true,
            mat_ft fileversion = MAT_FT_DEFAULT,
            const char * header = "MatioFile")
    : _file(NULL), _ft(MAT_FT_DEFAULT), _mode(0), _written(false)
  {
    //Mat_LogInit("hi");
    open(filename, mode, create, fileversion, header);
  }

  ~MatioFile()
  {
    close();
  }

  const std::string lasterr() { return _errstr.str(); }

  mat_t * file() { return _file; }

  explicit operator bool() const { return _file != NULL && _errstr.str().size() == 0; }

  int open(const char * filename,
           int mode = MAT_ACC_RDWR,
           bool create = true,
           mat_ft fileversion = MAT_FT_DEFAULT,
           const char * header = "MatioFile")
  {
    if (_file)
      close();
    _file = Mat_Open(filename, mode);
    if (_file == NULL && create && mode != MAT_ACC_RDONLY) {
#if MATIO_VERSION >= 150
      _file = Mat_CreateVer(filename, header, fileversion);
#else
      _file = Mat_Create(filename, header);
#endif
    }
    if (NULL == _file) {
      _errstr.clear();
      _errstr << "MatioFile::open() unable to open " << filename << "/" << fileversion << "\n";
      return -1;
    }
    _mode = mode;
    _ft = fileversion;
    return 0;
  }

  void close()
  {
    if (_file)
      Mat_Close(_file);
    _file = NULL;
  }

  // in case reading something after writing it (fflush / fsync would be better)
  int reopen()
  {
    if (_file) {
      std::string filename = Mat_GetFilename(_file);
      Mat_Close(_file);
      _file = Mat_Open(filename.c_str(), _mode);
      if (NULL == _file) {
        _errstr.clear();
        _errstr << "MatioFile() unable to reopen '" << filename << "'\n";
        return -1;
      }
      _written = false;
    }
    return 0;
  }

  // \TODO:
  //Mat_LogInit( const char *prog_name )
  //Mat_LogClose( void )
  //Mat_LogInitFunc(const char *prog_name,
  //   void (*log_func)(int log_level,char *message))

  template <class Derived, matio_compression compression = MAT_COMPRESSION_NONE>
  int
  write_mat(const char * matname, const Derived & matrix)
  {
    if (!_file || !matname) {
      _errstr.clear();
      _errstr << "MatioFile.write_mat() unable to write matrix '" << matname << "'\n";
      return -1;
    }
    typedef typename internal::matio_type<typename Derived::Scalar>::type mat_type;
    matvar_t * var;
#if MATIO_VERSION >= 150
    size_t rows = matrix.rows();
    size_t cols = matrix.cols();
    size_t dims[2] = {rows, cols};
#else
    int rows = matrix.rows();
    int cols = matrix.cols();
    int dims[2] = {rows, cols};
#endif

    matio_types tid = internal::matio_type<typename Derived::Scalar>::tid;
    matio_classes cid = internal::matio_class<typename Derived::Scalar>::cid;
    matio_flags cxflag = internal::matio_flag<typename Derived::Scalar>::fid;

    // \TODO - specialize this for the (common) case where mat_type is the same as
    // Derived::Scalar AND Scalar is NOT complex, in which case we dont need to create
    // temp matrices here...
    void * data;
    Matrix<mat_type,Dynamic,Dynamic> dst_re(rows, cols);
    Matrix<mat_type,Dynamic,Dynamic> dst_im(rows, cols);
    mat_complex_split_t cs;

    // \TODO - sparse matrices
    if (cxflag == MAT_F_COMPLEX) {
      dst_re = matrix.real().template cast<mat_type>();
      dst_im = matrix.imag().template cast<mat_type>();
      data = &cs;
      cs.Re = dst_re.data();
      cs.Im = dst_im.data();
    }
    else {
      dst_re = matrix.real().template cast<mat_type>();
      data = dst_re.data();
    }

    var = Mat_VarCreate(matname, cid, tid, 2, dims, data, cxflag);
    if (NULL == var) {
      _errstr.clear();
      _errstr << "write_mat() unable to create matrix\n";
      return -1;
    }

    // \TODO - thread safety
    int status = Mat_VarWrite(_file, var, compression);
    if (status) {
      _errstr.clear();
      _errstr << "write_mat() unable to put variable '" << matname << "'\n";
    }
    else
      _written = true;

    Mat_VarFree(var);
    return status;
  }

private:

  template <class data_t, class Derived, class Scalar>
  void matrix_from_var(Derived & matrix, matvar_t * var, Scalar zero)
  {
    (void)zero;
    Map<Matrix<data_t, Dynamic, Dynamic> > tmp((data_t *)var->data, var->dims[0], var->dims[1]);
    matrix = tmp.template cast<Scalar>();
  }

  template <class data_t, class Derived, class Scalar>
  void matrix_from_var(Derived & matrix, matvar_t * var, std::complex<Scalar> zero)
  {
    (void)zero;
    mat_complex_split_t * cs = (mat_complex_split_t *)var->data;
    Map<Matrix<data_t, Dynamic, Dynamic> > tmp_re((data_t *)cs->Re, var->dims[0], var->dims[1]);
    Map<Matrix<data_t, Dynamic, Dynamic> > tmp_im((data_t *)cs->Im, var->dims[0], var->dims[1]);
    matrix.resize(var->dims[0], var->dims[1]);
    matrix.real() = tmp_re.template cast<Scalar>();
    matrix.imag() = tmp_im.template cast<Scalar>();
  }

public:

  template <class Derived>
  int
  read_mat(const char * matname, Derived & matrix)
  {
    if (_written)
      reopen();
    if (!_file || !matname) {
      _errstr.clear();
      _errstr << "MatioFile.read_mat() unable to read file for matrix '" << matname << "'\n";
      return -1;
    }

    matvar_t * var = Mat_VarRead(_file, matname);
    if (NULL == var) {
      _errstr.clear();
      _errstr << "read_mat() unable to read matrix '" << matname << "'\n";
      return -1;
    }

    if (var->rank != 2) {
      _errstr.clear();
      _errstr << "read_mat() can only read rank-2 matrices: '" << matname << "':\n ";
      Mat_VarPrint(var, 0);
      Mat_VarFree(var);
      return -1;
    }

    if (static_cast<bool>(var->isComplex) != static_cast<bool>(NumTraits<typename Derived::Scalar>::IsComplex)) {
      _errstr.clear();
      _errstr << "read_mat() complex / real matrix mismatch\n ";
      Mat_VarPrint(var, 0);
      Mat_VarFree(var);
      return -1;
    }

 #define MATIO_HANDLE_READ_TYPE(MAT_T_X)                                 \
     else if (var->data_type == MAT_T_X                                  \
              && var->class_type != MAT_C_SPARSE)                        \
       do {                                                              \
         typedef typename internal::type_matio<MAT_T_X>::type data_t;    \
         typename Derived::Scalar ele_type;      \
         matrix_from_var<data_t>(matrix, var, ele_type); \
       } while (0)

    if (0) {}
    MATIO_HANDLE_READ_TYPE(MAT_T_INT8);
    MATIO_HANDLE_READ_TYPE(MAT_T_UINT8);
    MATIO_HANDLE_READ_TYPE(MAT_T_INT16);
    MATIO_HANDLE_READ_TYPE(MAT_T_UINT16);
    MATIO_HANDLE_READ_TYPE(MAT_T_INT32);
    MATIO_HANDLE_READ_TYPE(MAT_T_UINT32);
    MATIO_HANDLE_READ_TYPE(MAT_T_SINGLE);
    MATIO_HANDLE_READ_TYPE(MAT_T_DOUBLE);
    MATIO_HANDLE_READ_TYPE(MAT_T_INT64);
    MATIO_HANDLE_READ_TYPE(MAT_T_UINT64);
    else {
      _errstr.clear();
      _errstr << "read_mat() unrecognized matrix data_type '" << matname << "':\n ";
      Mat_VarPrint(var, 0);
      Mat_VarFree(var);
      return -1;
    }
#undef MATIO_HANDLE_READ_TYPE

    Mat_VarFree(var);
    return 0;
  }
};

template <class Derived, matio_compression compression = MAT_COMPRESSION_NONE>
int
write_mat(const char * filename, const char * matname, const Derived & matrix)
{
  MatioFile file(filename);
  return file.write_mat<Derived, compression>(matname, matrix);
}

template <class Derived>
int
read_mat(const char * filename, const char * matname, Derived & matrix)
{
  MatioFile file(filename, MAT_ACC_RDONLY, false);
  return file.read_mat(matname, matrix);
}

}

#endif // EIGEN_MATIO_MODULE
