#include "gtest/gtest.h"

#include <random>
#include <vector>

#include <Eigen/Dense>

extern "C" {

#include "cs.h"

}  // extern "C"

#include "sparse/matrices.h"
#include "sparse/project_one/project_one.h"

TEST(CsGaxpy, TestAsh219) {
    for (size_t i = 0; i < matrices::NUM_MATRICES; ++i) {
        cs *T = matrices::LoadTripletFormMatrix(static_cast<matrices::MatrixName>(i));
        ASSERT_NE(nullptr, T);
        cs *A = cs_compress(T);
        ASSERT_NE(nullptr, A);
        cs *AT = cs_transpose(A, 1);
        ASSERT_NE(nullptr, AT);

        Eigen::VectorXd x(AT->n);
        Eigen::VectorXd y(AT->m);
        Eigen::VectorXd z(AT->m);
        x.setRandom();
        y.setRandom();

        z = y;
        project_one::cs_gatxpy(A, x.data(), y.data());
        cs_gaxpy(AT, x.data(), z.data());

        EXPECT_TRUE(y.isApprox(z));

        cs_spfree(T);
        cs_spfree(A);
        cs_spfree(AT);
    }
}
