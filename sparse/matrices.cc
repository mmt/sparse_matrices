#include "sparse/matrices.h"

#include <assert.h>

extern "C" {

#include "cs.h"

}  // extern "C"

namespace matrices {

namespace {

std::string GetMatrixName(MatrixName matrix) {
    switch (matrix) {
    case ASH219:
        return "ash219";
    case BCSSTK01:
        return "bcsstk01";
    case BCSSTK16:
        return "bcsstk16";
    case FS_183_1:
        return "fs_183_1";
    case IBM32A:
        return "ibm32a";
    case IBM32B:
        return "ibm32b";
    case LP_AFIRO:
        return "lp_afiro";
    case MBEACXC:
        return "mbeacxc";
    case T1:
        return "t1";
    case WEST0067:
        return "west0067";
    case NUM_MATRICES:
    default:
        assert(false);
        return std::string();
    }
}

std::string GetMatrixPath(MatrixName matrix) {
    return std::string("./external/csparse/Matrix/" + GetMatrixName(matrix));
}

}  // namespace

cs *LoadTripletFormMatrix(MatrixName matrix) {
    cs *T;
    {
        std::string filepath = GetMatrixPath(matrix);
        FILE *file = fopen(filepath.c_str(), "r");
        if (!file) {
            return nullptr;
        }
        // Load triplet form matrix form stdin.
        T = cs_load(file);
        fclose(file);
    }
    return T;
}

}  // namespace csparse
