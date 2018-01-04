#include "gtest/gtest.h"

#include <vector>

#include <Eigen/Dense>

extern "C" {

#include "cs.h"

}  // extern "C"

#include "sparse/eigen_util.h"


TEST(EigenToCs, ColMajorToCompressedColumn) {
    Eigen::SparseMatrix<double> eigenA(2, 3);
    {
        std::vector<Eigen::Triplet<double>> triplets;
        triplets.reserve(2);
        triplets.emplace_back(0, 1, 22.0);
        triplets.emplace_back(1, 0, 23.0);
        eigenA.setFromTriplets(triplets.begin(), triplets.end());
    }

    cs *A = eigen_util::EigenToCs(eigenA, true);
    ASSERT_NE(nullptr, A);
    EXPECT_EQ(A->m, 2);
    EXPECT_EQ(A->n, 3);
    EXPECT_EQ(A->nz, -1);

    EXPECT_EQ(A->i[0], 1);
    EXPECT_EQ(A->i[1], 0);

    EXPECT_EQ(A->p[0], 0);
    EXPECT_EQ(A->p[1], 1);
    EXPECT_EQ(A->p[2], 2);

    EXPECT_LE(A->x[0], 23.0);
    EXPECT_GE(A->x[0], 23.0);

    EXPECT_LE(A->x[1], 22.0);
    EXPECT_GE(A->x[1], 22.0);
    cs_spfree(A);

    A = eigen_util::EigenToCs(eigenA, false);
    ASSERT_NE(nullptr, A);
    EXPECT_EQ(A->m, 2);
    EXPECT_EQ(A->n, 3);
    EXPECT_EQ(A->nz, -1);

    EXPECT_EQ(A->i[0], 1);
    EXPECT_EQ(A->i[1], 0);

    EXPECT_EQ(A->p[0], 0);
    EXPECT_EQ(A->p[1], 1);
    EXPECT_EQ(A->p[2], 2);

    EXPECT_EQ(nullptr, A->x);

    cs_spfree(A);
}

TEST(EigenToCs, Recovery) {
    Eigen::SparseMatrix<double> eigenA(4, 4);
    {
        std::vector<Eigen::Triplet<double>> triplets = {
            {0, 1, 1.0},
            {1, 2, 1.0},
            {2, 3, 1.0},
        };
        eigenA.setFromTriplets(triplets.begin(), triplets.end());
    }
    cs *A = eigen_util::EigenToCs(eigenA, true);
    std::cerr << eigenA << std::endl;
    cs_print(A, false);
    cs_spfree(A);
}
