#include "gtest/gtest.h"

#include <random>
#include <vector>

#include <Eigen/Dense>

extern "C" {

#include "cs.h"

}  // extern "C"

#include "sparse/eigen_util.h"
#include "sparse/matrices.h"
#include "sparse/project_one/project_one.h"

TEST(CsGaxpySym, TestMatrices) {
    Eigen::SparseMatrix<double> eigenA(2, 2);
    {
        std::vector<Eigen::Triplet<double>> triplets;
        triplets.reserve(2);
        triplets.emplace_back(0, 1, 22.0);
        triplets.emplace_back(1, 0, 22.0);
        eigenA.setFromTriplets(triplets.begin(), triplets.end());
    }

    Eigen::VectorXd x(2);
    x.setRandom();

    Eigen::VectorXd y(2);
    y.setRandom();


    Eigen::VectorXd z(2);
    Eigen::VectorXd z_sym(2);
    {
        cs *A = eigen_util::EigenToCs(eigenA, true);
        ASSERT_NE(nullptr, A);

        z = y;
        ASSERT_EQ(1, cs_gaxpy(A, x.data(), z.data()));
        z_sym = y;
        ASSERT_EQ(1, project_one::cs_gaxpy_sym(A, x.data(), z_sym.data()));

        ASSERT_TRUE(z_sym.isApprox(z));

        cs_spfree(A);
    }

    // Now intentionally corrupt lower triangular.
    eigenA.coeffRef(1, 0) = 2;
    {
        cs *A = eigen_util::EigenToCs(eigenA, true);
        ASSERT_NE(nullptr, A);

        z_sym = y;
        ASSERT_EQ(1, project_one::cs_gaxpy_sym(A, x.data(), z_sym.data()));

        ASSERT_TRUE(z.isApprox(z_sym));

        cs_spfree(A);
    }
}
