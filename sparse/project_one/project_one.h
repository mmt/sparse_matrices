#ifndef SPARSE_PROJECT_ONE_H
#define SPARSE_PROJECT_ONE_H

extern "C" {

#include "cs.h"

}  // extern "C"

namespace project_one {

// Problem one.
csi cs_gaxpy(const cs *A, const double *x, double *y);

// Problem two.
csi cs_gatxpy(const cs *A, const double *x, double *y);

// Problem three.
cs *cs_find(const cs *A);

// Problem four.
csi cs_gaxpy_sym(const cs *A, const double *x, double *y);

} // namespace project_one

#endif // SPARSE_PROJECT_ONE_H
