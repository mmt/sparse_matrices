#ifndef SPARSE_MATRICES_H_
#define SPARSE_MATRICES_H_

#include <string>

extern "C" {

#include "cs.h"

}  // extern "C"

namespace matrices {

enum MatrixName {
    ASH219,
    BCSSTK01,
    BCSSTK16,
    FS_183_1,
    IBM32A,
    IBM32B,
    LP_AFIRO,
    MBEACXC,
    T1,
    WEST0067,
    NUM_MATRICES
};


cs *LoadTripletFormMatrix(MatrixName matrix);

}  // namespace matrices

#endif  // SPARSE_MATRICES_H_
