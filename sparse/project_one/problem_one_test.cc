#include "gtest/gtest.h"

#include <random>
#include <vector>

#include <Eigen/Dense>

extern "C" {

#include "cs.h"

}  // extern "C"

#include "sparse/project_one/project_one.h"
#include "sparse/matrices.h"


TEST(CsGaxpy, TestMatrices) {
    for (size_t i = 0; i < matrices::NUM_MATRICES; ++i) {
        cs *T = matrices::LoadTripletFormMatrix(static_cast<matrices::MatrixName>(i));
        ASSERT_NE(nullptr, T);
        cs *A = cs_compress(T);
        ASSERT_NE(nullptr, A);

        Eigen::VectorXd x(A->n);
        Eigen::VectorXd y(A->m);
        Eigen::VectorXd z(A->m);
        x.setRandom();
        y.setRandom();

        z = y;
        project_one::cs_gaxpy(T, x.data(), y.data());
        cs_gaxpy(A, x.data(), z.data());
        EXPECT_TRUE(y.isApprox(z));

        // Check that the column compressed version still works.
        y.setRandom();
        z = y;
        project_one::cs_gaxpy(A, x.data(), y.data());
        cs_gaxpy(A, x.data(), z.data());
        EXPECT_TRUE(y.isApprox(z));

        cs_spfree(T);
        cs_spfree(A);
    }
}
