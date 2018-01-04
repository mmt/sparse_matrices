#include "eigen_util.h"

namespace eigen_util {

Eigen::SparseMatrix<double> CsToEigen(cs *A) {
    Eigen::SparseMatrix<double> M;
    if (A == nullptr) {
        M.resize(0, 0);
    } else {
        M.resize(A->m, A->n);
        M.setZero();
        if (CS_CSC(A)) {
            for (csi j = 0 ; j < A->n ; j++) {
                for (csi p = A->p[j]; p < A->p[j + 1]; p++) {
                    M.coeffRef(A->i[p], j) = A->x[p];
                }
            }
        } else {
            for (csi idx = 0; idx < A->nz; idx++) {
                M.coeffRef(A->i[idx], A->p[idx]) += A->x[idx];
            }
        }
    }
    return M;
}

cs *EigenToCs(const Eigen::SparseMatrix<double, Eigen::ColMajor> &M, bool values) {
    if (!M.isCompressed()) {
        return nullptr;
    }
    cs *A = cs_spalloc(M.rows(), M.cols(), M.nonZeros(), values, false);
    if (A != nullptr) {
        assert(M.outerSize() == A->n);
        const auto *colIndices = M.outerIndexPtr();
        for (int j = 0; j < M.outerSize(); ++j) {
            A->p[j] = colIndices[j];
        }
        A->p[M.cols()] = M.nonZeros();

        assert(M.innerSize() == A->m);
        const auto *innerIndices = M.innerIndexPtr();
        const auto *valuesArray = M.valuePtr();
        for (csi idx = 0; idx < A->p[M.cols()]; ++idx) {
            A->i[idx] = innerIndices[idx];
            if (values) {
                A->x[idx] = valuesArray[idx];
            }
        }
    }
    return A;
}

// cs *EigenToCs(const Eigen::SparseMatrix<double, Eigen::RowMajor> &M, bool values) {
//     cs *A_transpose = EigenToCs(M.transpose(), values);
//     cs *A = cs_transpose(A_transpose);
//     cs_spfree(A_transpose);
//     return A;
// }

}  // namespace eigen_util
