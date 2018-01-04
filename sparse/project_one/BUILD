load("//bazel:cc.bzl", "project_cc_test", "project_cc_binary", "project_cc_library")

project_cc_library(
    name = "project_one",
    srcs = ["project_one.cc"],
    hdrs = ["project_one.h"],
    deps = [
        "@csparse//:main",
        "@eigen//:eigen",
    ],
)

project_cc_test(
    name = "problem_one_test",
    srcs = ["problem_one_test.cc"],
    deps = [
        ":project_one",
        "//sparse:csparse_matrices",
    ],
)

project_cc_test(
    name = "problem_two_test",
    srcs = ["problem_two_test.cc"],
    deps = [
        ":project_one",
        "//sparse:csparse_matrices",
    ],
)

project_cc_test(
    name = "problem_three_test",
    srcs = ["problem_three_test.cc"],
    deps = [
        ":project_one",
        "//sparse:csparse_matrices",
        "//sparse:eigen_util",
    ],
)

project_cc_test(
    name = "problem_four_test",
    srcs = ["problem_four_test.cc"],
    deps = [
        ":project_one",
        "//sparse:csparse_matrices",
        "//sparse:eigen_util",
    ],
)
