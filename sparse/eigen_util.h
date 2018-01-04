#include <Eigen/Sparse>

extern "C" {

#include "cs.h"

}  // extern "C"

namespace eigen_util {

Eigen::SparseMatrix<double, Eigen::ColMajor> CsToEigen(cs *A);

cs *EigenToCs(const Eigen::SparseMatrix<double, Eigen::ColMajor> &M, bool values);
/* cs *EigenToCs(const Eigen::SparseMatrix<double, Eigen::RowMajor> &M, bool values); */

} // eigen_util
