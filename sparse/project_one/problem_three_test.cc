#include "gtest/gtest.h"

#include <random>
#include <vector>

#include <Eigen/Sparse>

extern "C" {

#include "cs.h"

}  // extern "C"

#include "sparse/eigen_util.h"
#include "sparse/matrices.h"
#include "sparse/project_one/project_one.h"


TEST(CsFind, TestAsh219) {
    for (size_t i = 0; i < matrices::NUM_MATRICES; ++i) {
        cs *T = matrices::LoadTripletFormMatrix(static_cast<matrices::MatrixName>(i));
        ASSERT_NE(nullptr, T);
        cs *A = cs_compress(T);
        ASSERT_NE(nullptr, A);
        cs *S = project_one::cs_find(A);
        ASSERT_NE(nullptr, S);

        EXPECT_EQ(T->nz, S->nz);
        EXPECT_EQ(T->nz, S->nzmax);

        EXPECT_EQ(T->n, S->n);
        EXPECT_EQ(T->m, S->m);

        if (T->p == nullptr || S->p == nullptr) {
             ASSERT_EQ(T->p, S->p);
        }

        Eigen::SparseMatrix<double> eigenT = eigen_util::CsToEigen(T);
        Eigen::SparseMatrix<double> eigenS = eigen_util::CsToEigen(T);

        EXPECT_TRUE(eigenT.isApprox(eigenS, 0.0));

        cs_spfree(S);
        cs_spfree(T);
        cs_spfree(A);
    }
}
